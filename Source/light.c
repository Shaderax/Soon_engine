/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrouzeva <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 17:30:59 by nrouzeva          #+#    #+#             */
/*   Updated: 2018/12/01 17:31:18 by nrouzeva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_light	new_light(t_vec4 pos, t_vec4 color, float strength)
{
	t_light ret;

	vec4_set(ret.pos, pos);
	vec4_set(ret.color, color);
	ret.strength = strength;
	return (ret);
}
