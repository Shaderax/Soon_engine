/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 19:39:06 by nrouzeva          #+#    #+#             */
/*   Updated: 2019/01/24 16:48:16 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

#include <iostream>

# define GLFW_INCLUDE_GLCOREARB
# include <GLFW/glfw3.h>
# define OPENGL_MAJOR_VERSION 4
# define OPENGL_MINOR_VERSION 1

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

#include "window.hpp"
#include "mouse.hpp"
#include "scene.hpp"

#include "matLibHeader.hpp"

/*
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>

# include "matrix.h"

# define TRUE 1
# define FALSE 0
# define BUFFER_SIZE 128
# define BSIZE 2048
# define SIZE_ALLOC(X) (((X) / BSIZE) * BSIZE + BSIZE)
# define NEAR 0.0001f
# define FAR 10000.0f

typedef struct	s_shader
{
	unsigned int	shader_program;
	GLuint			v_shader_id;
	GLuint			f_shader_id;
}				t_shader;

typedef struct	s_buffer
{
	GLfloat	*array;
	GLuint	vbo;
	int		size;
	t_vec3	min;
	t_vec3	max;
}				t_buffer;

typedef struct	s_texture
{
	unsigned int	txt;
	unsigned char	*data;
	int				width;
	int				height;
	int				size;
}				t_texture;

typedef struct	s_object
{
	t_buffer	vertex_array;
	t_buffer	normal_array;
	t_buffer	texture_coord;
	t_texture	texture;
	GLuint		vao;
	t_mat4		model;
	t_mat4		translate;
	t_mat4		rotate;
	t_mat4		scale;
	t_mat4		mvp;
}				t_object;

typedef struct	s_camera
{
	t_vec4	pos;
	t_vec4	target;
	t_vec4	rotate;
	t_mat4	view;
	t_mat4	proj;
	float	near;
	float	far;
	float	speed;
}				t_camera;

typedef struct	s_mouse
{
	float	last_x;
	float	last_y;
	double	new_x;
	double	new_y;
	float	off_x;
	float	off_y;
	float	sensitivity;
	float	yaw;
	float	pitch;
}				t_mouse;

typedef struct	s_window
{
	int			width;
	int			height;
	GLFWwindow	*win;
	t_mouse		mouse;
}				t_window;

typedef struct	s_light
{
	t_vec4	pos;
	t_vec4	color;
	float	strength;
}				t_light;

typedef struct	s_scene
{
	t_light		ambient;
	t_object	obj;
	t_light		spot;
	t_camera	camera;
	t_shader	shader;
	char		option;
}				t_scene;

void			input_control(t_window *window, t_scene *scene);
int				new_shader(t_shader *shader, char *pathv, char *pathf);
GLuint			load_shader(char const *path_shader, int shader_type);
unsigned int	new_shader_program(GLuint vertex, GLuint fragment);
void			set_vec2_shader(GLint shader_program, char *name, t_vec3 vec);
void			set_vec3_shader(GLint shader_program, char *name, t_vec4 vec);
void			set_mat4_shader(GLint shader_program, char *name, t_mat4 mat);
void			set_int_shader(GLint shader_program, char *name, int integer);
t_window		new_window(int width, int height, char *name_window);
void			delete_object(t_object obj);
t_object		new_object(char *path);
void			compute_model(t_object *obj);
void			compute_mvp(t_object *obj, t_camera *cam);
void			new_projection_matrix(float fov, float ratio, t_camera *cam);
void			set_projection_matrix(float fov, float ratio, t_camera *cam);
void			set_view(t_vec4 pos, t_vec4 target, t_vec4 vec_y, t_mat4 view);
void			new_view(t_camera *camera, float speed);
void			print_mat(char *name, t_mat4 mat);
int				tab_len(char **tab);
int				count_char(char *line, char c);
void			show_fps(double *lastime, int *nb_frame);
int				mouse_moved(t_mouse *mouse);
void			mouse_move(t_window *window, t_camera *camera);
void			set_mouse_win(t_window *window);
t_light			new_light(t_vec4 pos, t_vec4 color, float strength);
void			new_buffer(t_buffer *buf);
t_scene			new_scene(t_window *window, char *path, char *text);
int				parse_obj_file(char *path, t_object *object);
int				new_obj_texture(char *path, t_texture *obj_txt);
*/

int				init_glfw();

int				error(std::string msg);

void			framebuffer_size_callback(GLFWwindow *window, int width, int height);

#endif
