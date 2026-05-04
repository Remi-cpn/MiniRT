/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:33:52 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/04 16:08:50 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

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
# include "world_bonus.h"
# include "parsing_bonus.h"
# include "exit_bonus.h"

/* ——— Lib Graphique ———————————————————————————————————————————————————————— */
# include "../../MacroLibX/includes/mlx.h"
# include "../../MacroLibX/includes/mlx_extended.h"

/* ——— Forward Declare —————————————————————————————————————————————————— */
typedef struct s_world	t_world;
typedef struct s_data	t_data;
typedef struct s_object	t_object;

/* ——— DEFINE     ——————————————————————————————————————————————————————————— */
# define RENDER_DIST 5000000.0
# define SHADOW_DIST 200000.0
# define TILE_SIZE 128
# define GAMMA 0.75
# define ORBIT_SPEED 0.03
# define THETA_CLAMP 1.55

/* ——— Multi Threading —————————————————————————————————————————————————————— */
typedef enum e_mod
{
	PHYS_ACC,
	PHYS_SUN,
	PHYS_POS,
	RENDER
}	t_mod;

typedef struct s_threading
{
	t_mod			mod;
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
	int				job_idx;
	int				nbr_jobs;
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
    bool    n;
    bool    p;
	bool	most;
	bool	less;
}	t_input;

typedef struct s_cam_orbit
{
	double	r;
	double	theta;
	double	phi;
}	t_cam_orbit;

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
	int						cam_target;
	int						speed_sim;
	t_cam_orbit				orbit;
}	t_data;

typedef struct s_ray
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
	_R = 21,
	N = 17,
	P = 19,
	MOST = 87,
	LESS = 86,
}	t_key;

typedef enum e_event
{
	CROSS = 0,
}	t_event;

/* ——— Function prototypes —————————————————————————————————————————————————— */
t_data	init_program(void);
void	init_threads(t_data *d);
void	init_speed_sim(t_data *d, int ac, char **av);

t_ray	get_ray(t_camera cam, double i_hor, double i_ver);
void	draw(t_data *d);
void	pixel_color(t_world *w, t_ray ray, mlx_color *color);
void	light(t_world *w, t_hit *hit, mlx_color *color);
t_hit	find_closest_hit(t_world *w, t_ray ray, int flag_dist);

double	hit_sphere(t_sphere sphere, t_ray ray);
double	hit_plane(t_plane plane, t_ray ray);
double	hit_cylinder(t_cylinder cylinder, t_ray ray);
double	hit_cone(t_cone cone, t_ray ray);
double	hit_cap(t_plane plane, t_ray ray, double radius);
double	hit_ring(t_ring ring, t_ray ray);
t_hit	find_closest_hit(t_world *w, t_ray ray, int flag_dist);

void	calc_one_light(t_world *w, t_hit *hit, t_light *light,
			t_light_managment *l);
void	window_hook(int event, void *param);
void	key_hook_up(int key, void *param);
void	key_hook_down(int key, void *param);
void	mouse_hook_wheel(int event, void *param);
void	mouse_hook(int event, void *param);

bool	update_cam(t_data *d, double speed, double speed_rot);
void	orbit_movement(t_data *d, double speed);
void	orbit_zoom(t_data *d, double speed);
bool	update_cam_free(t_data *d, double speed, double speed_rot);
void	reparse(t_data *d);
void	linear_movement(t_data *d, t_camera *cam, double speed);
void	snap_cam_to_planet(t_data *d, int dir);
void	follow_cam(t_data *d);

void	*routine(void *params);
void	render_tile(t_data *d, t_world *w, int x, int y);

#endif
