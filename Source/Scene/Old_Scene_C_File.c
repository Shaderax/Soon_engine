#include "Scene.hpp"

void		select_shader(t_scene *scene, t_object *obj, int ret)
{
	if (obj->normal_array.size && ret == 1)
	{
		printf("1\n");
		new_shader(&scene->shader, "./shader/vertex.glsl", "./shader/fragment.glsl");
	}
	else if (obj->normal_array.size)
	{
		printf("2\n");
		new_shader(&scene->shader, "./shader/vertex_no_texture.glsl", "./shader/fragment_no_texture.glsl");
	}
	else if (ret == 1)
	{
		printf("3\n");
		new_shader(&scene->shader, "./shader/vertex_no_light.glsl", "./shader/fragment_no_light.glsl");
	}
	else
	{
		printf("4\n");
		new_shader(&scene->shader, "./shader/vertex_no_light_no_texture.glsl", "./shader/fragment_no_light_no_texture.glsl");
	}
}

t_scene		new_scene(t_window *window, char *path, char *text)
{
	t_scene scene;
	int		ret;

	ret = 0;
	bzero(&scene, sizeof(t_scene));
	scene.obj = new_object(path);
	printf("COCO\n");
	if (scene.obj.texture_coord.size)
		ret = new_obj_texture(text, &scene.obj.texture);
	printf("ret : %d\n", ret);
	select_shader(&scene, &scene.obj, ret);
	new_view(&scene.camera, 0.05f);
	new_projection_matrix(45.0f, (float)window->width / (float)window->height,
		&scene.camera);
	scene.ambient = new_light((t_vec4){0.0f, 0.0f, 0.0f},
		(t_vec4){1.0f, 1.0f, 1.0f, 1.0f}, 0.1f);
	scene.spot = new_light((t_vec4){1.2f, 1.0f, 2.0f},
		(t_vec4){1.0f, 1.0f, 1.0f, 1.0f}, 1.0f);
	return (scene);
}

namespace Soon
{
	Scene::Scene( void )
	{
		_currentCamera = null;
		_objects.resize = 100;
	}
}
