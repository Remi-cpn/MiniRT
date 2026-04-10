/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_norm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 14:12:43 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/10 08:49:19 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/librt.h"
#include <math.h>

void	vec_normalize(t_vec *v)
{
	*v = vec_mult_scalar(*v, 1.0 / vec_norm(*v));
}

double	vec_norm(t_vec v)
{
	return (sqrt(vec_square(v)));
}

double	vec_square(t_vec v)
{
	const double	x = v.x;
	const double	y = v.y;
	const double	z = v.z;

	return (x * x + y * y + z * z);
}

void	vec_init(t_vec *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}
