/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 17:01:39 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/12/04 15:50:56 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

const GLchar	*get_source_from_file(char const *path_shader)
{
	char	*source;
	char	*to_del;
	char	buffer[BUFFER_SIZE];
	int		ret;
	int		fd;

	if ((fd = open(path_shader, O_RDONLY)) == -1)
	{
		printf("Error open shader source file.\n");
		return (NULL);
	}
	source = ft_strnew(BUFFER_SIZE);
	while ((ret = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[ret] = '\0';
		to_del = source;
		source = ft_strjoin(source, buffer);
		ft_strdel(&to_del);
	}
	close(fd);
	return (source);
}

unsigned int	new_shader_program(GLuint vertex, GLuint fragment)
{
	unsigned int	shader_program;
	int				success;
	char			infolog[512];

	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex);
	glAttachShader(shader_program, fragment);
	glLinkProgram(shader_program);
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		printf("ERROR::SHADER::PROGRAM_FAILED\n");
		glGetProgramInfoLog(shader_program, 512, NULL, infolog);
		printf("%s\n", infolog);
	}
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	return (shader_program);
}

GLuint			load_shader(char const *path_shader, int shader_type)
{
	GLuint			shader_id;
	int				success;
	const GLchar	*source;
	char			infolog[512];

	shader_id = glCreateShader(shader_type);
	source = get_source_from_file(path_shader);
	glShaderSource(shader_id, 1, &source, NULL);
	glCompileShader(shader_id);
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader_id, 512, NULL, infolog);
		printf("ERROR::SHADER::COMPILATION_FAILED\n");
		printf("%s\n", infolog);
	}
	return (shader_id);
}

int				new_shader(t_shader *shader, char *pathv, char *pathf)
{
	shader->v_shader_id = load_shader(pathv, GL_VERTEX_SHADER);
	shader->f_shader_id = load_shader(pathf, GL_FRAGMENT_SHADER);
	shader->shader_program = new_shader_program(shader->v_shader_id,
			shader->f_shader_id);
	return (1);
}
