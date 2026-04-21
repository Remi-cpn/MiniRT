/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 13:17:11 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/20 18:12:32 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "minirt.h"
# include "../../MacroLibX/includes/mlx.h"

# define RGB 3
# define R 0
# define G 1
# define B 2

/* ——— Variable prototypes —————————————————————————————————————————————————— */
typedef struct s_data	t_data;

/* ——— Textures ————————————————————————————————————————————————————————————— */
typedef enum e_tex_type
{
	TEX_NONE,
	TEX_DAM, // Damier
}	t_tex_type;

typedef struct s_uv
{
	double	u;
	double	v;
	int		case_idx;
}	t_uv;

typedef struct s_texture
{
	t_tex_type	type;
	mlx_color	color2;
	double		scale;
}	t_texture;

/* ——— Objects —————————————————————————————————————————————————————————————— */
typedef struct s_light_managment
{
	double	diffuse[RGB];
	double	ambient[RGB];
	double	light[RGB];
}	t_light_managment;

typedef struct s_light
{
	t_point		position;
	mlx_color	color;
	double		intensity;
}	t_light;

typedef enum e_obj
{
	OBJ_NONE,
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
}	t_obj;

typedef struct s_camera
{
	t_point	origin;
	t_point	corner;
	t_vec	hor;
	t_vec	hor_n;
	t_vec	ver;
	t_vec	ver_n;
	t_vec	dir;
	double	fov;
	double	focal;
}	t_camera;

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

typedef struct s_cylinder
{
	t_point	center;
	t_vec	axis;
	double	radius;
	double	height;
}	t_cylinder;

typedef struct s_object
{
	t_obj				type;
	mlx_color			color;
	t_texture			texture;
	union u_shape
	{
		t_sphere		sphere;
		t_plane			plane;
		t_cylinder		cylinder;
	}	shape;
}	t_object;

/* ——— Ray —————————————————————————————————————————————————————————————————— */
typedef struct s_hit
{
	double		t;
	t_point		point;
	t_vec		normal;
	t_object	*object;
	int			hit;
	mlx_color	pixel_color;
}	t_hit;

/* ——— Scene ———————————————————————————————————————————————————————————————— */
typedef struct s_world
{
	t_camera	camera;
	t_object	*objects;
	int			nb_obj;
	t_light		lights;
	mlx_color	ambient;
	double		ambient_ratio;
}	t_world;

/* ——— Function prototypes —————————————————————————————————————————————————— */
void		calcul_viewport(t_camera *cam, double ratio);
void		init_world(t_data *d, t_world *w);
mlx_color	get_texture(t_hit hit);

#endif
