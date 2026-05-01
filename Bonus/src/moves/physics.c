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
#include <stdlib.h>

/* verlet : new_pos = (2 * cur) - prev + acc*dt^2*/
static void	calc_new_pos(t_vec *cur_pos, t_vec *prev_pos, t_physics *param)
{
	t_vec	tmp_pos;
	t_vec	new_pos;
	t_vec	term1;
	t_vec	term3;

	vec_init(&tmp_pos, cur_pos->x, cur_pos->y, cur_pos->z);
	term1 = vec_mult_scalar(tmp_pos, 2.0);
	term3 = vec_mult_scalar(param->acc, DT * DT);
	new_pos = vec_add(vec_sub(term1, *prev_pos), term3);
	vec_init(cur_pos, new_pos.x, new_pos.y, new_pos.z);
	vec_init(prev_pos, tmp_pos.x, tmp_pos.y, tmp_pos.z);
}

static void	apply_pair_force(t_object *o, int i, int j, t_vec *acc_tot)
{
	t_vec	dir;
	double	dist;
	double	f_i;
	double	f_j;

	dir = vec_sub(o[j].shape.sphere.param.cur_pos,
			o[i].shape.sphere.param.cur_pos);
	dist = vec_norm(dir);
	if (dist < 0.001)
		return ;
	vec_normalize(&dir);
	dist = dist * dist;
	f_i = _G * o[j].shape.sphere.param.mass / dist;
	f_j = _G * o[i].shape.sphere.param.mass / dist;
	acc_tot[i] = vec_add(acc_tot[i], vec_mult_scalar(dir, f_i));
	acc_tot[j] = vec_add(acc_tot[j], vec_mult_scalar(dir, -f_j));
}

void	calc_acc(t_object *o, int nb_obj)
{
	int			i;
	int			j;
	t_vec		*acc_tot;

	acc_tot = ft_calloc(sizeof(t_vec), nb_obj);
	i = -1;
	while (++i < nb_obj)
	{
		if (o[i].physics_enabled == false)
			continue ;
		j = i;
		while (++j < nb_obj)
			if (o[j].physics_enabled == true)
				apply_pair_force(o, i, j, acc_tot);
		vec_init(&o[i].shape.sphere.param.acc, acc_tot[i].x,
			acc_tot[i].y, acc_tot[i].z);
	}
	free(acc_tot);
}

void	recalcul_physics(t_world *w)
{
	int			i;
	t_physics	*p;

	i = -1;
	calc_acc(w->objects, w->nb_obj);
	while (++i < w->nb_obj)
	{
		if (w->objects[i].physics_enabled)
		{
			p = &w->objects[i].shape.sphere.param;
			calc_new_pos(&p->cur_pos, &p->prev_pos, p);
		}
	}
	i = -1;
	while (++i < w->nb_obj)
	{
		if (w->objects[i].physics_enabled)
			w->objects[i].shape.sphere.center
				= w->objects[i].shape.sphere.param.cur_pos;
	}
}
