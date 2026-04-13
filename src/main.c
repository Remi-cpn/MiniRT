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

static void	update(void *param)
{
	if (!update_cam((t_data *)param, 0.2))
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
	draw(&d, &d.map);
	mlx_add_loop_hook(d.mlx, update, &d);
	mlx_loop(d.mlx);
}
