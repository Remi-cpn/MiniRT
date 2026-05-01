/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:02:25 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/28 18:34:18 by rcompain         ###   ########.fr       */
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

void	draw(t_data *d)
{
	int	i;

	pthread_mutex_lock(&d->pool.queue);
	d->pool.index_tile = 0;
	d->pool.start = true;
	pthread_cond_broadcast(&d->pool.cond);
	pthread_mutex_unlock(&d->pool.queue);
	i = -1;
	while (++i < d->pool.nbr_tiles)
		sem_wait(&d->pool.sem);
	put_image(d, d->pixels);
	mlx_clear_window(d->mlx, d->win, (mlx_color){.rgba = 0x000000FF});
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
}
