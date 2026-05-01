/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:33:52 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/01 14:50:19 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
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


void	calc_acc_obj(t_object *o, int nbr_obj, int i)
{
	int		j;
	t_vec	acc;
	t_vec	dir;
	double	dist;
	double	f_i;

	j = -1;
	ft_memset(&acc, 0, sizeof(t_vec));
	while (++j < nbr_obj)
	{
		if (j == i || !o[j].physics_enabled)
			continue ;
		dir = vec_sub(o[j].shape.sphere.param.cur_pos,
				o[i].shape.sphere.param.cur_pos);
		dist = vec_norm(dir);
		if (dist < 0.001)
			continue ;
		vec_normalize(&dir);
		dist = dist * dist;
		f_i = _G * o[j].shape.sphere.param.mass / dist;
		acc = vec_add(acc, vec_mult_scalar(dir, f_i));
	}
	vec_init(&o[i].shape.sphere.param.acc, acc.x, acc.y, acc.z);
}

void	calc_acc(t_object *o, int nbr_obj)
{
	int		i;

	i = -1;
	while (++i < nbr_obj)
	{
		if (o[i].physics_enabled == false)
			continue ;
		calc_acc_obj(o, nbr_obj, i);
	}
}

void	recalcul_pos_obj(t_world *w, int i)
{
	t_physics	*p;

	if (w->objects[i].physics_enabled)
	{
		p = &w->objects[i].shape.sphere.param;
		calc_new_pos(&p->cur_pos, &p->prev_pos, p);
		w->objects[i].shape.sphere.center = p->cur_pos;
	}
}

void	recalcul_physics(t_data *d, t_world *w)
{
	int	i;
	int	j;

	i = 0;
	while (i < 2)
	{
		pthread_mutex_lock(&d->pool.queue);
		d->pool.job_idx = 0;
		d->pool.start = true;
		if (i == 0)
			d->pool.mod = PHYS_ACC;
		else
			d->pool.mod = PHYS_POS;
		d->pool.nbr_jobs = w->nb_obj;
		pthread_cond_broadcast(&d->pool.cond);
		pthread_mutex_unlock(&d->pool.queue);
		j = -1;
		while (++j < d->pool.nbr_jobs)
			sem_wait(&d->pool.sem);
		i++;
	}
}
