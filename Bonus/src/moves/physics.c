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

/* verlet : new_pos = (2 * cur) - prev + acc*dt^2 */
static void	calc_new_pos(t_vec *cur_pos, t_vec *prev_pos, t_physics *param)
{
	t_vec	tmp_pos;
	t_vec	new_pos;

	vec_init(&tmp_pos, cur_pos->x, cur_pos->y, cur_pos->z);
	new_pos = vec_add(
			vec_sub(vec_mult_scalar(tmp_pos, 2.0), *prev_pos),
			vec_mult_scalar(param->acc, DT * DT));
	vec_init(cur_pos, new_pos.x, new_pos.y, new_pos.z);
	vec_init(prev_pos, tmp_pos.x, tmp_pos.y, tmp_pos.z);
}

void	recalcul_physics(t_world *w)
{
	t_physics	*p;
	int			i;

	calc_acc(w);
	i = -1;
	while (++i < w->nb_obj)
	{
		if (w->objects[i].physics_enabled)
		{
			p = &w->objects[i].shape.sphere.param;
			calc_new_pos(&p->cur_pos, &p->prev_pos, p);
			w->objects[i].shape.sphere.center = p->cur_pos;
		}
	}
	i = -1;
	while (++i < w->nb_sun)
	{
		p = &w->suns[i].param;
		calc_new_pos(&p->cur_pos, &p->prev_pos, p);
	}
}
