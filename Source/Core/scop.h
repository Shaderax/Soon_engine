/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 19:39:06 by nrouzeva          #+#    #+#             */
/*   Updated: 2019/02/15 18:38:26 by nrouzeva         ###   ########.fr       */
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

#endif
