/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:32:17 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/09 17:00:01 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"
#include "../MacroLibX/includes/mlx.h"

void	mouse_hook_wheel(int event, void *param)
{
	if (event == 1)
		((t_data *)param)->map.camera.fov -= 0.01;
	if (event == 2)
		((t_data *)param)->map.camera.fov += 0.01;
}

void	mouse_hook(int event, void *param)
{
	(void)event;
	(void)param;
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
		((t_data *)param)->input.a = false;
	if (key == D)
		((t_data *)param)->input.d = false;
	if (key == W)
		((t_data *)param)->input.w = false;
	if (key == S)
		((t_data *)param)->input.s = false;
	if (key == UP)
		((t_data *)param)->input.up = false;
	if (key == DOWN)
		((t_data *)param)->input.down = false;
	//printf("cam x: %f\n", ((t_data *)param)->world.cam.pos.x);
}

void	key_hook_down(int key, void *param)
{
	//ft_printf("Key pressed: %d\n", key);
	if (key == ESC)
		exit_prog((t_data *)param, 0, NULL);
	if (key == A)
		((t_data *)param)->input.a = true;
	if (key == D)
		((t_data *)param)->input.d = true;
	if (key == W)
		((t_data *)param)->input.w = true;
	if (key == S)
		((t_data *)param)->input.s = true;
	if (key == UP)
		((t_data *)param)->input.up = true;
	if (key == DOWN)
		((t_data *)param)->input.down = true;
	//printf("cam x: %f\n", ((t_data *)param)->world.cam.pos.x);
}
