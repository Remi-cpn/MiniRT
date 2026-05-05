/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 15:20:07 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/04 17:29:46 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minirt_bonus.h"
#include <math.h>

static void	get_coeff(t_cone cone, t_ray ray, double coeff[3])
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
}

static int	valid_cone_hit(t_cone cone, t_ray ray, double t, double *out)
{
	t_vec	hit;
	double	dot;

	if (t < 0.001)
		return (0);
	hit = vec_add(ray.origin, vec_mult_scalar(ray.dir, t));
	dot = vec_dot(vec_sub(hit, cone.apex), cone.axis);
	if (dot < 0 || dot > cone.height)
		return (0);
	*out = t;
	return (1);
}

double	hit_cone(t_cone cone, t_ray ray)
{
	double	coeff[3];
	double	disc;
	double	t1;
	double	t2;
	t_plane	cap;

	get_coeff(cone, ray, coeff);
	disc = coeff[1] * coeff[1] - coeff[0] * coeff[2];
	t1 = -1.0;
	t2 = -1.0;
	if (disc >= 0)
	{
		disc = sqrt(disc);
		t1 = (-coeff[1] - disc) / coeff[0];
		t2 = (-coeff[1] + disc) / coeff[0];
		if (!valid_cone_hit(cone, ray, t1, &t1))
			t1 = -1.0;
		if (!valid_cone_hit(cone, ray, t2, &t2))
			t2 = -1.0;
	}
	if (t2 != -1.0 && (t1 == -1.0 || t2 < t1))
		t1 = t2;
	cap.normal = cone.axis;
	cap.point = vec_add(cone.apex, vec_mult_scalar(cone.axis, cone.height));
	t2 = hit_cap(cap, ray, cone.height * tan(cone.angle));
	if (t2 != -1.0 && (t1 == -1.0 || t2 < t1))
		t1 = t2;
	return (t1);
}
