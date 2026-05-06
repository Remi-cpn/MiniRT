/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 17:22:44 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/06 09:58:35 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"
#include <stdlib.h>

static void	destroy_pool(t_data *d)
{
	int	i;

	if (d->pool.mutex_ready)
	{
		pthread_mutex_lock(&d->pool.queue);
		d->pool.stop = true;
		if (d->pool.cond_ready)
			pthread_cond_broadcast(&d->pool.cond);
		pthread_mutex_unlock(&d->pool.queue);
	}
	if (d->pool.cond_ready)
		pthread_cond_destroy(&d->pool.cond);
	if (d->pool.sem_ready)
		sem_destroy(&d->pool.sem);
	i = -1;
	while (++i < d->pool.nbr_threads && d->pool.threads
		&& d->pool.threads[i])
		pthread_join(d->pool.threads[i], NULL);
	if (d->pool.mutex_ready)
		pthread_mutex_destroy(&d->pool.queue);
	free(d->pool.threads);
}

void	exit_prog_pars(t_parsing *p, int exit_code, char *error_message)
{
	if (error_message)
		print_error(error_message);
	if (p->world->objects)
		free_obj_and_light(p->world);
	free_parsing(p);
	if (p->data)
		exit_prog(p->data, exit_code, NULL);
	if (p->mlx)
		mlx_destroy_context(p->mlx);
	if (exit_code < 0)
		exit (EXIT_ERROR);
	exit(exit_code);
}

void	exit_prog(t_data *d, int exit_code, char *error_message)
{
	if (error_message)
		print_error(error_message);
	if (d->pixels)
		free(d->pixels);
	if (d->map.objects)
		free_obj_and_light(&(d->map));
	if (d->pool.nbr_threads)
		destroy_pool(d);
	if (d->img)
		mlx_destroy_image(d->mlx, d->img);
	if (d->win)
		mlx_destroy_window(d->mlx, d->win);
	if (d->mlx)
		mlx_destroy_context(d->mlx);
	if (exit_code < 0)
		exit (EXIT_ERROR);
	exit(exit_code);
}
