/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 16:08:04 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/02 17:26:54 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

mlx_color	get_pixel_img(t_img *img, t_uv uv)
{
	mlx_color	pixel;
	int			x;
	int			y;

	x = (int)((1.0 - uv.u) * img->width) % img->width;
	if (x < 0)
		x += img->width;
	y = (int)((1.0 - uv.v) * img->height) % img->height;
	if (y < 0)
		y += img->height;
	pixel = img->pixels[y * img->width + x];
	return (pixel);
}

static t_uv	get_uv(t_hit hit)
{
	t_uv		uv;

	if (hit.object->type == OBJ_SPHERE)
		uv = get_uv_sp(hit);
	else if (hit.object->type == OBJ_PLANE)
		uv = get_uv_pl(hit);
	else if (hit.object->type == OBJ_CYLINDER)
		uv = get_uv_cy(hit);
	else if (hit.object->type == OBJ_RING)
		uv = get_uv_ring(hit);
	else if (hit.object->type == OBJ_CONE)
		uv = get_uv_co(hit);
	return (uv);
}

static mlx_color	get_checkboard(t_hit hit, t_uv uv)
{
	if (uv.case_idx % 2 == 0)
		return (hit.object->color);
	return (hit.object->texture.color2);
}

mlx_color	get_texture(t_hit *hit)
{
	t_uv		uv;
	mlx_color	pixel;

	uv = get_uv(*hit);
	if (hit->object->texture.type == TEX_IMG)
	{
		pixel = get_pixel_img(&(hit->object->texture.img), uv);
		if (hit->object->texture.bump_m == true)
			get_bump_map(hit, uv);
	}
	else if (hit->object->texture.type == TEX_CB)
		pixel = get_checkboard(*hit, uv);
	return (pixel);
}
