/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:34:44 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/07 13:40:39 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"
#include "../MacroLibX/includes/mlx.h"
#include "../MacroLibX/includes/mlx_extended.h"

void	test(const t_data *d)
{
	mlx_color	pixels[40 * 40];
	int		i;
	int		x;
	int		y;

	ft_memset(pixels, 0, sizeof(mlx_color));
	i = 0;
	y = -1;
	while (++y < 40)
	{
		x = -1;
		while (++x < 40)
			pixels[i++].rgba = 0xFF0000FF;
	}
	mlx_pixel_put_region(d->mlx_init, d->win, 100, 100, 40, 40, pixels);
}

void    update(void *param)
{
    //static int      fram;
    const t_data    *d = (t_data *)param;
    //int             w;
    //int             h;
    
    //w = -1;
    //while (++w < d->win_info.width)
    //{
    //    h = -1;
    //    while (++h < d->win_info.height)
    //        mlx_pixel_put(d->mlx_init, d->win, w, h, (mlx_color){ .rgba = 0xFF0000FF});
    //}

	test(d);
}

void    window_hook(int event, void *param)
{
    //ft_printf("%d", event);
    if (event == CROSS)
        exit_prog(param, 0, NULL);
}

void    key_hook(int key, void *param)
{
    if (key == ESC)
        exit_prog(param, 0, NULL);
}

int	main(void)
{
	t_data	d;

	d = init_program();
    mlx_on_event(d.mlx_init, d.win, MLX_KEYDOWN, key_hook, &d);
    mlx_on_event(d.mlx_init, d.win, MLX_WINDOW_EVENT, window_hook, &d);
	mlx_pixel_put(d.mlx_init, d.win, 10, 10, (mlx_color){ .rgba = 0xFF0000FF});
    mlx_add_loop_hook(d.mlx_init, update, &d);
    mlx_loop(d.mlx_init);
}
