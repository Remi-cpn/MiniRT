/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:16:56 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/14 15:21:20 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include <math.h>

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
