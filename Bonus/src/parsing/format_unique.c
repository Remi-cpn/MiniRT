/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_unique.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 16:45:33 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/13 15:36:00 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/parsing.h"

void	add_cam(t_parsing *p, t_world *w, char **line_split)
{
	if (p->cam == true)
		exit_prog_pars(p, ERROR_FILE_CAM, ERROR_FILE_CAM_MSG);
	p->cam = true;
	if (check_idx_string_tab(line_split, 3))
	{
		if (!double_valid(line_split[3]))
			exit_prog_pars(p, ERROR_FILE_CAM, ERROR_FILE_CAM_ARGS_MSG);
		w->camera.origin = get_vec(p, line_split[1]);
		w->camera.dir = get_vec(p, line_split[2]);
		w->camera.fov = ft_atod(line_split[3]);
	}
	else
		exit_prog_pars(p, ERROR_FILE_CAM, ERROR_FILE_CAM_ARGS_MSG);
	if (w->camera.fov <= 0.0 || w->camera.fov >= 180.0)
		exit_prog_pars(p, ERROR_FILE_CAM, ERROR_FILE_CAM_ARGS_MSG);
}

void	add_light(t_parsing *p, t_world *w, char **line_split)
{
	if (p->light == true)
		exit_prog_pars(p, ERROR_FILE_LIGHT, ERROR_FILE_LIGHT_MSG);
	p->light = true;
	if (check_idx_string_tab(line_split, 3))
	{
		if (!double_valid(line_split[2]))
			exit_prog_pars(p, ERROR_FILE_LIGHT, ERROR_FILE_LIGHT_ARGS_MSG);
		w->lights.position = get_vec(p, line_split[1]);
		w->lights.intensity = ft_atod(line_split[2]);
		w->lights.color = get_color(p, line_split[3]);
	}
	else
		exit_prog_pars(p, ERROR_FILE_LIGHT, ERROR_FILE_LIGHT_ARGS_MSG);
	if (w->lights.intensity < 0.0 || w->lights.intensity > 1.0)
		exit_prog_pars(p, ERROR_FILE_LIGHT, ERROR_FILE_LIGHT_ARGS_MSG);
}

void	add_al(t_parsing *p, t_world *w, char **line_split)
{
	if (p->al == true)
		exit_prog_pars(p, ERROR_FILE_AL, ERROR_FILE_AL_MSG);
	p->al = true;
	if (check_idx_string_tab(line_split, 2))
	{
		if (!double_valid(line_split[1]))
			exit_prog_pars(p, ERROR_FILE_AL, ERROR_FILE_AL_ARGS_MSG);
		w->ambient_ratio = ft_atod(line_split[1]);
		w->ambient = get_color(p, line_split[2]);
	}
	else
		exit_prog_pars(p, ERROR_FILE_AL, ERROR_FILE_AL_ARGS_MSG);
	if (w->ambient_ratio < 0.0 || w->ambient_ratio > 1.0)
		exit_prog_pars(p, ERROR_FILE_AL, ERROR_FILE_AL_ARGS_MSG);
}
