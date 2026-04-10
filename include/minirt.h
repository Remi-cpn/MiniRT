/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:33:52 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/10 09:46:54 by rcompain         ###   ########.fr       */
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
# include "stdio.h"

/* ——— Structs data ————————————————————————————————————————————————————————— */
typedef struct s_input
{
	bool d;
	bool a;
	bool w;
	bool s;
	bool up;
	bool down;
}	t_input;

typedef struct s_data
{
	mlx_context				mlx;
	mlx_window_create_info	win_info;
	mlx_window				win;
	mlx_image				img;
	t_input					input;
	t_world					map;
	int						width;
	int						height;
}	t_data;

typedef struct t_ray
{
	t_vec	origin;
	t_vec	dir;
}	t_ray;

typedef enum e_key
{
	ESC = 41,
	D = 7,
	A = 4,
	W = 26,
	S = 22,
	UP = 82,
	DOWN = 81,
	WHEEL_F = 1,
	WHEEL_B = 2,
}	t_key;

typedef enum e_event
{
	CROSS = 0,
}	t_event;

/* ——— Function prototypes —————————————————————————————————————————————————— */
t_data	init_program(void);

t_ray	pixel_ray(t_world *w, t_data *d, int x_pixel, int y_pixel);
void	draw(t_data *d, t_world *w);
void	pixel_color(t_world *w, t_ray ray, mlx_color *color);

double	hit_sphere(t_world *w, t_ray ray);
double	hit_plane(t_world *w, t_ray ray);

void	window_hook(int event, void *param);
void	key_hook_up(int key, void *param);
void	key_hook_down(int key, void *param);
void	mouse_hook_wheel(int event, void *param);
void	mouse_hook(int event, void *param);

#endif
