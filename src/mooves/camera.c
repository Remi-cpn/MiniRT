
#include "../../include/minirt.h"
#include <math.h>
#include <stdbool.h>

static void	linear_moovement(t_data *d, t_camera *cam, double speed)
{
	if (d->input.w == true)
		cam->origin = vec_add(cam->origin, vec_mult_scalar(cam->dir, speed));	
	else if (d->input.s == true)
		cam->origin = vec_add(cam->origin, vec_mult_scalar(cam->dir, -speed));	
	else if (d->input.a == true)
		cam->origin = vec_add(cam->origin, vec_mult_scalar(cam->hor_n, -speed));	
	else if (d->input.d == true)
		cam->origin = vec_add(cam->origin, vec_mult_scalar(cam->hor_n, speed));	
	else if (d->input.ctrl == true)
		cam->origin = vec_add(cam->origin, vec_mult_scalar(cam->ver_n, -speed));	
	else if (d->input.space == true)
		cam->origin = vec_add(cam->origin, vec_mult_scalar(cam->ver_n, speed));	
}

static void	rotate_moovement(t_data *d, t_camera *cam, double speed_init)
{
	double	speed;

	speed = speed_init / 10;
	if (d->input.up == true)
		cam->dir = vec_add(vec_mult_scalar(cam->dir, cos(speed)), vec_mult_scalar(cam->ver_n, -sin(speed)));	
	else if (d->input.down == true)
		cam->dir = vec_add(vec_mult_scalar(cam->dir, cos(speed)), vec_mult_scalar(cam->ver_n, sin(speed)));	
	else if (d->input.left == true)
		cam->dir = vec_add(vec_mult_scalar(cam->dir, cos(speed)), vec_mult_scalar(cam->hor_n, -sin(speed)));	
	else if (d->input.right == true)
		cam->dir = vec_add(vec_mult_scalar(cam->dir, cos(speed)), vec_mult_scalar(cam->hor_n, sin(speed)));	
	vec_normalize(&(cam->dir));
}

static void	update_fov(t_data *d, t_camera *cam, double speed)
{
	if (d->input.i == true)
		cam->focal += speed;
	else if (d->input.o == true)
		cam->focal -= speed;
}

bool	update_cam(t_data *d, double speed)
{
	if (d->input.a == true || d->input.w == true
			|| d->input.d == true || d->input.s == true
			|| d->input.ctrl == true || d->input.space == true)
		linear_moovement(d, &d->map.camera, speed);
	else if (d->input.left == true || d->input.right == true
			|| d->input.down == true || d->input.up == true)
		rotate_moovement(d, &d->map.camera, speed);
	else if (d->input.i == true || d->input.o == true)
		update_fov(d, &(d->map.camera), speed);
	else
		return (false);
	calcul_viewport(&d->map.camera, (double)d->win_info.width / (double)d->win_info.height);
	return (true);
}
