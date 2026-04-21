/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_form_solar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:40:03 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/21 11:50:35 by rcompain         ###   ########.fr       */
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

void	add_sp_solar(t_parsing *p, t_object *o, char **line_split)
{
	if (line_split[1] && line_split[2] && line_split[3] && (!line_split[4]
			|| (line_split[4] && line_split[5] && !line_split[6])))
	{
		if (!double_valid(line_split[2]))
			exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_SP_ARGS_MSG);
		o->type = OBJ_SPHERE;
		o->physics_enabled = false;
		o->shape.sphere.center = get_vec(p, line_split[1]);
		o->shape.sphere.radius = ft_atod(line_split[2]) / 2.0;
		o->color = get_color(p, line_split[3]);
		if (line_split[4])
			pars_solar(p, o, line_split[4], line_split[5]);
	}
	else
		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_SP_ARGS_MSG);
	if (o->shape.sphere.radius <= 0.0)
		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_SP_ARGS_MSG);
}
