/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   librt.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 14:07:20 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/08 17:27:04 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBRT_H
# define LIBRT_H

# include "math.h"

/* ——— Struct prototypes ———————————————————————————————————————————————————— */
typedef struct s_vec
{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_color
{
	char	r;
	char	g;
	char	b;
}	t_color;

/* ——— Function prototypes —————————————————————————————————————————————————— */
double	vec_norm(t_vec *v);
double	vec_square(t_vec *v);
double	vec_dot(t_vec *v1, t_vec *v2);
t_vec	vec_mult_scalar(t_vec v, double d);
t_vec	vec_add(t_vec v1, t_vec v2);
t_vec	vec_sub(t_vec v1, t_vec v2);

#endif