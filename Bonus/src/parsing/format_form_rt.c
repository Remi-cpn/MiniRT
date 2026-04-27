/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_form_rt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:40:03 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/22 19:36:32 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/parsing.h"

void	add_sp(t_parsing *p, t_object *o, char **line_split)
{
	if (check_idx_string_tab(line_split, 3) || check_idx_string_tab(line_split, 4)
		|| check_idx_string_tab(line_split, 5))
	{
		if (!double_valid(line_split[2]))
			exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_SP_ARGS_MSG);
		o->type = OBJ_SPHERE;
		o->shape.sphere.center = get_vec(p, line_split[1]);
		o->shape.sphere.radius = ft_atod(line_split[2]) / 2.0;
		o->color = get_color(p, line_split[3]);
		if (line_split[4] && double_valid(line_split[4]) && line_split[5])
			pars_chessboard(p, o, line_split[4], line_split[5]);
		else if (line_split[4])
			pars_texture_map(p, &(o->texture), line_split[4], line_split[5]);
	}
	else
		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_SP_ARGS_MSG);
	if (o->shape.sphere.radius <= 0.0)
		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_SP_ARGS_MSG);
}

void	add_pl(t_parsing *p, t_object *o, char **line_split)
{
	if (check_idx_string_tab(line_split, 3) || check_idx_string_tab(line_split, 4)
		|| check_idx_string_tab(line_split, 5))
	{
		o->type = OBJ_PLANE;
		o->shape.plane.point = get_vec(p, line_split[1]);
		o->shape.plane.normal = get_vec(p, line_split[2]);
		if (fabs(vec_norm(o->shape.plane.normal) - 1.0) > 0.001)
			exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_PL_ARGS_MSG);
		o->color = get_color(p, line_split[3]);
		if (line_split[4] && double_valid(line_split[4]) && line_split[5])
			pars_chessboard(p, o, line_split[4], line_split[5]);
		else if (line_split[4])
			pars_texture_map(p, &(o->texture), line_split[4], line_split[5]);
	}
	else
		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_PL_ARGS_MSG);
}

void	add_cy(t_parsing *p, t_object *o, char **line_split)
{
	if (check_idx_string_tab(line_split, 5) || check_idx_string_tab(line_split, 6)
		|| check_idx_string_tab(line_split, 7))
	{
		if (!double_valid(line_split[3]) || !double_valid(line_split[4]))
			exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_CY_ARGS_MSG);
		o->type = OBJ_CYLINDER;
		o->shape.cylinder.center = get_vec(p, line_split[1]);
		o->shape.cylinder.axis = get_vec(p, line_split[2]);
		if (fabs(vec_norm(o->shape.cylinder.axis) - 1.0) > 0.001)
			exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_CY_ARGS_MSG);
		o->shape.cylinder.radius = ft_atod(line_split[3]) / 2.0;
		o->shape.cylinder.height = ft_atod(line_split[4]);
		o->color = get_color(p, line_split[5]);
		if (line_split[6] && double_valid(line_split[6]) && line_split[7])
			pars_chessboard(p, o, line_split[6], line_split[7]);
		else if (line_split[6])
			pars_texture_map(p, &(o->texture), line_split[6], line_split[7]);
	}
	else
		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_CY_ARGS_MSG);
	if (o->shape.cylinder.radius <= 0.0 || o->shape.cylinder.height <= 0.0)
		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_CY_ARGS_MSG);
}
