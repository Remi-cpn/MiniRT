/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 08:42:27 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/01 16:17:55 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"

void	calcul_viewport(t_camera *cam, double ratio)
{
	double				fov_rad;
	static const t_vec	up = {.x = 0, .y = 1, .z = 0};
	static const t_vec	depth = {.x = 0, .y = 0, .z = 1};

	cam->focal = 1.0;
	if (vec_square(cam->hor_n) < 0.0001)
	{
		cam->hor_n = vec_vectoriel(cam->dir, up);
		if (vec_square(cam->hor_n) < 0.0001)
			cam->hor_n = vec_vectoriel(cam->dir, depth);
		vec_normalize(&cam->hor_n);
	}
	cam->ver_n = vec_vectoriel(cam->hor_n, cam->dir);
	vec_normalize(&cam->ver_n);
	cam->hor_n = vec_vectoriel(cam->dir, cam->ver_n);
	vec_normalize(&cam->hor_n);
	fov_rad = 2 * tan(cam->fov * PI / 360.0);
	cam->hor = vec_mult_scalar(cam->hor_n, ratio * fov_rad);
	cam->ver = vec_mult_scalar(cam->ver_n, fov_rad);
	cam->corner = vec_sub(cam->origin, vec_mult_scalar(cam->hor, 0.5));
	cam->corner = vec_sub(cam->corner, vec_mult_scalar(cam->ver, 0.5));
	cam->corner = vec_add(cam->corner, vec_mult_scalar(cam->dir, cam->focal));
}

void	init_world(t_data *d, t_world *w)
{
	if (!d->pixels)
		d->pixels = ft_calloc(d->win_info.width * d->win_info.height,
				sizeof(mlx_color));
	if (!d->pixels)
		exit_prog(d, ERROR_MALLOC, ERROR_MALLOC_MSG);
	vec_normalize(&(w->camera.dir));
	calcul_viewport(&(w->camera), (double)d->win_info.width
		/ (double)d->win_info.height);
}
