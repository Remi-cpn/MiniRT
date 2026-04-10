/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 08:42:27 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/10 10:23:51 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static t_camera	*init_cam(double ratio, double fov, double focal)
{
	t_camera	*cam;

	if (ratio <= 0 || fov == 0 || focal == 0)
		return (NULL);
	cam = malloc(sizeof(t_camera));
	ft_memset(cam, 0, sizeof(t_camera));
	cam->fov = fov;
	vec_init(&cam->origin, 0, 0, 0);
	vec_init(&cam->hor, fov * ratio, 0, 0);
	vec_init(&cam->ver, 0, fov, 0);
	vec_init(&cam->corner, 0 - cam->hor.x / 2, 0 - cam->ver.y / 2, focal);
	return (cam);
}

t_world	init_world(t_data *d)
{
	t_world	w;

	(void)d;
	ft_memset(&w, 0, sizeof(t_world));
	d->map.ambient_ratio = (double)d->win_info.width / (double)d->win_info.height;
	init_cam(d->map.ambient_ratio, 2.0, 1.0);
	return (w);
}

