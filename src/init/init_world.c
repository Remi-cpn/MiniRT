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
#include <stdlib.h>

static t_camera	*init_cam(double ratio, double fov, double focal)
{
	t_camera	*cam;

	if (ratio <= 0 || fov == 0 || focal == 0)
		return (NULL);
	cam = malloc(sizeof(t_camera));
	ft_memset(cam, 0, sizeof(t_camera));
	cam->fov = fov;
	vec_init(&cam->origin, 0, 0, -5);
	vec_init(&cam->hor, fov * ratio, 0, 0);
	vec_init(&cam->ver, 0, fov, 0);
	vec_init(&cam->corner, 0 - cam->hor.x / 2, 0 - cam->ver.y / 2, -focal);
	return (cam);
}

t_world	init_world(t_data *d)
{
	t_world	w;

	(void)d;
	ft_memset(&w, 0, sizeof(t_world));
	d->map.ambient_ratio = (double)d->win_info.width / (double)d->win_info.height;
	d->pixels = ft_calloc(d->win_info.width * d->win_info.height, sizeof(mlx_color));
	if (!d->pixels)
	{
		d->pixels = NULL;
		exit_prog(d, ERROR_MALLOC, ERROR_MALLOC_MSG);
	}
	init_cam(d->map.ambient_ratio, 2.0, 1.0);
	w.nb_obj = 1;
	w.objects = ft_calloc(sizeof(t_object), w.nb_obj);
	if (!w.objects)
	{
		w.objects = NULL;
		exit_prog(d, ERROR_MALLOC, ERROR_MALLOC_MSG);
	}
	w.objects[0].color.rgba = 0xFF0000FF;
	w.objects[0].type = OBJ_SPHERE;
	vec_init(&(w.objects[0]).shape.sphere.center, 0, 0, 0);
	w.objects[0].shape.sphere.radius = 0.5;
	w.objects[1].color.rgba = 0x00FF00FF;
	w.objects[1].type = OBJ_PLANE;
	vec_init(&w.objects[1].shape.plane.point, 0, -2, 0);
	vec_init(&w.objects[1].shape.plane.normal, 0, 1, 0);
	w.ambient.rgba = 0xFFFFFFFF;
	w.ambient_ratio = 0.2;
	w.lights.intensity = 0.8;
	vec_init(&w.lights.position, 3, 3, 0);
	w.lights.color.rgba = 0xFFFFFFFF;
	return (w);
}

