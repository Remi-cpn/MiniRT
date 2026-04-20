/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:34:44 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/15 15:29:28 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"
#include "../../MacroLibX/includes/mlx.h"

static void	update(void *param)
{
	t_data *d;

	d = (t_data *)param;
	update_cam(d, 0.3);
	for (int i = 0; i < 60; i++)
		recalcul_physics(&d->map);
	draw(d, &d->map);
}

int	main(int ac, char **av)
{
	t_data	d;

	if (ac != 2)
		return (1);
	d = init_program();
	d.filename = av[1];
	d.map = parsing(&d, av[1]);
	// Après avoir parsé le fichier .rtt
	// printf("=== DEBUG PHYSIQUE ===\n");
	// for (int i = 0; i < d.map.nb_obj; i++)
	// {
	// 	if (d.map.objects[i].type == OBJ_SPHERE)
	// 	{
	// 		t_sphere *sp = &d.map.objects[i].shape.sphere;
	// 		printf("Sphere %d:\n", i);
	// 		printf("  Position: (%.2f, %.2f, %.2f)\n", 
	// 				sp->center.x, sp->center.y, sp->center.z);
	// 		printf("  Masse: %e\n", sp->param.mass);
	// 		printf("  Physics enabled: %d\n", d.map.objects[i].physics_enabled);
	// 	}
	// }
	mlx_on_event(d.mlx, d.win, MLX_KEYDOWN, key_hook_down, &d);
	mlx_on_event(d.mlx, d.win, MLX_KEYUP, key_hook_up, &d);
	mlx_on_event(d.mlx, d.win, MLX_WINDOW_EVENT, window_hook, &d);
	draw(&d, &d.map);
	mlx_add_loop_hook(d.mlx, update, &d);
	mlx_loop(d.mlx);
}
