/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 14:15:33 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/14 16:23:22 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"

t_ray	get_ray(t_camera cam, double i_hor, double i_ver)
{
	t_ray	ray;
	t_vec	temp1;
	t_vec	temp2;

	ray.origin = cam.origin;
	temp1 = vec_mult_scalar(cam.hor, i_hor);
	temp2 = vec_mult_scalar(cam.ver, i_ver);
	ray.dir = vec_add(cam.corner, temp1);
	ray.dir = vec_add(ray.dir, temp2);
	ray.dir = vec_sub(ray.dir, cam.origin);
	vec_normalize(&ray.dir);
	return (ray);
}
