/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:15:33 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/10 10:09:36 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Create a ray for a pixel */
/* Formule: norm x and y = (pixel_position - width / 2) / (half_width / 2) */
t_ray	pixel_ray(t_world *w, t_data *d, int x_pixel, int y_pixel)
{
	t_ray	ray;
	double	z;
	double	x_norm;
	double	y_norm;
	double	rasio;

	ray.origin = w->cam.pos;
	rasio = (double)d->win_info.width / (double)d->win_info.height;
	x_norm = (x_pixel - (double)d->win_info.width / 2)
		/ ((double)d->win_info.width / 2);
	// J'ai du inverser le y pour que ca soit dans le bon sens...
	y_norm = ((y_pixel - (double)d->win_info.height / 2)
		/ ((double)d->win_info.height / 2)) * -1;
	z = 1 / tan(w->cam.fov / 2);
	ray.dir = (t_vec){x_norm * rasio, y_norm, z};
	return (ray);
}
