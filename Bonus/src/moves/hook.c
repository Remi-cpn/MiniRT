/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:32:17 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/13 16:03:36 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	window_hook(int event, void *param)
{
	if (event == CROSS)
		exit_prog((t_data *)param, 0, NULL);
}

static void	hook_wasd(int key, void *param, bool up_down)
{
	if (key == A)
		((t_data *)param)->input.a = up_down;
	else if (key == D)
		((t_data *)param)->input.d = up_down;
	else if (key == W)
		((t_data *)param)->input.w = up_down;
	else if (key == S)
		((t_data *)param)->input.s = up_down;
}

void	key_hook_up(int key, void *param)
{
	if (key == A || key == S || key == D || key == W)
		hook_wasd(key, param, false);
	else if (key == UP)
		((t_data *)param)->input.up = false;
	else if (key == DOWN)
		((t_data *)param)->input.down = false;
	else if (key == LEFT)
		((t_data *)param)->input.left = false;
	else if (key == RIGHT)
		((t_data *)param)->input.right = false;
	else if (key == I)
		((t_data *)param)->input.i = false;
	else if (key == O)
		((t_data *)param)->input.o = false;
	else if (key == LCTRL)
		((t_data *)param)->input.ctrl = false;
	else if (key == SPACE)
		((t_data *)param)->input.space = false;
	else if (key == _R)
		((t_data *)param)->input.r = false;
}

void	key_hook_down(int key, void *param)
{
	if (key == ESC)
		exit_prog((t_data *)param, 0, NULL);
	else if (key == A || key == S || key == D || key == W)
		hook_wasd(key, param, true);
	else if (key == UP)
		((t_data *)param)->input.up = true;
	else if (key == DOWN)
		((t_data *)param)->input.down = true;
	else if (key == LEFT)
		((t_data *)param)->input.left = true;
	else if (key == RIGHT)
		((t_data *)param)->input.right = true;
	else if (key == I)
		((t_data *)param)->input.i = true;
	else if (key == O)
		((t_data *)param)->input.o = true;
	else if (key == LCTRL)
		((t_data *)param)->input.ctrl = true;
	else if (key == SPACE)
		((t_data *)param)->input.space = true;
	else if (key == _R)
		((t_data *)param)->input.r = true;
}
