/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 15:11:14 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/04 15:46:57 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"

void	render_tile(t_data *d, t_world *w, int x, int y)
{
	const int	x_max = x + TILE_SIZE;
	const int	y_max = y + TILE_SIZE;
	double		u;
	double		v;
	t_ray		ray;

	while (y < d->win_info.height && y < y_max)
	{
		x = x_max - TILE_SIZE;
		v = 1.0 - (((double)y + 0.5) / (double)d->win_info.height);
		while (x < d->win_info.width && x < x_max)
		{
			u = ((double)x + 0.5) / (double)d->win_info.width;
			ray = get_ray(w->camera, u, v);
			pixel_color(w, ray, &d->pixels[(y * d->win_info.width + x)]);
			x++;
		}
		y++;
	}
}

static void	dispatch_work(t_data *d, int idx)
{
	int	tile_per_row;
	int	x;
	int	y;

	if (d->pool.mod == PHYS_ACC)
		calc_acc_obj(&d->map, d->map.objects, d->map.nb_obj, idx);
	else if (d->pool.mod == PHYS_SUN)
		calc_acc_sun(&d->map, idx);
	else if (d->pool.mod == PHYS_POS)
		recalcul_pos_obj(&d->map, idx);
	else
	{
		tile_per_row = (d->win_info.width + TILE_SIZE - 1) / TILE_SIZE;
		x = (idx % tile_per_row) * TILE_SIZE;
		y = (idx / tile_per_row) * TILE_SIZE;
		render_tile(d, &d->map, x, y);
	}
}

void	*routine(void *params)
{
	t_data	*d;
	int		idx;

	d = (t_data *)params;
	pthread_mutex_lock(&d->pool.queue);
	while (d->pool.stop == false)
	{
		while ((!d->pool.start
				|| d->pool.job_idx >= d->pool.nbr_jobs)
			&& !d->pool.stop)
			pthread_cond_wait(&d->pool.cond, &d->pool.queue);
		if (d->pool.stop)
			break ;
		idx = d->pool.job_idx;
		d->pool.job_idx++;
		pthread_mutex_unlock(&d->pool.queue);
		dispatch_work(d, idx);
		sem_post(&d->pool.sem);
		pthread_mutex_lock(&d->pool.queue);
	}
	pthread_mutex_unlock(&d->pool.queue);
	return (NULL);
}
