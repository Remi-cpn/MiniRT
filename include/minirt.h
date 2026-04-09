/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:33:52 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/09 09:00:36 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/* ——— Lib Intern ——————————————————————————————————————————————————————————— */
# include "../libft/libft.h"
# include "exit.h"
# include "librt.h"
# include "world.h"

/* ——— Lib Graphique ———————————————————————————————————————————————————————— */
# include "../MacroLibX/includes/mlx.h"

/* ——— Lib Extern ——————————————————————————————————————————————————————————— */
# include "stdlib.h"
# include "unistd.h"

/* ——— Structs data ————————————————————————————————————————————————————————— */
typedef struct s_data
{
	mlx_context				mlx_init;
	mlx_window_create_info	win_info;
	mlx_window				win;
	t_world					world;
}	t_data;

typedef struct t_ray
{
	t_vec	origin;
	t_vec	dir;
}	t_ray;

typedef enum e_key
{
	ESC = 41,
}	t_key;

typedef enum e_event
{
	CROSS = 0,
}	t_event;

/* ——— Function prototypes —————————————————————————————————————————————————— */
t_data	init_program(void);

t_ray	pixel_ray(t_world *w, t_data *d, int x_pixel, int y_pixel);
void	draw(t_data *d, t_world *w);
int		hit_sphere(t_world *w, t_ray ray);

#endif
