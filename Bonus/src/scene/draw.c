/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:02:25 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/13 15:22:34 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static void	put_image(t_data *d, mlx_color *pixels)
{
	int			i;
	int			x;
	int			y;

	i = 0;
	y = -1;
	while (++y < d->win_info.height)
	{
		x = -1;
		while (++x < d->win_info.width)
		{
			mlx_set_image_pixel(d->mlx, d->img, x, y, pixels[i]);
			i++;
		}
	}
}

static void	set_pixel(t_data *d, t_world *w, mlx_color *pixels)
{
	int			x;
	int			y;
	double		inv_x;
	double		norm_y;
	t_ray		ray;

	y = -1;
	inv_x = 1.0 / d->win_info.width;
	while (++y < d->win_info.height)
	{
		x = -1;
		norm_y = 1.0 - (double)y / d->win_info.height;
		while (++x < d->win_info.width)
		{
			ray = get_ray(w->camera, (double)x * inv_x, norm_y);
			pixel_color(w, ray, &pixels[(y * d->win_info.width + x)]);
		}
	}
}

void	draw(t_data *d, t_world *w)
{
	set_pixel(d, w, d->pixels);
	put_image(d, d->pixels);
	mlx_clear_window(d->mlx, d->win, (mlx_color){.rgba = 0x000000FF});
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
}
