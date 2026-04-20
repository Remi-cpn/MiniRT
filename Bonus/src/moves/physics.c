

# include "../../include/minirt.h"
# include "../../include/physics.h"
# include "../../include/world.h"
#include <stdio.h>

/* verlet : new_pos = (2 * cur) - prev + acc*dt^2*/
static void	calc_new_pos(t_vec *cur_pos, t_vec *prev_pos, t_physics *param)
{
	t_vec	tmp_pos;
	t_vec	new_pos;
	t_vec	term1;
	t_vec	term3;


	vec_init(&tmp_pos, cur_pos->x, cur_pos->y, cur_pos->z);
	term1 = vec_mult_scalar(tmp_pos, 2.0);
	term3 = vec_mult_scalar(param->acc, DT * DT);
	new_pos = vec_add(vec_sub(term1, *prev_pos), term3);
	vec_init(cur_pos, new_pos.x, new_pos.y, new_pos.z);
	vec_init(prev_pos, tmp_pos.x, tmp_pos.y, tmp_pos.z);
}

void	calc_acc(t_object *o, int nb_obj)
{
	int			i;
	int			j;
	double 		dist;
	double		F;
	t_vec		acc_tot;
	t_vec		dir;
	// static int	count = 0;

	i = -1;
	while (++i < nb_obj)
	{
		if (o[i].physics_enabled == false)
			continue ;
		vec_init(&acc_tot, 0, 0, 0);
		j = -1;
		while (++j < nb_obj)
		{
			if (o[j].physics_enabled == false || j == i)
				continue ;
			dir = vec_sub(o[j].shape.sphere.param.cur_pos, o[i].shape.sphere.param.cur_pos);
			dist = vec_norm(dir);
			if (dist < 0.001)
				continue ;
			vec_normalize(&dir);
			F = _G * o[j].shape.sphere.param.mass / (dist * dist);
			t_vec tmp = vec_mult_scalar(dir, F);
			acc_tot = vec_add(acc_tot, tmp);
			// if (count % 100 == 0)
			// {
			// 	// t_vec p = o[i].shape.sphere.param.acc;
			// 	printf("G : %e\t%e\t%0.01f\n", _G, o[j].shape.sphere.param.mass, dist);
			// 	printf("F : %e\n", F);
			// 	printf("vecteur dir * F = %0.1f, %0.1f, %0.1f\n", dir.x, dir.y, dir.z);
			// 	i++;
			// }
		}
		vec_init(&o[i].shape.sphere.param.acc, acc_tot.x, acc_tot.y, acc_tot.z);
	}
}

void	recalcul_physics(t_world *w)
{
	int			i;
	t_physics	*p;

	i = -1;
	calc_acc(w->objects, w->nb_obj);
	while (++i < w->nb_obj)
	{
		if (w->objects[i].physics_enabled)
		{
			p = &w->objects[i].shape.sphere.param;
			calc_new_pos(&p->cur_pos, &p->prev_pos, p);
		}
	}
	i = -1;
	while (++i < w->nb_obj)
	{
		if (w->objects[i].physics_enabled)
			w->objects[i].shape.sphere.center = w->objects[i].shape.sphere.param.cur_pos;
	}
}
