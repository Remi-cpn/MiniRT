/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:02:25 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/08 20:51:23 by rcompain         ###   ########.fr       */
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

	ray.origin = w->cam.pos;
	x_norm = (x_pixel - (double)d->win_info.width / 2)
		/ ((double)d->win_info.width / 2);
	y_norm = (y_pixel - (double)d->win_info.height / 2)
		/ ((double)d->win_info.height / 2);
	z = 1 / tan(w->cam.fov / 2);
	ray.dir = (t_vec){x_norm, y_norm, z};
	return (ray);
}

void	draw(t_data *data, t_world *world)
{
	(void)data;
	(void)world;
}
