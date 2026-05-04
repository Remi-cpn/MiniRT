/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:17:52 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/02 18:12:26 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

void	reparse(t_data *d)
{
	free(d->map.objects);
	d->map.objects = NULL;
	d->map.nb_obj = 0;
	d->map = parsing(d, d->filename);
	d->input.r = false;
}

static bool	update_cam_orbit(t_data *d, double speed)
{
	if (d->input.left || d->input.right
		|| d->input.up || d->input.down)
		orbit_movement(d, ORBIT_SPEED);
	else if (d->input.w || d->input.s)
		orbit_zoom(d, speed / 50);
	else if (d->input.a || d->input.d
		|| d->input.ctrl || d->input.space)
	{
		d->cam_target = -1;
		linear_movement(d, &d->map.camera, speed);
	}
	else if (d->input.n == true)
		snap_cam_to_planet(d, +1);
	else if (d->input.p == true)
		snap_cam_to_planet(d, -1);
	else if (d->input.r == true)
		reparse(d);
	else
		return (false);
	follow_cam(d);
	return (true);
}

bool	update_cam(t_data *d, double speed, double speed_rot)
{
	if (d->cam_target >= 0)
		return (update_cam_orbit(d, speed));
	return (update_cam_free(d, speed, speed_rot));
}
