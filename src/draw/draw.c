/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:02:25 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/09 15:04:15 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static void	pos_cam(t_data *d)
{
	if (d->imput.a == true)
		d->world.cam.pos.x += 0.5;
	if (d->imput.d == true)
		d->world.cam.pos.x -= 0.5;
	if (d->imput.w == true)
		d->world.cam.pos.z += 0.5;
	if (d->imput.s == true)
		d->world.cam.pos.z -= 0.5;
	if (d->imput.up == true)
		d->world.cam.pos.y += 0.5;
	if (d->imput.down == true)
		d->world.cam.pos.y -= 0.5;
}

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
			mlx_set_image_pixel(d->mlx_init, d->img, x, y, pixels[i]);
			i++;
		}
	}
}

static void	set_pixel(t_data *d, t_world *w, mlx_color *pixels)
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
			if (hit_sphere(w, pixel_ray(w, d, x, y)))
				pixels[i].rgba = 0xFF0000FF;
			else
				pixels[i].rgba = 0x000000FF;
			i++;
		}
	}
}

void	draw(t_data *d, t_world *w)
{
	mlx_color	*pixels;

	pixels = ft_calloc(d->win_info.width * d->win_info.height, sizeof(mlx_color));
	if (!pixels)
		return ;
	pos_cam(d);
	set_pixel(d, w, pixels);
	put_image(d, pixels);
	mlx_clear_window(d->mlx_init, d->win, (mlx_color){.rgba = 0x000000FF});
	mlx_put_image_to_window(d->mlx_init, d->win, d->img, 0, 0);
	free(pixels);
}
