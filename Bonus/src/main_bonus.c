/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:34:44 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/04 16:08:59 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt_bonus.h"
#include "../../MacroLibX/includes/mlx.h"

static void	update(void *param)
{
	t_data	*d;
	int		i;

	d = (t_data *)param;
	if (d->solar_file == false)
	{
		update_cam(d, 0.6, 0.1);
		draw(d);
		return ;
	}
	i = -1;
	update_cam(d, 150, 0.1);
	if (d->input.most == true && d->speed_sim < 120)
		d->speed_sim++;
	if (d->input.less == true && d->speed_sim > 0)
		d->speed_sim--;
	while (++i < d->speed_sim)
		recalcul_physics(d, &d->map);
	follow_cam(d);
	draw(d);
}

int	main(int ac, char **av)
{
	t_data	d;

	if (ac != 2 && ac != 3)
		return (1);
	d = init_program();
	d.filename = av[1];
	init_speed_sim(&d, ac, av);
	d.map = parsing(&d, av[1]);
	init_threads(&d);
	mlx_on_event(d.mlx, d.win, MLX_KEYDOWN, key_hook_down, &d);
	mlx_on_event(d.mlx, d.win, MLX_KEYUP, key_hook_up, &d);
	mlx_on_event(d.mlx, d.win, MLX_WINDOW_EVENT, window_hook, &d);
	draw(&d);
	mlx_add_loop_hook(d.mlx, update, &d);
	mlx_loop(d.mlx);
}
