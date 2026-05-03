/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snap_cam_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:17:52 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/03 16:54:25 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"
#include <stdbool.h>

void	follow_cam(t_data *d)
{
	t_sphere	*sp;
	t_camera	*cam;

	if (d->cam_target < 0)
		return ;
	if (d->map.objects[d->cam_target].type != OBJ_SPHERE)
		return ;
	sp = &d->map.objects[d->cam_target].shape.sphere;
	cam = &d->map.camera;
	cam->origin.x = sp->center.x + sp->radius * -2.0;
	cam->origin.y = sp->center.y ;
	cam->origin.z = sp->center.z + sp->radius * 3.0;
	cam->dir = vec_sub(sp->center, cam->origin);
	vec_normalize(&cam->dir);
	vec_init(&cam->hor_n, 0, 0, 0);
	calcul_viewport(cam, (double)d->win_info.width
		/ (double)d->win_info.height);
}

static int	find_sphere(t_world *w, int start, int dir)
{
	int	i;
	int	count;

	i = ((start % w->nb_obj) + w->nb_obj) % w->nb_obj;
	count = 0;
	while (count < w->nb_obj)
	{
		if (w->objects[i].type == OBJ_SPHERE)
			return (i);
		i = (i + dir + w->nb_obj) % w->nb_obj;
		count++;
	}
	return (-1);
}

void	snap_cam_to_planet(t_data *d, int dir)
{
	int			start;
	int			target;
	t_sphere	*sp;
	t_camera	*cam;

	start = d->map.nb_obj - 1;
	if (d->cam_target < 0 && dir > 0)
		start = 0;
	else if (d->cam_target >= 0)
		start = (d->cam_target + dir + d->map.nb_obj) % d->map.nb_obj;
	target = find_sphere(&d->map, start, dir);
	if (target == -1)
		return ;
	d->cam_target = target;
	sp = &d->map.objects[target].shape.sphere;
	cam = &d->map.camera;
	vec_init(&cam->origin, sp->center.x + sp->radius * -2.0, sp->center.y,
			sp->center.z + sp->radius * 3.0);
	cam->dir = vec_sub(sp->center, cam->origin);
	vec_normalize(&cam->dir);
	vec_init(&cam->hor_n, 0, 0, 0);
	d->input.n = false;
	d->input.p = false;
	calcul_viewport(cam, (double)d->win_info.width
		/ (double)d->win_info.height);
}
