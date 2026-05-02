/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 15:20:48 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/14 15:21:03 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minirt_bonus.h"
#include <math.h>

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
