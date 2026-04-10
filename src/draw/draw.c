/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:02:25 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/10 09:05:28 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static void	light(t_world *w, t_vec p, mlx_color *color, t_vec normal)
{
	t_vec	light_dir;
	double	len;
	double	light_intensity;

	light_dir = vec_sub(w->light.pos, p);
	len = vec_norm(light_dir);
	light_dir = vec_mult_scalar(light_dir, 1 / len);
	light_intensity = vec_dot(normal, light_dir);
	// pas de couleur negative ca fou la merde
	if (light_intensity < 0)
    	light_intensity = 0;
	color->r = w->sphere.color.r * light_intensity;
	color->g = w->sphere.color.g * light_intensity;
	color->b = w->sphere.color.b * light_intensity;
	color->a = 255;
}

static void	pixel_color(t_world *w, t_ray ray, mlx_color *color)
{
	double	t;
	double	len;
	t_vec	p;
	t_vec	normal;

	t = hit_sphere(w, ray);
	if (t < 0)
	{
		color->rgba = 0x000000FF;
		return ;
	}
	p = vec_add(ray.origin, vec_mult_scalar(ray.dir, t));
	normal = vec_sub(p, w->sphere.center);
	len = vec_norm(normal);
	normal = vec_mult_scalar(normal, 1 / len);
	light(w, p, color, normal);
	// if (t > 0)
	// 	color->rgba = 0xFF0000FF;
}

static void	pos_cam(t_data *d, double speed_move)
{
	if (d->imput.a == true)
		d->world.cam.pos.x -= speed_move;
	if (d->imput.d == true)
		d->world.cam.pos.x += speed_move;
	if (d->imput.w == true)
		d->world.cam.pos.z += speed_move;
	if (d->imput.s == true)
		d->world.cam.pos.z -= speed_move;
	if (d->imput.up == true)
		d->world.cam.pos.y -= speed_move;
	if (d->imput.down == true)
		d->world.cam.pos.y += speed_move;
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
	t_ray		ray;

	i = 0;
	y = -1;
	while (++y < d->win_info.height)
	{
		x = -1;
		while (++x < d->win_info.width)
		{
			ray = pixel_ray(w, d, x, y);
			pixel_color(w, ray, &pixels[i]);
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
	pos_cam(d, 0.2);
	set_pixel(d, w, pixels);
	put_image(d, pixels);
	mlx_clear_window(d->mlx_init, d->win, (mlx_color){.rgba = 0x000000FF});
	mlx_put_image_to_window(d->mlx_init, d->win, d->img, 0, 0);
	free(pixels);
}
