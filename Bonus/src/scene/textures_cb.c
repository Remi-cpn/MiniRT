/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_cb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 10:38:04 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/20 18:18:01 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"


/* axis1 = cross(normal, up)
   u = dot(hit_point, axis1)
   axis2 = cross(normal, axis1)
   v = dot(hit_point, axis2)
   even or odd = floor(u / scale) + floor(v / scale) */
static mlx_color	get_uv_pl(t_hit hit)
{
	t_uv				uv;
	t_vec				axis;
	mlx_color			color;
	static const t_vec	up = {.x = 0, .y = 1, .z = 0};
	static const t_vec	depth = {.x = 0, .y = 0, .z = 1};

	axis = vec_vectoriel(hit.normal, up);
	if (vec_square(axis) < 0.0001)
		axis = vec_vectoriel(hit.normal, depth);
	vec_normalize(&axis);
	uv.u = vec_dot(hit.point, axis);
	axis = vec_vectoriel(hit.normal, axis);
	uv.v = vec_dot(hit.point, axis);
	uv.case_idx = (int)floor(uv.u / hit.object->texture.scale)
		+ (int)floor(uv.v / hit.object->texture.scale);
	if (uv.case_idx % 2 == 0)
		color = hit.object->color;
	else
		color = hit.object->texture.color2;
	return (color);
}

/* u = 0.5 + atan2(Pz, Px) / (2 * PI)
v = 0,5 + asin(Py) / (PI)*/
static mlx_color	get_uv_sp(t_hit hit)
{
	t_uv		uv;
	mlx_color	color;

	uv.u = 0.5 + atan2(hit.normal.z, hit.normal.x) / (2 * PI);
	uv.v = 0.5 + asin(hit.normal.y) / PI;
	uv.case_idx = (int)(uv.u * hit.object->texture.scale)
		+ (int)(uv.v * hit.object->texture.scale);
	if (uv.case_idx % 2 == 0)
		color = hit.object->color;
	else
		color = hit.object->texture.color2;
	return (color);
}

mlx_color	get_texture(t_hit hit)
{
	mlx_color	pixel;

	if (hit.object->type == OBJ_SPHERE)
		pixel = get_uv_sp(hit);
	else if (hit.object->type == OBJ_PLANE)
		pixel = get_uv_pl(hit);
	return (pixel);
}
