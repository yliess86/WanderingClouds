#define STB_IMAGE_IMPLEMENTATION

#include "vendor/include/glad/glad.h"

#include<GLFW/glfw3.h>

#include "include/quad.h"
#include "include/clock.h"
#include "include/controller.h"
#include "include/navigator.h"
#include "include/texture.h"
#include "include/uniform.h"
#include "include/vec.h"
#include "include/window.h"

const char*        TITLE         = "WanderingClouds\0"; 
const char*        VS_FILE       = "resources/shaders/default.vert\0";
const char*        FS_FILE       = "resources/shaders/default.frag\0";
const char*        NOISE_2D_FILE = "resources/textures/blue_noise.png\0";
const char*        NOISE_3D_FILE = "resources/textures/fbm_noise_512_8_5.dat\0";

const unsigned int VERSION[]     = { 3, 3 };
const unsigned int SIZE   []     = { 512, 512 };
      float        FSIZE  []     = { (float)SIZE[0], (float)SIZE[1] };
const float        CLEAR  []     = { 0.0f, 0.0f, 0.0f, 1.0f };

const float        FPS_CAP       = 60.0f;

int main() {
	Window* window  = new Window(TITLE, SIZE, VERSION, CLEAR);
	Clock*  clock   = new Clock();
	Shader* shader  = new Shader(VS_FILE, FS_FILE);
	Tex2D*  noise2D = new Tex2D(NOISE_2D_FILE, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	Tex3D*  noise3D = new Tex3D(NOISE_3D_FILE, GL_TEXTURE1, GL_RED,  GL_FLOAT        );
	Quad*   quad    = new Quad(shader);
	Nav*    nav     = new Nav(Vec3());

	Uniform1f* u_time       = shader->GetUniform<Uniform1f>("u_time");
	Uniform2f* u_resolution = shader->GetUniform<Uniform2f>("u_resolution");
	Uniform1i* u_noise2D    = shader->GetUniform<Uniform1i>("u_noise2D");
	Uniform1i* u_noise3D    = shader->GetUniform<Uniform1i>("u_noise3D");
	Uniform3f* u_pos        = shader->GetUniform<Uniform3f>("u_pos");

	shader->Use();
	{
		u_resolution->SetValue(FSIZE);
		u_noise2D->SetValue(0);
		u_noise3D->SetValue(1);
	}

	while (window->Running()) {
		clock->Tick();

		if (clock->DeltaTime() >= 1 / FPS_CAP) {
			clock->Reset();			
			window->Clear();

			// Navigator Update
			nav->Update(clock->DeltaTime());
			
			// Display Update
			shader->Use();
			{
				u_time->SetValue(clock->EllapsedTime());		
				u_pos->SetValue(nav->transform.pos.Data());
				
				noise2D->Bind();
				noise3D->Bind();
			}
			quad->Draw();

			window->Update();
		}
	}

	delete nav;
	delete quad;
	delete noise2D;
	delete noise3D;
	delete shader;
	delete clock;
	delete window;
	
	return EXIT_SUCCESS;
}
