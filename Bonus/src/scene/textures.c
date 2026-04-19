/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 10:38:04 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/19 12:30:51 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include <stdio.h>

/* u = 0.5 + atan2(Pz, Px) / (2 * PI)
v = 0,5 + asin(Py) / (PI)*/
static t_uv	get_uv(t_hit hit)
{
	t_uv	uv;

	if (hit.object->type == OBJ_SPHERE)
	{
		uv.u = 0.5 + atan2(hit.normal.z, hit.normal.x) / (2 * PI);
		uv.v = 0.5 + asin(hit.normal.y) / PI;
	}
	return (uv);
}

mlx_color	get_texture(t_hit hit)
{
	t_uv		uv;
	int			c;
	mlx_color	pixel;

	uv = get_uv(hit);
	c = (int)(uv.u * hit.object->texture.scale)
		+ (int)(uv.v * hit.object->texture.scale);
	if (c % 2 == 0)
		pixel = hit.object->color;
	else
		pixel = hit.object->texture.color2;
	return (pixel);
}
