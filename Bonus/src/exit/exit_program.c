/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 17:22:44 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/01 16:55:16 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
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

static void	free_obj_and_light(t_world *w)
{
	int	i;

	i = 0;
	while (i < w->nb_obj)
	{
		if (w->objects[i].texture.img.pixels)
			free(w->objects[i].texture.img.pixels);
		if (w->objects[i].texture.bump_map.pixels)
			free(w->objects[i].texture.bump_map.pixels);
		i++;
	}
	if (w->lights)
		free(w->lights);
	if (w->suns)
		free(w->suns);
	free(w->objects);
}

void	print_error(char *message)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}

void	free_parsing(t_parsing *p)
{
	if (p->line)
	{
		while (p->line)
		{
			p->line = ft_freenull(p->line);
			p->line = ft_get_next_line(p->fd);
		}
		close(p->fd);
	}
	if (p->line_split)
		ft_free_array(p->line_split);
}

void	exit_prog_pars(t_parsing *p, int exit_code, char *error_message)
{
	if (error_message)
		print_error(error_message);
	if (p->world->objects)
		free_obj_and_light(p->world);
	free_parsing(p);
	if (p->data)
	{
		exit_prog(p->data, exit_code, NULL);
		return ;
	}
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
