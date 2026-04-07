/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operator.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 15:47:34 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/07 16:20:29 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/librt.h"

t_vec	vec_add(t_vec v1, t_vec v2)
{
	t_vec	v;

	v.x = v1.x + v2.x;
	v.y = v1.y + v2.y;
	v.z = v1.z + v2.z;
	return (v);
}

t_vec	vec_sub(t_vec v1, t_vec v2)
{
	t_vec	v;

	v.x = v1.x - v2.x;
	v.y = v1.y - v2.y;
	v.z = v1.z - v2.z;
	return (v);
}

double	vec_dot(t_vec *v1, t_vec *v2)
{	
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vec	vec_mult_scalar(t_vec v_src, double d)
{
	t_vec	v;
	
	v.x = v_src.x * d;
	v.y = v_src.y * d;
	v.z = v_src.z * d;
	return (v);
}
