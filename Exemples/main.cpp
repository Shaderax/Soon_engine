Soon::Engine& engine = Soon::Engine::GetInstance();

int main(int argc, char**argv)
{
	Scene& scene = engine.NewScene();

	Object& object1 = scene.NewObjectInScene();

	object1.AddComponent<GravityComponent>();

	engine._world.AddSystem<GravitySystem>();

	while (engine.ShouldClose())
		engine.Update();

	return (0);
}


Soon::Engine& engine = Soon::Engine::GetInstance();

int main(int argc, char**argv)
{
	//engine.Init();
	//engine.

	Scene& scene = engine.NewScene();

	Object& object1 = scene.NewObjectInScene();

	object1.AddComponent<GravityComponent>();

	engine._world.AddSystem<GravitySystem>();

	while (engine.ShouldClose())
		engine.Update();

	return (0);
}
