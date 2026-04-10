/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 17:15:57 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/09 14:56:39 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
static t_input	init_input(void)
{
	t_input	i;
	
	ft_memset(&i, 0, sizeof(t_input));
	return (i);
}

static mlx_window_create_info	init_window_info(void)
{
	mlx_window_create_info	win_info;

	ft_memset(&win_info, 0, sizeof(mlx_window_create_info));
	win_info.title = "MiniRT";
	win_info.width = 800;
	win_info.height = 600;
	return (win_info);
}

static void	init_mlx(t_data *d)
{
	d->mlx_init = mlx_init();
	if (!d->mlx_init)
		exit_prog(d, ERROR_MLX_INIT, ERROR_MLX_INIT_MSG);
	d->win_info = init_window_info();
	d->win = mlx_new_window(d->mlx_init, &d->win_info);
	if (!d->win)
		exit_prog(d, ERROR_MLX_WINDOW, ERROR_MLX_WINDOW_MSG);
	d->img = mlx_new_image(d->mlx_init, d->win_info.width, d->win_info.height);
	if (!d->img)
		exit_prog(d, ERROR_MLX_WINDOW, "mlx_new_image failed");
}

t_data	init_program(void)
{
	t_data	d;

	ft_memset(&d, 0, sizeof(t_data));
	init_mlx(&d);
	d.world = init_world(&d);
	d.input = init_input();
	return (d);
}
