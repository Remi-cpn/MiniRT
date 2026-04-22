/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bump_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 17:53:58 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/22 18:56:21 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* (r + g + b) / (3 * 255.0) */
static double	get_height(t_hit hit, t_uv uv, int flag)
{
	t_uv		next;
	double		height;
	mlx_color	pixel;

	next = uv;
	if (flag == 0)
		next.u += 1.0 / hit.object->texture.bump_map.width;
	else if (flag == 1)
		next.v += 1.0 / hit.object->texture.bump_map.height;
	pixel = get_pixel_img(&(hit.object->texture.bump_map), next);
	height = (pixel.r + pixel.g + pixel.b) / (3 * 255.0);
	return (height);
}

static void	get_gradient(t_hit *hit, t_uv uv, double *gradient_u,
	double *gradient_v)
{
	double	h;
	double	h_next_x;
	double	h_next_y;

	h = get_height(*hit, uv, -1);
	h_next_x = get_height(*hit, uv, 0);
	h_next_y = get_height(*hit, uv, 1);
	*gradient_u = h_next_x - h;
	*gradient_v = h_next_y - h;
}

/* normal += du * axis1 + dv * axis2 */
void	get_bump_map(t_hit *hit, t_uv uv)
{
	double	gradient_u;
	double	gradient_v;

	gradient_u = 0;
	gradient_v = 0;
	get_gradient(hit, uv, &gradient_u, &gradient_v);
	hit->normal = vec_add(hit->normal,
			vec_add(vec_mult_scalar(uv.tangent, gradient_u),
				vec_mult_scalar(uv.bitangent, gradient_v)));
	vec_normalize(&(hit->normal));
}
