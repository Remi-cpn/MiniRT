
#ifndef PHYSICS_H
# define PHYSICS_H

/* ——— Lib Extern ——————————————————————————————————————————————————————————— */
# include "minirt.h"
#include "world.h"
# include <math.h>

/* ——— Units ——————————————————————————————————————————————————————————— */
// Distance : 1 unit = 1 AU (Astronomical Unit) = 1.496e11 m
// Mass : 1 unit = 1 solar mass  = 1.989e30 kg
// Times : 1 unit = 1 day = 86400 s

/* ——— Define ——————————————————————————————————————————————————————————————— */
# define SOLAR_MASS 1.989e30
#define _G 2.959122e-4
# define DT 0.01

typedef struct s_object t_object;
typedef struct s_world t_world;

/* ——— Struct prototypes ———————————————————————————————————————————————————— */
typedef struct s_physics
{
	t_point		cur_pos;
	t_point		prev_pos;
	double		mass;
	t_vec		acc;
}	t_physics;

/* ——— Functions prototypes ———————————————————————————————————————————————————— */
void	calc_acc(t_object *o, int nb_obj);
void	recalcul_physics(t_world *w);

#endif

