/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_acc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:33:52 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/01 16:20:22 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/physics_bonus.h"
#include "../../include/world_bonus.h"
#include "../../include/minirt_bonus.h"

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

void	calc_acc_sun(t_world *w, int i)
{
	t_vec	acc;
	int		j;

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

void	calc_acc_obj(t_world *w, t_object *o, int nbr_obj, int i)
{
	int		j;
	t_vec	acc;

	j = -1;
	ft_memset(&acc, 0, sizeof(t_vec));
	while (++j < nbr_obj)
	{
		if (j == i || !o[j].physics_enabled)
			continue ;
		acc = vec_add(acc, gravity_from(
					&o[i].shape.sphere.param,
					&o[j].shape.sphere.param));
	}
	j = -1;
	while (++j < w->nb_sun)
	{
		acc = vec_add(acc, gravity_from(
					&o[i].shape.sphere.param,
					&w->suns[j].param));
	}
	vec_init(&o[i].shape.sphere.param.acc, acc.x, acc.y, acc.z);
}
