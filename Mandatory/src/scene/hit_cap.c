/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 10:38:16 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/02 10:40:19 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include <math.h>

double	hit_cap(t_plane plane, t_ray ray, double radius)
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
