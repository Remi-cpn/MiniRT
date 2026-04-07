/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 17:22:44 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/07 08:28:37 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	print_error(char *message)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
}

void	exit_prog(t_data *data, int exit_code, char *error_message)
{
	if (error_message)
		print_error(error_message);
	if (data->win)
		mlx_destroy_window(data->mlx_init, data->win);
	if (data->mlx_init)
		mlx_destroy_context(data->mlx_init);
	exit(exit_code);
}
