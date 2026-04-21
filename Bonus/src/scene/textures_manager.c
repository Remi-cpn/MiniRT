/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 16:08:04 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/21 16:41:26 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static t_uv	get_uv(t_hit hit)
{
	t_uv		uv;
	
	if (hit.object->type == OBJ_SPHERE)
		uv = get_uv_sp(hit);
	else if (hit.object->type == OBJ_PLANE)
		uv = get_uv_pl(hit);
	else if (hit.object->type == OBJ_CYLINDER)
		uv = get_uv_cy(hit);
	return (uv);
}

static mlx_color	get_img(t_hit hit, t_uv uv)
{
	t_img		*img;
	mlx_color	pixel;
	int			x;
	int			y;

	img = &hit.object->texture.img;
	x = (int)(uv.u * img->width) % img->width;
	y = (int)((1.0 - uv.v) * img->height) % img->height;
	pixel = img->pixels[y * img->width + x];
	return (pixel);
}

static mlx_color	get_dam(t_hit hit, t_uv uv)
{
	if (uv.case_idx % 2 == 0)
		return (hit.object->color);
	return (hit.object->texture.color2);
}

mlx_color	get_texture(t_hit hit)
{
	t_uv		uv;
	mlx_color	pixel;

	uv = get_uv(hit);
	if (hit.object->texture.type == TEX_IMG)
		pixel = get_img(hit, uv);
	else if (hit.object->texture.type == TEX_DAM)
		pixel = get_dam(hit, uv);
	return (pixel);
}
