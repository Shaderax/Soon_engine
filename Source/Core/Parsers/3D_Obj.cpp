#if 1 == 1
# if 1 == 1
#  if 1 == 1
#   if 1 == 1
#    if 1 == 1
#     if 1 == 1
#      if 1 == 1
#       if 1 == 1
#        if 1 == 1
#         if 1 == 1
#          if 1 == 1
#           if 1 == 1
#            if 1 == 1
#             if 1 == 1
#              if 1 == 1
#               if 1 == 1
#                if 1 == 1
#                 if 1 == 1
#                  if 1 == 1
#                  // include "scop.h"
#                  endif
#                 endif
#                endif
#               endif
#              endif
#             endif
#            endif
#           endif
#          endif
#         endif
#        endif
#       endif
#      endif
#     endif
#    endif
#   endif
#  endif
# endif
#endif

void	normal_tab(t_object *obj)
{
	t_buffer *v;
	t_buffer *t;
	t_buffer *n;

	v = &obj->vertex_array;
	t = &obj->texture_coord;
	n = &obj->normal_array;
	v->array = realloc(v->array, v->size * sizeof(float));
	n->array = realloc(n->array, n->size * sizeof(float));
	t->array = realloc(t->array, t->size * sizeof(float));
}

void	fill_array_vertice(char **split, t_buffer *buffer)
{
	int index;

	index = 0;
	while (++index < 4)
	{
		if (!(buffer->size % BSIZE))
			buffer->array = realloc(buffer->array, SIZE_ALLOC(buffer->size)
					* sizeof(float));
		buffer->array[buffer->size] = split[index] ?
			(float)(atof(split[index])) : 0;
		if (buffer->array[buffer->size] < buffer->min[index - 1])
			buffer->min[index - 1] = buffer->array[buffer->size];
		if (buffer->array[buffer->size] < buffer->max[index - 1])
			buffer->max[index - 1] = buffer->array[buffer->size];
		buffer->size += 1;
		free(split[index]);
	}
}

void	str_to_tab(char *line, int *tab)
{
	int x;
	int index;
	int nb_shash;

	nb_shash = count_char(line, '/');
	x = -1;
	index = 0;
	while (line[x++] != '\0')
	{
		if (ft_isdigit(line[x]))
		{
			tab[index] = atoi(line + x);
			while (line[++x] && ft_isdigit(line[x]))
				;
			if (line[x] == ' ' && nb_shash == 3)
				index += 2;
			if (line[x] == ' ' && nb_shash == 4)
				index += 2;
			else if (line[x] == ' ' && !nb_shash)
				index += 3;
			else if (line[x] == ' ' && nb_shash)
				index++;
		}
		if (line[x] == '/')
			++index;
	}
}

void	fill_array_indice(t_buffer *tmp, t_buffer *fill, int *tab, int limit, int ar)
{
	int index;
	int index2;
	int prout;

	if (!tab[ar])
		return ;
	limit = limit == 3 ? 3 : 6;
	index = -1;
	while (++index < 3)
	{
		index2 = -1;
		int caca = limit == 3 ? 3 : 12;
		while (++index2 < caca)
		{
			if (!((fill->size + index2) % BSIZE) || !fill->size)
			{
				fill->array = realloc(fill->array, SIZE_ALLOC(fill->size + index2) * sizeof(float));
				break ;
			}
		}
		prout = -1;
		while (++prout < 3)
		{
			if (limit == 3)
				fill->array[fill->size + prout] = tmp->array[(tab[index * 3 + ar] - 1) * 3 + prout];
			else if (limit == 6)
			{
				fill->array[fill->size - index * 3 + prout] = tmp->array[(tab[index * 3 + ar] - 1) * 3 + prout];
				fill->array[fill->size + 9 - index * 3 + prout] = tmp->array[(tab[(index + (index > 0 ? 1 : 0)) * 3 + ar] - 1) * 3 + prout];
			}
		}
		fill->size += limit;
	}
}

void	parse_face(char *line, t_buffer tmp[3], t_object *obj, int **tab)
{
	int len;

	len = ft_wd_count(line, ' ') - 1;
	*tab = realloc(*tab, len * 3 * sizeof(int));
	bzero(*tab, len * 3 * sizeof(int));
	str_to_tab(line + 2, *tab);
	fill_array_indice(&tmp[0], &obj->vertex_array, *tab, len, 0);
	fill_array_indice(&tmp[1], &obj->texture_coord, *tab, len, 1);
	fill_array_indice(&tmp[2], &obj->normal_array, *tab, len, 2);
}

void	push_line(char *line, t_buffer tmp[3], int **tab, t_object *obj)
{
	char		**split;

	if (line[0] == 'v' && line[1] == ' ')
	{
		split = ft_strsplit(line, ' ');
		fill_array_vertice(split, &(tmp[0]));
		free(split);
	}
	else if (line[0] == 'v' && line[1] == 'n')
	{
		split = ft_strsplit(line, ' ');
		fill_array_vertice(split, &(tmp[2]));
		free(split);
	}
	else if (line[0] == 'v' && line[1] == 't')
	{
		split = ft_strsplit(line, ' ');
		fill_array_vertice(split, &(tmp[1]));
		free(split);
	}
	else if (line[0] == 'f' && line[1] == ' ')
	{
		parse_face(line, tmp, obj, tab);
	}
}

int		parse_obj_file(char *path, 3dObj* obj)
{
	int			fd;
	char		*line;
	t_buffer	tmp[3];
	int			*tab;

	if ((fd = open(path, O_RDONLY)) < 0)
		printf("Failed Open : %s\n", path);
	else
		printf("Open : %s\n", path);
	tab = NULL;
	bzero(tmp, sizeof(t_buffer) * 3);
	while (get_next_line(fd, &line) > 0)
	{
		push_line(line, tmp, &tab, obj);
		free(line);
	}
	printf("FINI LOAD\n");
	normal_tab(obj);
	printf("FINI NORMAL\n");
	printf("%d, %d, %d\n", tmp[0].size, tmp[1].size, tmp[2].size);
	printf("v %d, n %d, t %d\n", obj->vertex_array.size, obj->normal_array.size, obj->texture_coord.size);
	printf("vertex min : %f, %f, %f\n", tmp[0].min[0], tmp[0].min[1], tmp[0].min[2]);
	printf("veretx max : %f, %f, %f\n", tmp[0].max[0], tmp[0].max[1], tmp[0].max[2]);
	return (1);
}

class ObjFile : Component
{
	void LoadObjFile(std::string path)
	{
		FILE* fp = fopen(path.c_str(), "r");
		if (fp == NULL)
			exit(-1);

		char* line = NULL;
		size_t len = 0;
		while ((getline(&line, &len, fp)) != -1)
			printf("%s", line);
			// using printf() in all tests for consistency
		fclose(fp);
		if (line)
			free(line);

	}

	std::vector< vec3 > _vertex;
	std::vector< vec3 > _normal;
	std::vector< vec3 > _vectexTexture;
}
