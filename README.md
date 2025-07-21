# Imzi Engine

Imzi means tiny in Amazigh!

The goal is simple, building a tiny engine for rendering both 2D and 3D items! 

# Structure
The project is split into 3 Layers, Core is where the abstraction for rendering, audio, IO will be. This will eventually also encapsulate the OpenGL rendering backend and maybe even a Vulkan backend if I feel spicy/ 

Engine will have systems and primitives that we can use to build games. These include sprites, animations, Asset Managers, Rigid Bodies and so on. 

Game is where the user would use the engine layer to build their game using the systems from the engine layer.

# Restrictions

Core must only ever use vendor libraries.
Engine must only ever use Core and vendor libraries.
Game must only ever use vendors and Engine without reaching for Core.