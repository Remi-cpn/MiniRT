/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:16:56 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/10 08:34:54 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

/* Check if a ray hits a sphere */
/* a = dir² */
/* b = 2 * (oc · dir) */
/* c = oc² - radius² */
/* discriminant = b² - 4ac */
double	hit_sphere(t_world *w, t_ray ray)
{
	t_vec			oc;
	t_second_degret	sd;
	double			t;
	double			discriminant;

	sd.a = vec_dot(ray.dir, ray.dir);
	oc = vec_sub(ray.origin, w->sphere.center);
	sd.b = 2 * vec_dot(oc, ray.dir);
	sd.c = vec_dot(oc, oc) - w->sphere.radius * w->sphere.radius;
	discriminant = sd.b * sd.b - 4 * sd.a * sd.c;
	if (discriminant < 0)
		return (-1);
	t = (-sd.b - sqrt(discriminant)) / (2 * sd.a);
	return (t);
}
