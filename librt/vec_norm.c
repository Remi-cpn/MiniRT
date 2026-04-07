/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_norm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 14:12:43 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/07 15:46:54 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/librt.h"

double	vec_norm(t_vec *v)
{
	return (sqrt(vec_square(v)));
}

double	vec_square(t_vec *v)
{
	const double	x = v->x;
	const double	y = v->y;
	const double	z = v->z;
	
	return (x * x + y * y + z * z);
}