# Readme for the GameEngine 7

![Demo Screenshot](docs/screenshots/HeaderImg.png)\
engine that uses brushes to render the world.\
Supports Trenchbroom import ([TRENCHBROOM MAP BUILDING](#TrenchBroomMapBuilding)).\
pbr shaders

***

# Table of Contents
1. [QuickStart](#QuickStart)
2. [Build (EXE,Release)](#Build)
3. [Project Setup](#ProjectSetup)
4. [TRENCHBROOM MAP BUILDING](#TrenchBroomMapBuilding)
5. [Features / todo list](#FeatureList)
6. [Screenshots](#Screenshots)

#### external (`docs/`)
[BasicSetup](docs/BasicSetup.md)\
[Entity Functions](docs/EntityFunctions.md)

# QuickStart
1. Build this code [Build (EXE,Release)](#Build)
2. Build OpenAl [Compiling_OpenAl](#CompilingOpenAl)
3. copy folders `\shaders` to Build folder
4. copy folders `\resources\textures` to Build folder
5. create `\saves`
6. copy `PipeMap.obj` and `PipeMap.map` to Build folder. they can be found at `resources/maps`

# Build

```
mkdir Build
cd Build
cmake ..
cmake --build . --config Release
```

# ProjectSetup

CMake does not build OpenAL and puts dll into the Build folder

if you are using only Engine7 (without an example project) keep reading, else just make sure that files exist

1. Get Engine Folder or Example Engine7 Project
2. create files EntManager.h,EntUser.h,GameEnt.cpp,GameSubsys.cpp in game folder
3. setup files EntManager.h,EntUser.h,GameEnt.cpp,GameSubsys.cpp, example in `docs/BasicSetup.md`
4. add "textures", "shaders" folder to Build folder
5. "textures" folder must contain "textures.ini", example in `docs/BasicSetup.md`
6. "textures" folder must contain your textures
7. "shaders" folder must contain your shaders (Vertex,Fragment)

##### IMPORTANT : for engine to launch, OpenAl32.dll should be present

### CompilingOpenAl

1. Compile OpenAL (openal-soft), guides can be found in readme for OpenAl or you can use this
```
mkdir Build
cd Build
cmake ..
cmake --build . --config Release
```
2. paste OpenAl32.dll file into the Build folder





**code is in the docs/BasicSetup.md**
`docs/BasicSetup.md` also contains file structure

---

## Entity Functions can be found at `docs/EntityFunctions.md`

---
# TrenchBroomMapBuilding

**this step needs 2 files**
* .map
* .obj

to get obj use `export>Wavefront OBJ...`\
pass 2 files with "textures.ini"\
save is built into a function so map can be loaded faster with `.gems` format\
example:
`Game.CompileTrenchBroomMap("PipeMap.obj","PipeMap.map","saves/test1.gems","textures/textures.ini");`

### what is .GEMS ?

`.gems` is a compiled map for engine7.\
`.gem` was a map format that stores Brushes and Entity data in binary

`.gems` was made more flexible, for any type of entity. (data isn't constrained to 64 bytes)\
by passing only `.gems` engine needs less time to load a level compared to `.map` or `.obj`

#### Format structure

1. int BrushN | Brush Number in a level
2. Brushes | (slightly compressed. Unused sides removed)
3. unsigned int EntN | Ent Number
4. every entity DEBUG name (64 bytes)
5. entity custom data. any format. Use Save Load function for that.


.gems can be built from `.map` AND `.obj` AT THE SAME TIME


---

# FeatureList

### DONE
* scripting with classes
* lighting system (point,spot)
* collisions
* world raycast
* particle system
* mappable keys
* level loading/saving (quick save/load)
* PBR
* Flood Light (with shadows)
* trenchbroom map loading and saving (obj,.map)
* _level loading_
* GUI (ImGUI)
* audio
* player controller (DEMO)
### WORKING ON
### TODO

* static prop creation,compilation  **[CANCELED]**
* GUI   **[CANCELED]**


# Screenshots

#### Full Engine Window
![FullScreen](docs/screenshots/FullScreen1.png)
#### Full Engine Window (point light ONLY)
![FullScreen](docs/screenshots/FullScreen2.png)

#### Texture example
![FullScreen](docs/screenshots/TextureExample.png)\
RED - metallic(0-255) | GREEN - roughness(0-255) or shininess

---
# License
**This project is licensed under the GNU GENERAL PUBLIC LICENSE**

## Third-Party Licenses
**This project uses third-party libraries which have their own licenses**

* [GLFW](licenses/GLFW)  **| https://www.glfw.org/**
* [GLEW](licenses/GLEW)  **| https://glew.sourceforge.net/**
* [ImGui](licenses/ImGui)  **| https://github.com/ocornut/imgui**
* [OpenAl](licenses/OpenAl)  **| https://github.com/kcat/openal-soft**
* [SimpleGl](licenses/SimpleGl) **| https://github.com/kitaS24/SimpleGl**