/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 17:22:44 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/22 20:05:18 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include <stdlib.h>

static void	free_obj(t_world *w)
{
	int	i;

	i = 0;
	while (i < w->nb_obj)
	{
		if (w->objects[i].texture.img.pixels)
			free(w->objects[i].texture.img.pixels);
		i++;
	}
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
		free_obj(p->world);
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
		free_obj(&(d->map));
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
