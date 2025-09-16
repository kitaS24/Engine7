# Functions that can be used when programing entity
this file contains most functions

## Entity Functions update (scripting)

| Function         | In                                                       | return      | Description                                                                                      |
|------------------|----------------------------------------------------------|-------------|--------------------------------------------------------------------------------------------------|
| Think            | float TPS                                                | float (sec) | called with return delay                                                                         |
| Save             | std::ofstream &File                                      | void        | called when saving, save your important vars here                                                |
| Load             | std::ifstream &File                                      | void        | called when loading, load your important vars here **MUST BE SAME**                              |
| Render3D         |                                                          | void        | called when rendering 3d                                                                         |
| Render2D         |                                                          | void        | called when rendering 2d                                                                         |
| PreRender        |                                                          | void        | called when rendering (3d) begins                                                                |
| SetVar           | std::string Var,std::string Val                          | void        | called when map is loaded with trenchbroom and var needs to be set in the entity                 |
| ShadowPass       | Vec3 LightPos,Vec3 LightSize,Vec3 LightDir,GLuint Shader | void        | called when 3d shadows are baked, render your geometry with the **Shader** for it to cast shadow |
| Cleanup          |                                                          | void        | called before engine shuts down                                                                  |
| OnMapStart       |                                                          | void        | called when map starts (1st tick)                                                                |
| GetDebugName     |                                                          | std::string | called to request entity debug name                                                              |
| CreateVarWindow  | int cId,Vec2I W                                          | void        | called to draw debug window                                                                      |

## Entity Functions

| Function    | In                            | return | Description                                                                                                       |
|-------------|-------------------------------|--------|-------------------------------------------------------------------------------------------------------------------|
| KillSelf    |                               | void   | Flags Entity to be killed (public)                                                                                |
| GetPos      |                               | Vec3   | Returns Entity Pos (public)                                                                                       |
| GetScale    |                               | Vec3   | Returns Entity Scale (public)                                                                                     |
| GetRotation |                               | Vec3   | Returns Entity Rotation (public)                                                                                  |
| SetPos      | Vec3                          | void   | Sets Entity Pos (public)                                                                                          |
| SetRot      | Vec3                          | void   | Sets Entity Rot (public)                                                                                          |
| SetScale    | Vec3                          | void   | Sets Entity Scale (public)                                                                                        |
| addVel      | Vec3                          | void   | Adds Velocity to the entity velocity (public)                                                                     |
| ChangeMap   | std::string Map,bool IsNewMap | void   | Sets Map for engine to load. bool IsNewMap is used when loading new map (not quicksave),OnMapStart will be called |
| SetWeight   | float Kg                      | void   | Sets weight in KG                                                                                                 |
| GetWeight   |                               | float  | Gets weight in KG                                                                                                 |
| GetForce    | float G                       | float  | Returns force -Y                                                                                                  |
| GetForceVec | Vec3 G                        | Vec3   | Returns force Vec                                                                                                 |
| GetMomentum |                               | Vec3   | Returns momentum (from ent Vel)                                                                                   |

## Entity Events

when calling pass 2 arguments
* Ent *activator | original activator
* Ent *caller | last activator (self)

| Function       | In                          | return | Description                                 |
|----------------|-----------------------------|--------|---------------------------------------------|
| OnFire         | Ent *activator,Ent *caller  | void   | Called when ent is triggered by another ent |
| OnDamage       | Ent *activator,Ent *caller  | void   | Called when ent is taking damage            |
| OnInteract     | Ent *activator,Ent *caller  | void   | Called when player presses "E"              |
| OnKill         | Ent *activator,Ent *caller  | void   | Called when entity must be killed           |
| OnPlayerDeath  | Ent *activator,Ent *caller  | void   | Called when player dies                     |
| OnPlayerShoot  | Ent *activator,Ent *caller  | void   | Called when player shoots                   |

## Entity Variables/Pointers

| Type                                | Name        | Description                                                                                                               |
|-------------------------------------|-------------|---------------------------------------------------------------------------------------------------------------------------|
| Brush *                             | Brushes     | Level brushes (pointer)                                                                                                   |
| Material *                          | Materials   | Loaded Materials                                                                                                          |
| Vec3                                | Pos         | Entity Position                                                                                                           |
| Vec3                                | Rot         | Entity Rotation                                                                                                           |
| Vec3                                | Vel         | Entity Velocity                                                                                                           |
| Vec3                                | Scale       | Entity Scale                                                                                                              |
| float                               | Time        | Time From Engine Start                                                                                                    |
| DISPLAY *                           | Display     | Display Struct with data for display                                                                                      |
| Vec3 *                              | CamPos      | Camera Position                                                                                                           |
| Vec3 *                              | CamRot      | Camera Rotation                                                                                                           |
| Vec3 *                              | CamRotVec   | Camera Look Vector                                                                                                        |
| MapKey *                            | UserKeyBind | User KeyBinds (class. use Map(unsigned char Key,int glfwVal) to bind, use key(unsigned char Key) to get mapped key state) |
| std::vector<std::unique_ptr<Ent>> * | Ents        | Pointer to the list with all entities                                                                                     |
| MapTransition *                     | Transition  | Pointer to struct for level transition                                                                                    |


## SubSystem Functions


