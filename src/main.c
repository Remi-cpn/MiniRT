/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:34:44 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/10 15:17:26 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"
#include "../MacroLibX/includes/mlx.h"

void	update(void *param)
{
	draw((t_data *)param, &((t_data *)param)->world);
}

int	main(int ac, char **av)
{
	t_data	d;

	if (ac != 2)
		return (1);
	d = init_program();
	mlx_on_event(d.mlx, d.win, MLX_KEYDOWN, key_hook_down, &d);
	mlx_on_event(d.mlx, d.win, MLX_KEYUP, key_hook_up, &d);
	mlx_on_event(d.mlx, d.win, MLX_WINDOW_EVENT, window_hook, &d);
	mlx_on_event(d.mlx, d.win, MLX_MOUSEDOWN, mouse_hook, &d);
    mlx_on_event(d.mlx, d.win, MLX_MOUSEWHEEL, mouse_hook_wheel, &d);
	mlx_add_loop_hook(d.mlx, update, &d);
	mlx_loop(d.mlx);
}
