/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_form_solar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:40:03 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/02 12:32:58 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minirt_bonus.h"
#include "../../../include/parsing_bonus.h"
#include <stdio.h>

static void	pars_solar(t_parsing *p, t_object *o, char *mass, char *velocity)
{
	t_vec	vel;

	o->physics_enabled = true;
	o->shape.sphere.param.cur_pos = o->shape.sphere.center;
	o->shape.sphere.param.mass = get_mass(mass);
	vel = get_vec(p, velocity);
	o->shape.sphere.param.prev_pos = vec_sub(o->shape.sphere.center,
			vec_mult_scalar(vel, DT));
	vec_init(&o->shape.sphere.param.acc, 0, 0, 0);
	if (o->shape.sphere.param.mass < 0)
		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_SP_ARGS_MSG);
}

void	add_sp_solar(t_parsing *p, t_object *o, char **l_split)
{
	if (check_idx_string_tab(l_split, 8))
	{
		if (!double_valid(l_split[2]) || !double_valid(l_split[6]))
			exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_SP_ARGS_MSG);
		o->type = OBJ_SPHERE;
		o->physics_enabled = false;
		o->shape.sphere.center = get_vec(p, l_split[1]);
		o->shape.sphere.radius = ft_atod(l_split[2]) / 2.0;
		o->color = get_color(p, l_split[3]);
		if (ft_strncmp(l_split[4], "NULL", 5))
			pars_texture_map(p, &(o->texture), l_split[4],
				ft_strncmp(l_split[5], "NULL", 5) ? l_split[5] : NULL);
		o->shape.sphere.rotation = 0.0;
		o->shape.sphere.rotation_speed = ft_atod(l_split[6]);
		pars_solar(p, o, l_split[7], l_split[8]);
	}
	else
		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_SP_ARGS_MSG);
	if (o->shape.sphere.radius <= 0.0)
		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_SP_ARGS_MSG);
}

void	add_ri(t_parsing *p, t_object *o, char **l_split, int idx)
{
	if (check_idx_string_tab(l_split, 4) || check_idx_string_tab(l_split, 5))
	{
		if (!double_valid(l_split[2]) || !double_valid(l_split[3]))
			exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_RI_ARGS_MSG);
		o->type = OBJ_RING;
		o->physics_enabled = false;
		if (idx == 0 || p->world->objects[idx - 1].type != OBJ_SPHERE)
			exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_RI_ARGS_MSG);
		o->shape.ring.center = &p->world->objects[idx - 1].shape.sphere.center;
		o->shape.ring.normal = get_vec(p, l_split[1]);
		if (fabs(vec_norm(o->shape.ring.normal) - 1.0) > 0.001)
			exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_RI_ARGS_MSG);
		o->shape.ring.inner_rad = ft_atod(l_split[2]);
		o->shape.ring.outer_rad = ft_atod(l_split[3]);
		o->color = get_color(p, l_split[4]);
		if (l_split[5])
			pars_texture_map(p, &(o->texture), l_split[5], NULL);
	}
	else
		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_RI_ARGS_MSG);
	if (o->shape.ring.inner_rad < 0.0
		|| o->shape.ring.outer_rad <= o->shape.ring.inner_rad
		|| o->shape.ring.center == NULL)
		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_RI_ARGS_MSG);
}

void	add_so(t_parsing *p, t_sun *s, char **l)
{
	if (check_idx_string_tab(l, 6) || (check_idx_string_tab(l, 7)))
	{
		if (!double_valid(l[2]) || !double_valid(l[4]) || !double_valid(l[5]))
			exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_SO_ARGS_MSG);
		s->param.cur_pos = get_vec(p, l[1]);
		s->radius = ft_atod(l[2]) / 2.0;
		s->color = get_color(p, l[3]);
		s->intensity = ft_atod(l[4]);
		s->param.mass = get_mass(l[5]);
		s->param.prev_pos = vec_sub(s->param.cur_pos,
				vec_mult_scalar(get_vec(p, l[6]), DT));
		vec_init(&s->param.acc, 0, 0, 0);
		if (l[7])
			pars_texture_map(p, &(s->texture), l[7], NULL);
	}
	else
		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_SO_ARGS_MSG);
	if (s->radius <= 0.0 || s->param.mass < 0 || s->intensity < 0)
		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_SO_ARGS_MSG);
}
