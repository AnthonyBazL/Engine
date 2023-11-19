# Engine
This project is a sandbox for different engine rendering topics.
The goal is to acquire some knowledge on various rendering topics but also on different graphic APIs.


## General
  ### Interface
  - [X] Manage ImGui interface
  - [ ] Manage a simple camera [WIP]
  - [ ] Manage object selection
  - [X] Manage object local transform properties (translate, rotate, scale)
  
  ### OBJ Loader
  - [ ] Deserialize OBJ file
    - [X] Deserialize a single object from an OBJ file
    - [x] Deserialize multiple objects from the same OBJ file
    - [ ] Deserialize OBJ files with faces without UVs coordinates
  - [ ] Manage OBJ file containing both quad and triangulate faces
    - [ ] Identify when an OBJ file contains quad or triangulate faces
    - [ ] Convert quad faces to triangulate faces
       
  ### Profiler
  - [ ] Track FPS
  - [ ] Track memory consumption (to define)
  - [ ] Track CPU consumption (to define)
  - [ ] Track GPU consumption (to define)

<br/><br/>

## Rendering
  ### OpenGL rendering
  - [X] Hello world with triangle
  - [x] Render a custom mesh
    - [x] A simple object from an OBJ file
    - [x] Multiple object from an OBJ file
  - [x] Apply a simple unlit shader
  - [x] Apply a simple texture 2D shader
  - [x] Apply a simple lit shader
  - [ ] Apply a 3D texture shader
  
  ### DirectX rendering
  - [ ] Hello world with triangle
  
  ### Vulkan rendering
  - [ ] Hello world with triangle

  ### Metal rendering ?
  - [ ] Hello world with triangle

  ### Ray tracing rendering
  - [ ] Render a simple unlit sphere
  - [ ] Render multiple inlit spheres
  - [ ] Render multiple spheres with simple lighting
  - [ ] Implement octree optimization

<br/><br/>

## Topics to investigate
  - [ ] Geometric shader
  - [ ] PBR texture rendering
  - [ ] Quadtrees
  - [ ] Octrees
  - [ ] BVH (Bounding Volume Hierarchies)
  - [ ] Spline editor
  - [ ] Mesh collision
  - [ ] Fog/fluid simulation
  - [ ] ...
  
