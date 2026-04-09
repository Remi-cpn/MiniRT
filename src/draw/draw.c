/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:02:25 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/09 09:09:51 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../MacroLibX/includes/mlx_extended.h"

/* Check if a ray hits a sphere */
/* a = dir² */
/* b = 2 * (oc · dir) */
/* c = oc² - radius² */
/* discriminant = b² - 4ac */
int	hit_sphere(t_world *w, t_ray ray)
{
	t_vec			oc;
	t_second_degret	sd;
	double			discriminant;

	sd.a = vec_dot(ray.dir, ray.dir);
	oc = vec_sub(ray.origin, w->sphere.center);
	sd.b = 2 * vec_dot(oc, ray.dir);
	sd.c = vec_dot(oc, oc) - w->sphere.radius * w->sphere.radius;
	discriminant = sd.b * sd.b - 4 * sd.a * sd.c;
	if (discriminant < 0)
		return (0);
	return (1);
}

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
	y_norm = (y_pixel - (double)d->win_info.height / 2)
		/ ((double)d->win_info.height / 2);
	z = 1 / tan(w->cam.fov / 2);
	ray.dir = (t_vec){x_norm * rasio, y_norm, z};
	return (ray);
}

void	draw(t_data *d, t_world *w)
{
	mlx_color	pixels[d->win_info.width * d->win_info.height];
	int			i;
	int			x;
	int			y;

	ft_memset(pixels, 0, sizeof(mlx_color));
	i = 0;
	y = -1;
	while (++y < d->win_info.height)
	{
		x = -1;
		while (++x < d->win_info.width)
		{
			if (hit_sphere(w, pixel_ray(w, d, x, y)))
				pixels[i].rgba = 0xFF0000FF;
			else
				pixels[i].rgba = 0xFF000000;
			i++;
		}
	}
	mlx_pixel_put_region(d->mlx_init, d->win, 0, 0,
		d->win_info.width, d->win_info.height, pixels);
}
