/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 13:17:11 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/27 10:15:05 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "../../librt/librt.h"
# include "../../MacroLibX/includes/mlx.h"
# include "physics.h"

# define SHINY 32
# define KS 0.5
# define RGB 3
# define R 0
# define G 1
# define B 2


/* ——— Forward Declare —————————————————————————————————————————————————— */
typedef struct s_data		t_data;
typedef struct s_ray		t_ray;

/* ——— Textures ————————————————————————————————————————————————————————————— */
typedef enum e_tex_type
{
	TEX_NONE,
	TEX_CB,
	TEX_IMG,
}	t_tex_type;

typedef struct s_img
{
	int			width;
	int			height;
	mlx_color	*pixels;
}	t_img;

typedef struct s_uv
{
	double	u;
	double	v;
	int		case_idx;
	t_vec	tangent;
	t_vec	bitangent;
}	t_uv;

typedef struct s_texture
{
	t_tex_type	type;
	mlx_color	color2;
	double		scale;
	t_img		img;
	bool		bump_m;
	t_img		bump_map;
}	t_texture;

/* ——— Objects —————————————————————————————————————————————————————————————— */
typedef struct s_light_managment
{
	double	diffuse[RGB];
	double	ambient[RGB];
	double	light[RGB];
	double	specular[RGB];
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
	OBJ_CONE,
}	t_obj;

typedef struct s_camera
{
	t_point		origin;
	t_point		corner;
	t_vec		hor;
	t_vec		hor_n;
	t_vec		ver;
	t_vec		ver_n;
	t_vec		dir;
	double		fov;
	double		focal;
}	t_camera;

typedef struct s_sun
{
	t_physics	param;
	double		radius;
	mlx_color	color;
	double		intensity;
	t_texture	texture;
}   t_sun;

typedef struct s_plane
{
	t_point	point;
	t_vec	normal;
}	t_plane;

typedef struct s_sphere
{
	t_point		center;
	double		radius;
	t_physics	param;
	double		rotation;
	double		rotation_speed;
}	t_sphere;

typedef struct s_cylinder
{
	t_point	center;
	t_vec	axis;
	double	radius;
	double	height;
}	t_cylinder;

typedef struct s_cone
{
	t_point	apex;
	t_vec	axis;
	double	angle;
}	t_cone;

typedef struct s_object
{
	t_obj				type;
	mlx_color			color;
	t_texture			texture;
	bool				physics_enabled;
	union u_shape
	{
		t_sphere		sphere;
		t_cone			cone;
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
	int			sun_idx;
	mlx_color	pixel_color;
}	t_hit;

/* ——— Scene ———————————————————————————————————————————————————————————————— */
typedef struct s_world
{
	t_camera	camera;
	t_object	*objects;
	int			nb_obj;
	t_light		*lights;
	int			nb_light;
	t_sun		*suns;
	int			nb_sun;
	mlx_color	ambient;
	double		ambient_ratio;
}	t_world;

/* ——— Function prototypes —————————————————————————————————————————————————— */
void		calcul_viewport(t_camera *cam, double ratio);
void		init_world(t_data *d, t_world *w);
void		fill_hit_details(t_hit *hit, t_ray ray);

/* Textures */
mlx_color	get_texture(t_hit *hit);
t_uv		get_uv_sp(t_hit hit);
t_uv		get_uv_pl(t_hit hit);
t_uv		get_uv_cy(t_hit hit);
t_uv		get_uv_caps(t_hit hit);
mlx_color	get_pixel_img(t_img *img, t_uv uv);
void		get_bump_map(t_hit *hit, t_uv uv);

#endif
