/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 13:17:11 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/27 10:15:05 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHYSICS_H
# define PHYSICS_H

/* ——— Lib Extern ——————————————————————————————————————————————————————————— */
# include <math.h>

/* ——— Lib Intern ——————————————————————————————————————————————————————————— */
# include "../../librt/librt.h"

/* ——— Units ——————————————————————————————————————————————————————————— */
// Distance : 1 unit = 1 AU (Astronomical Unit) = 1.496e11 m
// Mass : 1 unit = 1 solar mass  = 1.989e30 kg
// Times : 1 unit = 1 day = 86400 s

/* ——— Forward Declare —————————————————————————————————————————————————— */
typedef struct s_object	t_object;
typedef struct s_world	t_world;

/* ——— Define ——————————————————————————————————————————————————————————————— */
# define SOLAR_MASS 1.989e30
# define _G 2.959122e-4
# define DT 0.01

/* ——— Struct prototypes ———————————————————————————————————————————————————— */
typedef struct s_physics
{
	t_point		cur_pos;
	t_point		prev_pos;
	double		mass;
	t_vec		acc;
}	t_physics;

/* ——— Functions prototypes ————————————————————————————————————————————————— */
void	calc_acc(t_object *o, int nb_obj);
void	recalcul_physics(t_world *w);

#endif
