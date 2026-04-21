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

static double	hit_cap(t_plane plane, t_ray ray, double radius)
{
	t_vec	hit_point;
	double	t;
	double	dir;
	t_vec	po;
	t_vec	diff;

	dir = vec_dot(plane.normal, ray.dir);
	if (fabs(dir) < 0.0001)
		return (-1.0);
	po = vec_sub(plane.point, ray.origin);
	t = vec_dot(po, plane.normal) / dir;
	if (t < 0.001)
		return (-1.0);
	hit_point = vec_add(ray.origin, vec_mult_scalar(ray.dir, t));
	diff = vec_sub(hit_point, plane.point);
	if (vec_dot(diff, diff) > radius * radius)
		return (-1.0);
	return (t);
}

/* A_vec = D - (D·v)*v       // composante de D perpendiculaire à l'axe
B_vec = w - (w·v)*v       // composante de w perpendiculaire à l'axe
a = A_vec · A_vec
b = 2 * (A_vec · B_vec)
c = B_vec · B_vec - r²*/
static void	coeff_cyl(double coeff[3], t_cylinder cylinder, t_ray ray)
{
	t_vec	oc;
	t_vec	a_vec;
	t_vec	b_vec;

	oc = vec_sub(ray.origin, cylinder.center);
	a_vec = vec_sub(ray.dir, vec_mult_scalar(cylinder.axis,
				vec_dot(ray.dir, cylinder.axis)));
	b_vec = vec_sub(oc, vec_mult_scalar(cylinder.axis,
				vec_dot(oc, cylinder.axis)));
	coeff[0] = vec_dot(a_vec, a_vec);
	coeff[1] = vec_dot(a_vec, b_vec);
	coeff[2] = vec_dot(b_vec, b_vec) - cylinder.radius * cylinder.radius;
}

/* 
delta = b² - 4*a*c
delta < 0 → pas d'intersection
delta >= 0 → t = (-b ± sqrt(delta)) / (2*a)
projection = (P(t) - C) · v
0 <= projection <= h       // sinon le hit est hors du cylindre
hit_point = ray.origin + ray.dir * t
proj = (hit_point - cylinder.center) . cylinder.axis
*/
double	hit_tube(t_cylinder cylinder, t_ray ray)
{
	t_vec	hit_point;
	double	coeff[3];
	double	t;
	double	discriminant;
	double	proj;

	coeff_cyl(coeff, cylinder, ray);
	discriminant = coeff[1] * coeff[1] - coeff[0] * coeff[2];
	if (discriminant < 0)
		return (-1.0);
	t = (-coeff[1] - sqrt(discriminant)) / coeff[0];
	if (t < 0.001)
		t = (-coeff[1] + sqrt(discriminant)) / coeff[0];
	if (t < 0.001)
		return (-1.0);
	hit_point = vec_add(ray.origin, vec_mult_scalar(ray.dir, t));
	proj = vec_dot(vec_sub(hit_point, cylinder.center), cylinder.axis);
	if (proj < -cylinder.height / 2.0 || proj > cylinder.height / 2.0)
		return (-1.0);
	return (t);
}

double	hit_cylinder(t_cylinder cylinder, t_ray ray)
{
	double	t_tube;
	double	t_cap1;
	double	t_cap2;
	double	t;
	t_plane	cap;

	t = -1.0;
	t_tube = hit_tube(cylinder, ray);
	if (t_tube != -1.0)
		t = t_tube;
	cap.normal = vec_mult_scalar(cylinder.axis, -1);
	cap.point = vec_add(cylinder.center, vec_mult_scalar(
				vec_mult_scalar(cylinder.axis, -1), cylinder.height / 2.0));
	t_cap1 = hit_cap(cap, ray, cylinder.radius);
	if (t_cap1 != -1.0 && (t == -1.0 || t_cap1 < t))
		t = t_cap1;
	cap.normal = cylinder.axis;
	cap.point = vec_add(cylinder.center,
			vec_mult_scalar(cylinder.axis, cylinder.height / 2.0));
	t_cap2 = hit_cap(cap, ray, cylinder.radius);
	if (t_cap2 != -1.0 && (t == -1.0 || t_cap2 < t))
		t = t_cap2;
	return (t);
}
