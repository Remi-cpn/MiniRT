/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 17:22:44 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/13 11:44:46 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include <stdlib.h>

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
	free_parsing(p);
	if (exit_code < 0)
		exit (EXIT_ERROR);
	exit(exit_code);
}

void	exit_prog(t_data *data, int exit_code, char *error_message)
{
	if (error_message)
		print_error(error_message);
	free(data->pixels);
	if (data->map.objects)
		free(data->map.objects);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_destroy_context(data->mlx);
	if (exit_code < 0)
		exit (EXIT_ERROR);
	exit(exit_code);
}
