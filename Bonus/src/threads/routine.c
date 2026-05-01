/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 15:11:14 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/01 08:54:18 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	render_tile(t_data *d, t_world *w, int x, int y)
{
	const int	x_max = x + TILE_SIZE;
	const int	y_max = y + TILE_SIZE;
	double		inv_x;
	double		norm_y;
	t_ray		ray;

	inv_x = 1.0 / d->win_info.width;
	while (y < d->win_info.height && y < y_max)
	{
		x = x_max - TILE_SIZE;
		norm_y = 1.0 - (double)y / d->win_info.height;
		while (x < d->win_info.width && x < x_max)
		{
			ray = get_ray(w->camera, (double)x * inv_x, norm_y);
			pixel_color(w, ray, &d->pixels[(y * d->win_info.width + x)]);
			x++;
		}
		y++;
	}
}

void	*routine(void *params)
{
	t_data	*d;
	int		y;
	int		x;
	int		idx;
	int		tile_per_row;

	d = (t_data *)params;
	pthread_mutex_lock(&d->pool.queue);
	while (d->pool.stop == false)
	{
		while ((!d->pool.start
				|| d->pool.index_tile >= d->pool.nbr_tiles)
			&& !d->pool.stop)
			pthread_cond_wait(&d->pool.cond, &d->pool.queue);
		if (d->pool.stop)
			break ;
		idx = d->pool.index_tile;
		d->pool.index_tile++;
		tile_per_row = (d->win_info.width + TILE_SIZE - 1) / TILE_SIZE;
		x = (idx % tile_per_row) * TILE_SIZE;
		y = (idx / tile_per_row) * TILE_SIZE;
		pthread_mutex_unlock(&d->pool.queue);
		render_tile(d, &d->map, x, y);
		sem_post(&d->pool.sem);
		pthread_mutex_lock(&d->pool.queue);
	}
	pthread_mutex_unlock(&d->pool.queue);
	return (NULL);
}
