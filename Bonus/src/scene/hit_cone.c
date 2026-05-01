/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 15:20:07 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/14 16:41:30 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include <math.h>

static int	solve_quadratic(double a, double b, double c, double *t)
{
	double	disc;
	double	sqrt_disc;

	disc = b * b - a * c;
	if (disc < 0)
		return (0);
	sqrt_disc = sqrt(disc);
	*t = (-b - sqrt_disc) / a;
	if (*t < 0.001)
		*t = (-b + sqrt_disc) / a;
	return (*t >= 0.001);
}

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

double	hit_cone(t_cone cone, t_ray ray)
{
	double	coeff[3];
	double	t;
	t_vec	hit;

	get_coeff(cone, ray, coeff);
	if (!solve_quadratic(coeff[0], coeff[1], coeff[2], &t))
		return (-1.0);
	hit = vec_add(ray.origin, vec_mult_scalar(ray.dir, t));
	if (vec_dot(vec_sub(hit, cone.apex), cone.axis) < EPS)
		return (-1.0);
	return (t);
}
