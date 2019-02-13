/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 17:15:25 by nrouzeva          #+#    #+#             */
/*   Updated: 2019/02/13 21:30:24 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
void	looper(t_scene *scene, t_window *window)
{
	t_vec4	sub;
	double	lastime;
	int		nb_frame;

	lastime = glfwGetTime();
	nb_frame = 0;
	printf("%f\n", scene->obj.texture_coord.array[2]);
	t_vec3 v_colore;
	v_colore[0] = 0.4f;
	v_colore[1] = 0.04f;
	while (!glfwWindowShouldClose(window->win))
	{
		show_fps(&lastime, &nb_frame);
		input_control(window, scene);
		if (glfwGetKey(window->win, GLFW_KEY_HOME) == GLFW_PRESS)
		{
			v_colore[0] -= 0.0001f;
			v_colore[1] -= 0.00001f;
		}
		if (glfwGetKey(window->win, GLFW_KEY_END) == GLFW_PRESS)
		{
			v_colore[0] += 0.0001f;
			v_colore[1] += 0.00001f;
		}
		vec4_add(scene->camera.pos, scene->camera.target, sub);
		set_view(scene->camera.pos, sub, scene->camera.rotate, scene->camera.view);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		mat4_rotate(scene->obj.rotate, glfwGetTime() / 500000, 2, scene->obj.rotate);
//		compute_model(&scene->obj);
		compute_mvp(&scene->obj, &scene->camera);
		glUseProgram(scene->shader.shader_program);
		set_vec3_shader(scene->shader.shader_program, "ambient_light", scene->ambient.pos);
		if (scene->obj.texture_coord.size)
			set_int_shader(scene->shader.shader_program, "texture1", scene->obj.texture.txt);
		set_vec2_shader(scene->shader.shader_program, "o_color", v_colore);
		if (scene->obj.normal_array.size)
		{
			set_vec3_shader(scene->shader.shader_program, "pos_light", scene->spot.pos);
			set_vec3_shader(scene->shader.shader_program, "camPos", scene->camera.pos);
			set_mat4_shader(scene->shader.shader_program, "model", scene->obj.model);
		}
		set_mat4_shader(scene->shader.shader_program, "mvp", scene->obj.mvp);
		glBindVertexArray(scene->obj.vao);
		glDrawArrays(GL_TRIANGLES, 0, scene->obj.vertex_array.size / 3);
		glfwSwapBuffers(window->win);
		glfwPollEvents();
	}
}
*/

int		main(int argc, char **argv)
{
//	t_scene		scene;

	if (!init_glfw())
		return (error("Error : Arguments or glfw"));
	
	Window		window("Je suis suisse.");
	if (!window._win)
		return (error("Error : Window init"));
	window.makeContextCurrent();

	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 1.0f);
	glfwSwapInterval(0);
	
	while (!window.shouldClose())
	{
		glfwSwapBuffers(window._win);
		glfwPollEvents();
	}

//	window = new_window(1920, 1080, "JE SUIS FENETRE");
//	if (!window.win)
//		return (error());
//	set_mouse_win(&window);

//	glEnable(GL_DEPTH_TEST);
//	glClearColor(0, 0, 0, 1.0f);
//	// fps
//	glfwSwapInterval(0);
////	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

//	scene = new_scene(&window, argv[1], argv[2]);
//	print_mat("VIEW", scene.camera.view);
//	print_mat("PROJ", scene.camera.proj);
//	compute_model(&scene.obj);
//	print_mat("MODEL", scene.obj.model);
//	compute_mvp(&scene.obj, &scene.camera);
//	print_mat("mvp", scene.obj.mvp);
//
//	glEnable(GL_CULL_FACE);
//	glCullFace(GL_BACK);
////	glFrontFace(GL_CCW);  
//
//	looper(&scene, &window);
//	delete_object(scene.obj);
	return (0);
}
