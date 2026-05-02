/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_ring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 11:42:29 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/02 12:35:13 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include <math.h>

double	hit_ring(t_ring ring, t_ray ray)
{
	t_vec	hit_point;
	double	t;
	double	dir;
	t_vec	po;
	t_vec	diff;

	dir = vec_dot(ring.normal, ray.dir);
	if (fabs(dir) < 0.0001)
		return (-1.0);
	po = vec_sub(*ring.center, ray.origin);
	t = vec_dot(po, ring.normal) / dir;
	if (t < 0.001)
		return (-1.0);
	hit_point = vec_add(ray.origin, vec_mult_scalar(ray.dir, t));
	diff = vec_sub(hit_point, *ring.center);
	if (ring.inner_rad * ring.inner_rad >= vec_dot(diff, diff)
		|| vec_dot(diff, diff) > ring.outer_rad * ring.outer_rad)
		return (-1.0);
	return (t);
}
