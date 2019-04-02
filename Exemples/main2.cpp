Soon::Engine& engine = Soon::Engine::GetInstance();
// or
// Soon::Init();

int main(int argc, char**argv)
{
	Soon::Window window("Je suis suisse.");
	window.makeContextCurrent();

	Scene& scene = engine.NewScene();

	Object& object1 = scene.NewObjectInScene();

	object1.AddComponent<GravityComponent>();

	engine._world.AddSystem<GravitySystem>();

	engine.Update();

	return (0);
}
