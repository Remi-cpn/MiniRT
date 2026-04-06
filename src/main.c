/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:34:44 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/06 15:20:53 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"
#include "../MacroLibX/includes/mlx.h"

int	main(void)
{
	mlx_context mlx = mlx_init();

    mlx_window_create_info window_info;
	ft_memset(&window_info, 0, sizeof(mlx_window_create_info));
    window_info.title = "Hello World!";
    window_info.width = 400;
    window_info.height = 400;
    mlx_window win = mlx_new_window(mlx, &window_info);

    mlx_image target = mlx_new_image(mlx, 100, 100);

    mlx_window_create_info target_info;
	ft_memset(&target_info, 0, sizeof(mlx_window_create_info));
    target_info.render_target = target;
    mlx_window target_win = mlx_new_window(mlx, &target_info);

    {
        // All of this will be rendered in `target`
        mlx_clear_window(mlx, target_win, (mlx_color){ .rgba = 0xC16868FF });
        mlx_string_put(mlx, target_win, 10, 10, (mlx_color){ .rgba = 0xFF2066FF }, "text");
        mlx_pixel_put(mlx, target_win, 20, 40, (mlx_color){ .rgba = 0xFF0000FF });
    }

    mlx_put_image_to_window(mlx, win, target, 10, 10); // Render the target to the real window
	
	mlx_loop(mlx);

    mlx_destroy_window(mlx, target_win);
    mlx_destroy_image(mlx, target);

    mlx_destroy_window(mlx, win);

    mlx_destroy_context(mlx);
}

