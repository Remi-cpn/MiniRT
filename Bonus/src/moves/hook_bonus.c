/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:32:17 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/04 10:38:42 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"

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

static void	hook_arrow(int key, void *param, bool up_down)
{
	if (key == UP)
		((t_data *)param)->input.up = up_down;
	else if (key == DOWN)
		((t_data *)param)->input.down = up_down;
	else if (key == LEFT)
		((t_data *)param)->input.left = up_down;
	else if (key == RIGHT)
		((t_data *)param)->input.right = up_down;
}

void	key_hook_up(int key, void *param)
{
	if (key == A || key == S || key == D || key == W)
		hook_wasd(key, param, false);
	else if (key == UP || key == DOWN || key == LEFT || key == RIGHT)
		hook_arrow(key, param, false);
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
	else if (key == LESS)
		((t_data *)param)->input.less = false;
	else if (key == MOST)
		((t_data *)param)->input.most = false;
}

void	key_hook_down(int key, void *param)
{
	if (key == ESC)
		exit_prog((t_data *)param, 0, NULL);
	else if (key == A || key == S || key == D || key == W)
		hook_wasd(key, param, true);
	else if (key == UP || key == DOWN || key == LEFT || key == RIGHT)
		hook_arrow(key, param, true);
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
	else if (key == N)
		((t_data *)param)->input.n = true;
	else if (key == P)
		((t_data *)param)->input.p = true;
	else if (key == LESS)
		((t_data *)param)->input.less = true;
	else if (key == MOST)
		((t_data *)param)->input.most = true;
}
