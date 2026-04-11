/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 08:42:27 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/11 17:28:10 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include <stdlib.h>

static void	init_cam(t_camera *cam, double ratio)
{
	double	fov_rad;

	cam->focal = 1.0;
	fov_rad = 2 * tan(cam->fov * 3.14159265358979323846 / 360.0);
	vec_init(&cam->hor, ratio * fov_rad, 0, 0);
	vec_init(&cam->ver, 0, fov_rad, 0);
	vec_init(&cam->corner, 0 - cam->hor.x / 2, 0 - cam->ver.y / 2, -cam->focal);
}

void	init_world(t_data *d, t_world *w)
{
	d->pixels = ft_calloc(d->win_info.width * d->win_info.height, sizeof(mlx_color));
	if (!d->pixels)
		exit_prog(d, ERROR_MALLOC, ERROR_MALLOC_MSG);
	init_cam(&(w->camera), (double)d->win_info.width / (double)d->win_info.height);
}

