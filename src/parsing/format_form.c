/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_form.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:40:03 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/11 15:50:02 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/parsing.h"

void	add_sp(t_parsing *p, t_object *o, char **line_split)
{
	if (line_split[1] && line_split[2] && line_split[3] && line_split[4]
		&& !line_split[5])
	{
		o->type = OBJ_SPHERE;
		o->shape.sphere.center = get_vec(p, line_split[1]);
		o->shape.sphere.radius = ft_atof(line_split[2]) / 2.0;
		o->color = get_color(p, line_split[3]);
	}
	else
		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_SP_ARGS_MSG);
	if (o->shape.sphere.radius <= 0.0)
		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_SP_ARGS_MSG);
}

void	add_pl(t_parsing *p, t_object *o, char **line_split)
{
	if (line_split[1] && line_split[2] && line_split[3] && !line_split[4])
	{
		o->type = OBJ_PLANE;
		o->shape.plane.point = get_vec(p, line_split[1]);
		o->shape.plane.normal = get_vec(p, line_split[2]);
		o->color = get_color(p, line_split[3]);
	}
	else
		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_PL_ARGS_MSG);
	if (o->shape.plane.normal.x < -1.0 || o->shape.plane.normal.x > 1.0
		|| o->shape.plane.normal.y < -1.0 || o->shape.plane.normal.y > 1.0
		|| o->shape.plane.normal.z < -1.0 || o->shape.plane.normal.z > 1.0)
		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_PL_ARGS_MSG);
}

void	add_cy(t_parsing *p, t_object *o, char **line_split)
{
	if (line_split[1] && line_split[2] && line_split[3] && line_split[4]
		&& line_split[5] && !line_split[6])
	{
		o->type = OBJ_CYLINDER;
		o->shape.cylinder.center = get_vec(p, line_split[1]);
		o->shape.cylinder.axis = get_vec(p, line_split[2]);
		o->shape.cylinder.radius = ft_atof(line_split[3]) / 2.0;
		o->shape.cylinder.height = ft_atof(line_split[4]);
		o->color = get_color(p, line_split[5]);
	}
	else
		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_CY_ARGS_MSG);
	if (o->shape.cylinder.radius <= 0.0 || o->shape.cylinder.height <= 0.0
		|| o->shape.cylinder.axis.x < -1.0 || o->shape.cylinder.axis.x > 1.0
		|| o->shape.cylinder.axis.y < -1.0 || o->shape.cylinder.axis.y > 1.0
		|| o->shape.cylinder.axis.z < -1.0 || o->shape.cylinder.axis.z > 1.0)
		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_CY_ARGS_MSG);
}
