#ifndef CLOCK_H
#define CLOCK_H

#include<chrono>

class Clock {
public:
	Clock ();
	~Clock();

	void Reset();
	void Tick ();
	
	float DeltaTime   ();
	float EllapsedTime();

private:
	std::chrono::system_clock::time_point m_start;
	std::chrono::duration<float>          m_dt;
	std::chrono::duration<float>          m_ellapsed;
};

#endif
