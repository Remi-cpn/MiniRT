/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:17:52 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/02 12:13:27 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

static void	linear_movement(t_data *d, t_camera *cam, double speed)
{
	d->cam_target = -1;
	if (d->input.w == true)
		cam->origin = vec_add(cam->origin, vec_mult_scalar(cam->dir, speed));
	if (d->input.s == true)
		cam->origin = vec_add(cam->origin, vec_mult_scalar(cam->dir, -speed));
	if (d->input.a == true)
		cam->origin = vec_add(cam->origin, vec_mult_scalar(cam->hor_n, -speed));
	if (d->input.d == true)
		cam->origin = vec_add(cam->origin, vec_mult_scalar(cam->hor_n, speed));
	if (d->input.ctrl == true)
		cam->origin = vec_add(cam->origin, vec_mult_scalar(cam->ver_n, -speed));
	if (d->input.space == true)
		cam->origin = vec_add(cam->origin, vec_mult_scalar(cam->ver_n, speed));
}

static void	rotate_movement(t_data *d, t_camera *cam, double speed_init)
{
	double	speed;

	speed = speed_init;
	if (d->input.up == true)
		cam->dir = vec_add(vec_mult_scalar(cam->dir, cos(speed)),
				vec_mult_scalar(cam->ver_n, -sin(speed)));
	else if (d->input.down == true)
		cam->dir = vec_add(vec_mult_scalar(cam->dir, cos(speed)),
				vec_mult_scalar(cam->ver_n, sin(speed)));
	if (d->input.left == true)
		cam->dir = vec_add(vec_mult_scalar(cam->dir, cos(speed)),
				vec_mult_scalar(cam->hor_n, -sin(speed)));
	else if (d->input.right == true)
		cam->dir = vec_add(vec_mult_scalar(cam->dir, cos(speed)),
				vec_mult_scalar(cam->hor_n, sin(speed)));
	vec_normalize(&(cam->dir));
}

static void	update_fov(t_data *d, t_camera *cam, double speed)
{
	if (d->input.i == true)
		cam->fov += speed * 10;
	else if (d->input.o == true)
		cam->fov -= speed * 10;
}

static void	reparse(t_data *d)
{
	free(d->map.objects);
	d->map.objects = NULL;
	d->map.nb_obj = 0;
	d->map = parsing(d, d->filename);
	d->input.r = false;
}

bool	update_cam(t_data *d, double speed, double speed_rot)
{
	if (d->input.a == true || d->input.w == true
		|| d->input.d == true || d->input.s == true
		|| d->input.ctrl == true || d->input.space == true)
		linear_movement(d, &d->map.camera, speed);
	else if (d->input.left == true || d->input.right == true
		|| d->input.down == true || d->input.up == true)
		rotate_movement(d, &d->map.camera, speed_rot);
	else if (d->input.i == true || d->input.o == true)
		update_fov(d, &(d->map.camera), speed);
	else if (d->input.r == true)
		reparse(d);
	else if (d->input.n == true)
		snap_cam_to_planet(d, +1);
	else if (d->input.p == true)
		snap_cam_to_planet(d, -1);
	else
		return (false);
	calcul_viewport(&d->map.camera, (double)d->win_info.width
		/ (double)d->win_info.height);
	return (true);
}
