/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 13:17:11 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/10 08:55:41 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "librt.h"

# define FOV 70

/* ——— Variable prototypes —————————————————————————————————————————————————— */
typedef struct s_data	t_data;

/* ——— Struct prototypes ———————————————————————————————————————————————————— */
typedef struct s_light
{
	t_vec	pos;
	t_color	color;
}	t_light;

typedef struct s_camera
{
	t_vec	pos;
	t_vec	dir;
	int		fov;
}	t_camera;

typedef struct s_sphere
{
	t_vec	center;
	double	radius;
	t_color	color;
}	t_sphere;

typedef struct s_world
{
	t_sphere	sphere;
	t_camera	cam;
	t_light		light;
}	t_world;

/* ——— Function prototypes —————————————————————————————————————————————————— */
t_world	init_world(t_data *data);

#endif