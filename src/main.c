/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:34:44 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/11 16:15:54 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"
#include "../MacroLibX/includes/mlx.h"

static bool	moove_cam(t_data *d, double speed_move)
{
	if (d->input.a == true)
		d->map.camera.origin.x -= speed_move;
	else if (d->input.d == true)
		d->map.camera.origin.x += speed_move;
	else if (d->input.w == true)
		d->map.camera.origin.z += speed_move;
	else if (d->input.s == true)
		d->map.camera.origin.z -= speed_move;
	else if (d->input.up == true)
		d->map.camera.origin.y += speed_move;
	else if (d->input.down == true)
		d->map.camera.origin.y -= speed_move;
	else
		return (0);
	return (1);
}

void	update(void *param)
{
	if (!moove_cam((t_data *)param, 0.2))
		return ;
	draw((t_data *)param, &((t_data *)param)->map);
}

int	main(int ac, char **av)
{
	t_data	d;

	if (ac != 2)
		return (1);
	d = init_program();
	d.map = parsing(&d, av[1]);
	mlx_on_event(d.mlx, d.win, MLX_KEYDOWN, key_hook_down, &d);
	mlx_on_event(d.mlx, d.win, MLX_KEYUP, key_hook_up, &d);
	mlx_on_event(d.mlx, d.win, MLX_WINDOW_EVENT, window_hook, &d);
	mlx_on_event(d.mlx, d.win, MLX_MOUSEDOWN, mouse_hook, &d);
	mlx_on_event(d.mlx, d.win, MLX_MOUSEWHEEL, mouse_hook_wheel, &d);
	draw(&d, &d.map);
	mlx_add_loop_hook(d.mlx, update, &d);
	mlx_loop(d.mlx);
}
