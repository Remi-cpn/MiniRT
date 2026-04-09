/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:34:44 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/09 15:06:42 by rcompain         ###   ########.fr       */
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
		exit_prog((t_data *)param, 0, NULL);
}

void	key_hook_up(int key, void *param)
{
	//ft_printf("Key pressed: %d\n", key);
	if (key == A)
		((t_data *)param)->imput.a = false;
	if (key == D)
		((t_data *)param)->imput.d = false;
	if (key == W)
		((t_data *)param)->imput.w = false;
	if (key == S)
		((t_data *)param)->imput.s = false;
	if (key == UP)
		((t_data *)param)->imput.up = false;
	if (key == DOWN)
		((t_data *)param)->imput.down = false;
	//printf("cam x: %f\n", ((t_data *)param)->world.cam.pos.x);
}

void	key_hook_down(int key, void *param)
{
	//ft_printf("Key pressed: %d\n", key);
	if (key == ESC)
		exit_prog((t_data *)param, 0, NULL);
	if (key == A)
		((t_data *)param)->imput.a = true;
	if (key == D)
		((t_data *)param)->imput.d = true;
	if (key == W)
		((t_data *)param)->imput.w = true;
	if (key == S)
		((t_data *)param)->imput.s = true;
	if (key == UP)
		((t_data *)param)->imput.up = true;
	if (key == DOWN)
		((t_data *)param)->imput.down = true;
	//printf("cam x: %f\n", ((t_data *)param)->world.cam.pos.x);
}

int	main(void)
{
	t_data	d;

	d = init_program();
	mlx_on_event(d.mlx_init, d.win, MLX_KEYDOWN, key_hook_down, &d);
	mlx_on_event(d.mlx_init, d.win, MLX_KEYUP, key_hook_up, &d);
	mlx_on_event(d.mlx_init, d.win, MLX_WINDOW_EVENT, window_hook, &d);
	mlx_add_loop_hook(d.mlx_init, update, &d);
	mlx_loop(d.mlx_init);
}
