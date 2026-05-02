/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 19:26:57 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/27 10:28:10 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/parsing.h"
#include <stdio.h>

static int	set_img(t_parsing *p, t_img *img, char *file_name)
{
	mlx_image	i;

	i = mlx_new_image_from_file(p->mlx, file_name,
			&(img->width), &(img->height));
	if (!i)
		return (1);
	img->pixels = ft_calloc(img->width * img->height, sizeof(mlx_color));
	if (!img->pixels)
	{
		mlx_destroy_image(p->mlx, i);
		exit_prog_pars(p, ERROR_MALLOC, ERROR_MALLOC_MSG);
	}
	mlx_get_image_region(p->mlx, i, 0, 0, img->width,
		img->height, img->pixels);
	mlx_destroy_image(p->mlx, i);
	return (0);
}

void	pars_texture_map(t_parsing *p, t_texture *t, char *texture_file,
	char *bump_file)
{
	int	flag;

	t->type = TEX_IMG;
	flag = set_img(p, &(t->img), texture_file);
	if (flag == 1)
		exit_prog_pars(p, ERROR_FILE_TEX, ERROR_FILE_TEX_MSG);
	if (!bump_file)
		return ;
	t->bump_m = true;
	flag = set_img(p, &(t->bump_map), bump_file);
	if (flag == 1)
		exit_prog_pars(p, ERROR_FILE_BUMP, ERROR_FILE_BUMP_MSG);
}

void	pars_chessboard(t_parsing *p, t_object *o, char *scale, char *color)
{
	if (double_valid(scale))
	{
		o->texture.type = TEX_CB;
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
	if (o->type == OBJ_CONE)
		exit_prog_pars(p, ERROR_FILE_OBJ, ERROR_FILE_CO_ARGS_MSG);
}
