# Soon Engine

A Vulkan game engine to practice my C++ skill and 3D programming.

[![Exemple](/Extern/Example.png)]()

## Disclaimer

It is a learning project that is ongoing and not complete.
Feel free to contact me to discuss it, if you have any ideas to add.

## Status

The engine has undergone many architectural changes. Because I wanted to experience a lot of things.
It is not yet very readable, but as it develops it should become more comfortable to read.
Today the project is only at the beginning.

## Basic Example
Forget the includes...

```
#include "Core/Engine.hpp"
#include "Utilities/ShowFps.hpp"
#include "Core/Scene/Object.hpp"
#include "Utilities/MeshArray.hpp"
#include "Core/Scene/3D/Components/Mesh.hpp"
#include "Core/Scene/3D/Components/Camera.hpp"
#include "Core/Scene/3D/Systems/3dObjectControlerSystem.hpp"
#include "Core/Scene/3D/Components/3dObjectControler.hpp"
#include "ECS/World.hpp"
#include "Core/Parsers/RessourceImporter.hpp"
#include "Core/Scene/Instantiate.hpp"

Soon::Engine& engine = Soon::Engine::GetInstance();

int main(int argc, char**argv)
{
        double lastTime = glfwGetTime();

        engine._world.AddSystem<ObjectControlerSystem>();

        Soon::Object Camera;
        Camera.AddComponent<Soon::Camera3D>();
        Camera.AddComponent<ObjectControler>();

        Soon::MeshArray* ar = Soon::RessourceImporter::GetSingleton().Load<Soon::MeshArray>("../Ressources/Objects/Borderlands 2 - Maya/untitled.obj");
        Soon::Object* Maya = Instantiate(*ar);

        while (!engine.ShouldEnd())
        {
                lastTime = ShowFPS(lastTime);
                engine.Update();
                engine.DrawFrame();
        }

        return (0);
}
```
