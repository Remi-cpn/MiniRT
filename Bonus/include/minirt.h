/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:33:52 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/01 08:53:00 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/* ——— Lib Extern ——————————————————————————————————————————————————————————— */
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/sysinfo.h>
# include <semaphore.h>

/* ——— Lib Intern ——————————————————————————————————————————————————————————— */
# include "../../libft/libft.h"
# include "../../librt/librt.h"
# include "exit.h"
# include "world.h"
# include "parsing.h"
# include "physics.h"

/* ——— Lib Graphique ———————————————————————————————————————————————————————— */
# include "../../MacroLibX/includes/mlx.h"
# include "../../MacroLibX/includes/mlx_extended.h"

/* ——— DEFINE     ——————————————————————————————————————————————————————————— */
# define RENDER_DIST 1000.0
# define TILE_SIZE 16
# define GAMMA 0.8

/* ——— Multi Threading —————————————————————————————————————————————————————— */
typedef struct s_threading
{
	int				nbr_threads;
	pthread_t		*threads;
	pthread_mutex_t	queue;
	bool			mutex_ready;
	pthread_cond_t	cond;
	bool			cond_ready;
	sem_t			sem;
	bool			sem_ready;
	bool			start;
	bool			stop;
	int				index_tile;
	int				nbr_tiles;
}	t_threading;

/* ——— Structs data ————————————————————————————————————————————————————————— */
typedef struct s_input
{
	bool	d;
	bool	a;
	bool	w;
	bool	s;
	bool	up;
	bool	down;
	bool	left;
	bool	right;
	bool	i;
	bool	o;
	bool	ctrl;
	bool	space;
	bool	r;
}	t_input;

typedef struct s_data
{
	mlx_context				mlx;
	mlx_window_create_info	win_info;
	mlx_window				win;
	mlx_image				img;
	t_input					input;
	t_world					map;
	mlx_color				*pixels;
	char					*filename;
	bool					solar_file;
	t_threading				pool;
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
	LEFT = 80,
	RIGHT = 79,
	I = 12,
	O = 18,
	LCTRL = 224,
	SPACE = 44,
	WHEEL_F = 1,
	WHEEL_B = 2,
	_R = 21
}	t_key;

typedef enum e_event
{
	CROSS = 0,
}	t_event;

/* ——— Function prototypes —————————————————————————————————————————————————— */
t_data	init_program(void);
void	init_threads(t_data *d);

t_ray	get_ray(t_camera cam, double i_hor, double i_ver);
void	draw(t_data *d);
void	pixel_color(t_world *w, t_ray ray, mlx_color *color);
void	light(t_world *w, t_hit *hit, mlx_color *color);
t_hit	find_closest_hit(t_world *w, t_ray ray, int flag_dist);

double	hit_sphere(t_sphere sphere, t_ray ray);
double	hit_plane(t_plane plane, t_ray ray);
double	hit_cylinder(t_cylinder cylinder, t_ray ray);

void	window_hook(int event, void *param);
void	key_hook_up(int key, void *param);
void	key_hook_down(int key, void *param);
void	mouse_hook_wheel(int event, void *param);
void	mouse_hook(int event, void *param);

bool	update_cam(t_data *d, double speed);

void	*routine(void *params);
void	render_tile(t_data *d, t_world *w, int x, int y);

#endif
