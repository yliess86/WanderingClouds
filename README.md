# Wandering Clouds: a Raymarching Navigation Engine for the Wandering Mind Project

Wandering Clouds is a navigation engine for the Wandering Mind Project initated by Xin LIU and Gershon DUBLON as an art project.
It uses RayMarching to render Wandering Mind States -- Sleep or Awake VS Wandering -- as a sky full with clouds.
The Wanering State map can be loaded into the engine as a binary `.dat` file.
The project relied on GLFW and OpenGL via GLAD. 

## Use

```sh
mkdir build
cd build
cmake ..
make
cd ..
./build/WanderingClouds
```

or

```sh
make
```

## Binary File Format

The file contains:

|Name   |Start (Bytes)|Length (Bytes) |Type   |Description                |
|:------|:------------|:--------------|:------|:--------------------------|
|Size   |0            |3 * 4          |Int32  |width x height x depth     |
|Content|3 * 4        |Remaining Bytes|Float32|Contiguous Major Row Tensor|
