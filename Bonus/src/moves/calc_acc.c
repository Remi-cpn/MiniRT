/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:33:52 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/23 12:35:25 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/physics.h"
#include "../../include/world.h"
#include "../../include/minirt.h"

static t_vec	gravity_from(t_physics *dst, t_physics *src)
{
	t_vec	dir;
	t_vec	acc;
	double	dist;

	dir = vec_sub(src->cur_pos, dst->cur_pos);
	dist = vec_norm(dir);
	if (dist < 0.001)
		return ((t_vec){0, 0, 0});
	vec_normalize(&dir);
	acc = vec_mult_scalar(dir, _G * src->mass / (dist * dist));
	return (acc);
}

static void	calc_acc_obj(t_world *w)
{
	t_vec	acc;
	int		i;
	int		j;

	i = -1;
	while (++i < w->nb_obj)
	{
		if (!w->objects[i].physics_enabled)
			continue ;
		vec_init(&acc, 0, 0, 0);
		j = -1;
		while (++j < w->nb_obj)
			if (j != i && w->objects[j].physics_enabled)
				acc = vec_add(acc, gravity_from(
							&w->objects[i].shape.sphere.param,
							&w->objects[j].shape.sphere.param));
		j = -1;
		while (++j < w->nb_sun)
			acc = vec_add(acc, gravity_from(
						&w->objects[i].shape.sphere.param,
						&w->suns[j].param));
		w->objects[i].shape.sphere.param.acc = acc;
	}

}

static void	calc_acc_sol(t_world *w)
{
	t_vec	acc;
	int		i;
	int		j;

	i = -1;
	while (++i < w->nb_sun)
	{
		vec_init(&acc, 0, 0, 0);
		j = -1;
		while (++j < w->nb_sun)
			if (j != i)
				acc = vec_add(acc, gravity_from(
							&w->suns[i].param,
							&w->suns[j].param));
		j = -1;
		while (++j < w->nb_obj)
			if (w->objects[j].physics_enabled)
				acc = vec_add(acc, gravity_from(
							&w->suns[i].param,
							&w->objects[j].shape.sphere.param));
		w->suns[i].param.acc = acc;
	}
}

void	calc_acc(t_world *w)
{
	calc_acc_obj(w);
	calc_acc_sol(w);
}
