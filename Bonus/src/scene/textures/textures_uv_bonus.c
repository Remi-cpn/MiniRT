/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_uv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 10:38:04 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/02 17:28:49 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minirt_bonus.h"

t_uv	get_uv_ring(t_hit hit)
{
	t_uv				uv;
	t_vec				diff;
	double				r;
	static const t_vec	up = {.x = 0, .y = 1, .z = 0};
	static const t_vec	depth = {.x = 0, .y = 0, .z = 1};

	uv.tangent = vec_vectoriel(hit.object->shape.ring.normal, up);
	if (vec_square(uv.tangent) < 0.0001)
		uv.tangent = vec_vectoriel(hit.object->shape.ring.normal, depth);
	vec_normalize(&uv.tangent);
	uv.bitangent = vec_vectoriel(hit.object->shape.ring.normal, uv.tangent);
	vec_normalize(&uv.bitangent);
	diff = vec_sub(hit.point, *hit.object->shape.ring.center);
	uv.u = vec_dot(diff, uv.tangent);
	uv.v = vec_dot(diff, uv.bitangent);
	r = sqrt(uv.u * uv.u + uv.v * uv.v);
	uv.v = 0.5 + atan2(uv.v, uv.u) / (2 * PI);
	uv.u = (r - hit.object->shape.ring.inner_rad)
		/ (hit.object->shape.ring.outer_rad - hit.object->shape.ring.inner_rad);
	return (uv);
}

/* u = 0.5 + atan2(Pz, Px) / (2 * PI)
v = 0,5 + asin(Py) / (PI)*/
t_uv	get_uv_sp(t_hit hit)
{
	t_uv				uv;
	static const t_vec	up = {.x = 0, .y = 1, .z = 0};
	static const t_vec	depth = {.x = 0, .y = 0, .z = 1};

	uv.tangent = vec_vectoriel(hit.normal, up);
	if (vec_square(uv.tangent) < 0.0001)
		uv.tangent = vec_vectoriel(hit.normal, depth);
	vec_normalize(&uv.tangent);
	uv.bitangent = vec_vectoriel(hit.normal, uv.tangent);
	uv.u = 0.5 + atan2(hit.normal.z, hit.normal.x) / (2 * PI)
		+ hit.object->shape.sphere.rotation / (2 * PI);
	uv.v = 0.5 + asin(hit.normal.y) / PI;
	if (hit.object->texture.type == TEX_IMG)
		return (uv);
	uv.case_idx = (int)(uv.u * hit.object->texture.scale)
		+ (int)(uv.v * hit.object->texture.scale);
	return (uv);
}