| FunctionName                     | In                                                                                                                                                 | Out       | Description                                                                                        |
|----------------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------|-----------|----------------------------------------------------------------------------------------------------|
| RotateBrush()                    | Brush &Br,Vec3 SetRot,Vec3 RotPoint                                                                                                                | void      | sets rotation for the brush                                                                        |
| RenderSideRotate()               | BrushSide Br,Vec3 Transform[3],Vec3 Matrix[3]                                                                                                      | BrushSide | rotates brush side with matrices (including vert)                                                  |
| CollisionSideRotate()            | BrushSide Br,Vec3 Transform[3],Vec3 Matrix[3]                                                                                                      | BrushSide | rotates brush side with matrices (ONLY normals, Collision Pos)                                     |
| AddLight()                       | GpuLights *L,Vec3 Pos,Vec3 Color,Vec3 Dir,float InnerCone,float OuterCone                                                                          | void      | adds light to the scene                                                                            |
| AddFloodLight()                  | GpuLights *L,Vec3 Pos,Vec3 Color,Vec3 Size,Vec3 Dir,GLuint DT                                                                                      | void      | adds floodlight to the scene                                                                       |
| InitFloodLight()                 | GLuint &tx,GLuint &fbo,GLuint &rbo                                                                                                                 | void      | creates floodlight texture/setup.Provide 3 GLuint s                                                |
| UpdateFloodLight()               | Vec3 LightPos,Vec3 LightSize,Vec3 LightDir,GLuint Shader,Vec2 WindowSize,std::vector<std::unique_ptr<Ent>> &Ent,GLuint &tx,GLuint &fbo,GLuint &rbo | void      | renders world to the flood texture                                                                 |
| CollisionWorld()                 | Brush *Brushes,unsigned int CheckBrushes,Vec3 Point                                                                                                | bool      | returns TRUE if point is inside of any brush                                                       |
| CollisionWorldArea()             | Brush *Brushes,unsigned int CheckBrushes,Vec3 Point,Vec3 HSize                                                                                     | bool      | returns TRUE if AABB area is inside of any brush                                                   |
| AABBtoAABB()                     | Vec3 A1,Vec3 A2,Vec3 B1,Vec3 B2                                                                                                                    | bool      | AABB to AABB                                                                                       |
| AABBtoAABBSmart()                | Vec3 A1,Vec3 A2,Vec3 B1,Vec3 B2                                                                                                                    | bool      | Same as AABB to AABB ,but can flip pA and pB so AABB always works                                  |
| CreateBrushBoundingBox()         | Brush &Br                                                                                                                                          | void      | Updates Brush Bounding Box by vert                                                                 |
| CreateBrushBoundingBoxNormals()  | Brush &Br                                                                                                                                          | void      | Updates Brush Bounding Box by collision box                                                        |
| CreateBrushBoundingBoxAll()      | Brush &Br                                                                                                                                          | void      | does both: CreateBrushBoundingBox and CreateBrushBoundingBoxNormals                                |
| MapKey.Map()                     | unsigned char Key,int glfwVal                                                                                                                      | void      | Maps Key(char) to GLFW value. Example: at start 'A'=='A', can be changed so, 'A'='B'               |
| MapKey.key()                     | unsigned char Key                                                                                                                                  | bool      | Set Key to key before it was mapped                                                                |
| MapKey.SetupGlfwKeys()           |                                                                                                                                                    | void      | Sets All keys to initial val ('A'=='A')                                                            |
| RenderParticle()                 | Vec3 *Pos,unsigned int RenderParticles,Vec3 Rot,Vec2 Size,Material *Material,GpuLights *L,unsigned int LN,Vec3 CamPos,Vec4 Color                   | void      | Renders Particles Facing to the camera (can render any amount of particles, is material is shared) |
| ShadowRenderParticle()           | Vec3 *Pos,unsigned int RenderParticles,Vec3 Rot,Vec2 Size,GLuint Shader,Vec3 LightPos,Vec3 LightSize,Vec3 LightDir                                 | void      | Allows for particles to have shadows                                                               |
| WorldRaycast()                   | Vec3 Start,Vec3 End,Vec3 Size,float SampleRate,Brush *Brushes                                                                                      | float     | Returns Distance to any brush in a level. Input:Start,End pos                                      |
| SoundEngineSource.Setup()        | Vec3 P                                                                                                                                             | void      | Init, set audio pos                                                                                |
| SoundEngineSource.UpdatePos()    | Vec3 P                                                                                                                                             | void      | set audio pos                                                                                      |
| SoundEngineSource.UpdateSpeed()  | float Speed                                                                                                                                        | void      | Sets audio play speed                                                                              |
| SoundEngineSource.LoadWavSound() | std::string filename,float Vol                                                                                                                     | bool      | Loads WAV file (UNCOMPRESSED,Audacity can be used for that)                                        |
| SoundEngineSource.Pause()        |                                                                                                                                                    | void      | Pauses the sound                                                                                   |
| SoundEngineSource.UnloadSound()  |                                                                                                                                                    | void      | Unloads sound (OpenAL buffer)                                                                      |
| SoundEngineSource.Delete()       |                                                                                                                                                    | void      | Deletes source,Stops Audio,Unloads                                                                 |
| SoundEngineSource.Play()         | float SoundVolume                                                                                                                                  | void      | Plays the sound                                                                                    |
