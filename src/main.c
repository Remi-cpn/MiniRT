/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:34:44 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/09 09:01:52 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"
#include "../MacroLibX/includes/mlx.h"

void	update(void *param)
{
	draw((t_data *)param, &((t_data *)param)->world);
}

void	window_hook(int event, void *param)
{
	if (event == CROSS)
		exit_prog(param, 0, NULL);
}

void	key_hook(int key, void *param)
{
	if (key == ESC)
		exit_prog(param, 0, NULL);
}

int	main(void)
{
	t_data	d;

	d = init_program();
	mlx_on_event(d.mlx_init, d.win, MLX_KEYDOWN, key_hook, &d);
	mlx_on_event(d.mlx_init, d.win, MLX_WINDOW_EVENT, window_hook, &d);
	mlx_add_loop_hook(d.mlx_init, update, &d);
	mlx_loop(d.mlx_init);
}
