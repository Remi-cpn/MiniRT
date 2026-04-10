/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 13:17:11 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/10 09:50:30 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "librt.h"
# include "../MacroLibX/includes/mlx.h"

# define FOV 70

/* ——— Variable prototypes —————————————————————————————————————————————————— */
typedef struct s_data	t_data;

/* ——— Struct prototypes ———————————————————————————————————————————————————— */
typedef enum e_obj
{
	OBJ_NONE,
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
}	t_obj;

typedef struct	s_camera
{
	t_point	origin;
	t_point	corner;
	t_vec	hor;
	t_vec	ver;
	double	fov;
	double	focal;
}				t_camera;

typedef struct s_plane
{
	t_point	point;
	t_vec	normal;
}	t_plane;

typedef struct s_sphere
{
	t_point	center;
	double	radius;
}	t_sphere;

typedef struct s_cylinder {
	t_point	center;
	t_vec	axis;
	double	radius;
	double	height;
}   t_cylinder;

typedef struct s_light {
	t_point		position;
	mlx_color	color;
	double		intensity;
}   t_light;

typedef struct s_object {
	t_obj				type;
	mlx_color			color;
	union {
		t_sphere        sphere;
		t_plane         plane;
		t_cylinder      cylinder;
	}                   shape;
}   t_object;

typedef struct s_hit {
	double		t;
	t_point		point;
	t_vec		normal;
	t_object	*object;
	int			hit;
}   t_hit;

typedef struct s_scene {
	t_camera	camera;
	t_object	*objects;
	int			nb_obj;
	t_light		lights;
	mlx_color	ambient;
	double		ambient_ratio;
}   t_scene;

typedef struct s_world
{
	t_sphere	sphere;
	t_plane		plane;
	t_camera	cam;
	t_light		light;
	double		ambient_light;
}	t_world;

/* ——— Function prototypes —————————————————————————————————————————————————— */
t_world	init_world(t_data *data);

#endif
