#include "Entity.hpp"
#include "Transform.hpp"

int main()
{
    Entity entite;

    Transform& tr = entite.AddComponent<Transform>();

    tr.Disable();
    tr.Enable();

    entite.Deactivate();

    // Wut if Mesh.Disable();
}