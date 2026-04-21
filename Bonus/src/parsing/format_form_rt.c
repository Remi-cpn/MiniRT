/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_form_rt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/11 12:40:03 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/21 16:04:49 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/parsing.h"

static void pars_texture_map(t_parsing *p, t_texture *t, char *texture_file)
{
	t->type = TEX_IMG;
	t->img.mlx =  mlx_new_image_from_file(p->mlx, texture_file,
		&(t->img.width), &(t->img.height));
	if (!t->img.mlx)
		exit_prog_pars(p, ERROR_FILE_TEX, ERROR_FILE_TEX_MSG);
	t->img.pixels = ft_calloc(t->img.width * t->img.height, sizeof(mlx_color));
	if (!t->img.pixels)
		exit_prog_pars(p, ERROR_MALLOC, ERROR_MALLOC_MSG);
	mlx_get_image_region(p->mlx, t->img.mlx, 0, 0, t->img.width,
		t->img.height, t->img.pixels);
}

static void	pars_chessboard(t_parsing *p, t_object *o, char *scale, char *color)
{
	if (double_valid(scale))
	{
		o->texture.type = TEX_DAM;
		o->texture.scale = ft_atod(scale);
		o->texture.color2 = get_color(p, color);
		if (o->texture.scale > 0)
			return ;
	}
	if (o->type == OBJ_SPHERE)
		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_SP_ARGS_MSG);
	if (o->type == OBJ_PLANE)
		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_PL_ARGS_MSG);
	if (o->type == OBJ_CYLINDER)
		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_CY_ARGS_MSG);
}

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
			pars_texture_map(p, &(o->texture), line_split[4]);
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
			pars_texture_map(p, &(o->texture), line_split[4]);
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
			pars_texture_map(p, &(o->texture), line_split[6]);
	}
	else
		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_CY_ARGS_MSG);
	if (o->shape.cylinder.radius <= 0.0 || o->shape.cylinder.height <= 0.0)
		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_CY_ARGS_MSG);
}
