/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_hit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:02:25 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/02 12:02:01 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/world.h"

static void	fill_hit_details_cylinder(t_hit *hit)
{
	t_vec	oc;
	t_vec	new_center;
	double	proj;

	oc = vec_sub(hit->point, hit->object->shape.cylinder.center);
	new_center = vec_proj(oc, hit->object->shape.cylinder.axis);
	proj = vec_dot(oc, hit->object->shape.cylinder.axis);
	if (fabs(proj - hit->object->shape.cylinder.height / 2.0) < 0.001)
		hit->normal = hit->object->shape.cylinder.axis;
	else if (fabs(proj + hit->object->shape.cylinder.height / 2.0) < 0.001)
		hit->normal = vec_mult_scalar(hit->object->shape.cylinder.axis, -1.0);
	else
		hit->normal = vec_sub(oc, new_center);
}

static void	fill_hit_details_cone(t_hit *hit)
{
	t_vec	co;
	t_vec	v;
	double	k;
	double	dot;

	co = vec_sub(hit->point, hit->object->shape.cone.apex);
	v = hit->object->shape.cone.axis;
	dot = vec_dot(co, v);
	if (fabs(dot - hit->object->shape.cone.height) < 0.001)
	{
		hit->normal = v;
		return ;
	}
	k = pow(tan(hit->object->shape.cone.angle), 2);
	hit->normal = vec_sub(co, vec_mult_scalar(v, (1 + k) * dot));
}

void	fill_hit_details(t_hit *hit, t_ray ray)
{
	hit->point = vec_add(ray.origin, vec_mult_scalar(ray.dir, hit->t));
	if (hit->object->type == OBJ_SPHERE)
		hit->normal = vec_sub(hit->point, hit->object->shape.sphere.center);
	else if (hit->object->type == OBJ_PLANE)
		hit->normal = hit->object->shape.plane.normal;
	else if (hit->object->type == OBJ_CONE)
		fill_hit_details_cone(hit);
	else if (hit->object->type == OBJ_CYLINDER)
		fill_hit_details_cylinder(hit);
	else if (hit->object->type == OBJ_RING)
		hit->normal = hit->object->shape.ring.normal;
	if (hit->object->type == OBJ_SPHERE || hit->object->type == OBJ_PLANE
		|| hit->object->type == OBJ_CYLINDER || hit->object->type == OBJ_CONE
		|| hit->object->type == OBJ_RING)
		vec_normalize(&hit->normal);
	if (vec_dot(hit->normal, ray.dir) > 0)
		hit->normal = vec_mult_scalar(hit->normal, -1.0);
}
