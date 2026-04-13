/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:16:56 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/13 14:27:32 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include <math.h>

/* A_vec = D - (D·v)*v       // composante de D perpendiculaire à l'axe
B_vec = w - (w·v)*v       // composante de w perpendiculaire à l'axe
a = A_vec · A_vec
b = 2 * (A_vec · B_vec)
c = B_vec · B_vec - r²*/
static void coeff_cyl(double coeff[3], t_cylinder cylinder, t_ray ray)
{
	t_vec	oc; // ray.origin - cylinder.center
	t_vec	a_vec;   // ray.dir - (ray.dir · cylinder.axis) * cylinder.axis
    t_vec	b_vec;   // oc - (oc · cylinder.axis) * cylinder.axis

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
double	hit_cylinder(t_cylinder cylinder, t_ray ray)
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

double	hit_plane(t_plane plane, t_ray ray)
{
	double	t;
	double	dir;
	t_vec	po;

	dir = vec_dot(plane.normal, ray.dir);
	if (fabs(dir) < 0.0001)
		return (-1.0);
	po = vec_sub(plane.point, ray.origin);
	t = vec_dot(po, plane.normal) / dir;
	if (t < 0.001)
		return (-1.0);
	return (t);
}

double	hit_sphere(t_sphere sphere, t_ray ray)
{
	t_vec	oc;
	double	coeff[3];
	double	t;
	double	discriminant;

	oc = vec_sub(ray.origin, sphere.center);
	coeff[0] = vec_dot(ray.dir, ray.dir);
	coeff[1] = vec_dot(oc, ray.dir);
	coeff[2] = vec_dot(oc, oc) - sphere.radius * sphere.radius;
	discriminant = coeff[1] * coeff[1] - coeff[0] * coeff[2];
	if (discriminant < 0)
		return (-1.0);
	t = (-coeff[1] - sqrt(discriminant)) / coeff[0];
	if (t < 0.001)
		t = (-coeff[1] + sqrt(discriminant)) / coeff[0];
	if (t < 0.001)
		return (-1.0);
	return (t);
}
