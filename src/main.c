/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:34:44 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/09 15:35:01 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"
#include "../MacroLibX/includes/mlx.h"

void	update(void *param)
{
	draw((t_data *)param, &((t_data *)param)->world);
}

int	main(void)
{
	t_data	d;

	d = init_program();
	mlx_on_event(d.mlx_init, d.win, MLX_KEYDOWN, key_hook_down, &d);
	mlx_on_event(d.mlx_init, d.win, MLX_KEYUP, key_hook_up, &d);
	mlx_on_event(d.mlx_init, d.win, MLX_WINDOW_EVENT, window_hook, &d);
	mlx_on_event(d.mlx_init, d.win, MLX_MOUSEDOWN, mouse_hook, NULL);
    mlx_on_event(d.mlx_init, d.win, MLX_MOUSEWHEEL, mouse_hook_wheel, NULL);
	mlx_add_loop_hook(d.mlx_init, update, &d);
	mlx_loop(d.mlx_init);
}
