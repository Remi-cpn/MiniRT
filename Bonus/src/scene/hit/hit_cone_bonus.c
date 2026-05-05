/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 15:20:07 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/05 10:02:09 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minirt_bonus.h"
#include <math.h>

static double	get_coeff(t_cone cone, t_ray ray, double coeff[3])
{
	t_vec	oc;
	t_vec	d_normal;
	t_vec	oc_normal;
	double	k;

	k = tan(cone.angle) * tan(cone.angle);
	oc = vec_sub(ray.origin, cone.apex);
	d_normal = vec_sub(ray.dir, vec_proj(ray.dir, cone.axis));
	oc_normal = vec_sub(oc, vec_proj(oc, cone.axis));
	coeff[0] = vec_dot(d_normal, d_normal) - k * vec_dot(ray.dir, cone.axis)
		* vec_dot(ray.dir, cone.axis);
	coeff[1] = vec_dot(d_normal, oc_normal) - k * vec_dot(ray.dir, cone.axis)
		* vec_dot(oc, cone.axis);
	coeff[2] = vec_dot(oc_normal, oc_normal) - k * vec_dot(oc, cone.axis)
		* vec_dot(oc, cone.axis);
	return (coeff[1] * coeff[1] - coeff[0] * coeff[2]);
}

static double	valid_cone_hit(t_cone cone, t_ray ray)
{
	t_vec	hit;
	double	dot;
	double	coeff[3];
	double	disc;
	double	t;

	t = -1.0;
	disc = get_coeff(cone, ray, coeff);
	if (disc >= 0)
	{
		disc = sqrt(disc);
		t = (-coeff[1] - disc) / coeff[0];
		if (t < 0.001)
			t = (-coeff[1] + disc) / coeff[0];
		hit = vec_add(ray.origin, vec_mult_scalar(ray.dir, t));
		dot = vec_dot(vec_sub(hit, cone.apex), cone.axis);
		if (dot < 0 || dot > cone.height)
			t = (-coeff[1] + disc) / coeff[0];
		hit = vec_add(ray.origin, vec_mult_scalar(ray.dir, t));
		dot = vec_dot(vec_sub(hit, cone.apex), cone.axis);
		if (dot < 0 || dot > cone.height)
			t = -1.0;
	}
	return (t);
}

double	hit_cone(t_cone cone, t_ray ray)
{
	double	t1;
	double	t2;
	t_plane	cap;

	t1 = valid_cone_hit(cone, ray);
	cap.normal = cone.axis;
	cap.point = vec_add(cone.apex, vec_mult_scalar(cone.axis, cone.height));
	t2 = hit_cap(cap, ray, cone.height * tan(cone.angle));
	if (t2 != -1.0 && (t1 == -1.0 || t2 < t1))
		t1 = t2;
	return (t1);
}
