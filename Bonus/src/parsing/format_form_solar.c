/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_form_solar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:40:03 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/01 12:07:57 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/parsing.h"

static void	pars_solar(t_parsing *p, t_object *o, char *mass, char *velocity)
{
	o->physics_enabled = true;
	o->shape.sphere.param.cur_pos = o->shape.sphere.center;
	o->shape.sphere.param.mass = get_mass(mass);
	o->shape.sphere.param.prev_pos = get_vec(p, velocity);
	vec_init(&o->shape.sphere.param.acc, 0, 0, 0);
	if (o->shape.sphere.param.mass < 0)
		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_SP_ARGS_MSG);
}

void	add_sp_solar(t_parsing *p, t_object *o, char **l_split)
{
	if (check_idx_string_tab(l_split, 3) || check_idx_string_tab(l_split, 4)
		|| check_idx_string_tab(l_split, 5) || check_idx_string_tab(l_split, 6))
	{
		if (!double_valid(l_split[2]))
			exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_SP_ARGS_MSG);
		o->type = OBJ_SPHERE;
		o->physics_enabled = false;
		o->shape.sphere.center = get_vec(p, l_split[1]);
		o->shape.sphere.radius = ft_atod(l_split[2]) / 2.0;
		o->color = get_color(p, l_split[3]);
		if ((l_split[4] && ! l_split[5]) || (l_split[4] && l_split[5] && l_split[6]))
			pars_texture_map(p, &(o->texture), l_split[4], NULL);
		if (l_split[4] && l_split[5] && !l_split[6])
			pars_solar(p, o, l_split[4], l_split[5]);
		else if (l_split[4] && l_split[5])
			pars_solar(p, o, l_split[5], l_split[6]);
	}
	else
		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_SP_ARGS_MSG);
	if (o->shape.sphere.radius <= 0.0)
		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_SP_ARGS_MSG);
}
