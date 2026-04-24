/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 09:46:02 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/19 12:14:23 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static int	is_light_inside(t_world *w)
{
	int		i;
	t_vec	diff;

	i = -1;
	while (++i < w->nb_obj)
	{
		if (w->objects[i].type != OBJ_SPHERE)
			continue ;
		diff = vec_sub(w->lights.position, w->objects[i].shape.sphere.center);
		if (vec_norm(diff) < w->objects[i].shape.sphere.radius)
			return (1);
	}
	return (0);
}

static t_vec	shadow_ray(t_world *w, t_hit *hit_origin, t_vec light_dir,
	double light_n)
{
	t_ray	shadow_ray;
	t_hit	hit;
	t_vec	attenuation;
	t_vec	diff;

	if (hit_origin->object && hit_origin->object->type == OBJ_SPHERE)
	{
		diff = vec_sub(w->lights.position, hit_origin->object->shape.sphere.center);
		if (vec_norm(diff) < hit_origin->object->shape.sphere.radius)
			return ((t_vec){1.0, 1.0, 1.0});
	}
	vec_init(&attenuation, 1.0, 1.0, 1.0);
	shadow_ray.dir = light_dir;
	shadow_ray.origin = vec_add(hit_origin->point, vec_mult_scalar(hit_origin->normal, 0.001));
	while (1)
	{
		hit = find_closest_hit(w, shadow_ray, 1);
		if (!hit.hit || hit.t <= 0.001 || hit.t >= light_n)
			return (attenuation);
		if (hit.object->color.a == 255)
			return ((t_vec){0.0, 0.0, 0.0});
		attenuation.x *= (1 - (hit.object->color.a / 255.0)) * (hit.object->color.r / 255.0);
		attenuation.y *= (1 - (hit.object->color.a / 255.0)) * (hit.object->color.g / 255.0);
		attenuation.z *= (1 - (hit.object->color.a / 255.0)) * (hit.object->color.b / 255.0);
		light_n -= hit.t;
		shadow_ray.origin = vec_add(hit.point, vec_mult_scalar(shadow_ray.dir, 0.001));
	}
}

static void	init_vars(t_world *w, double *ambient, double *diffuse)
{
	ambient[R] = (w->ambient.r / 255.0) * w->ambient_ratio;
	ambient[G] = (w->ambient.g / 255.0) * w->ambient_ratio;
	ambient[B] = (w->ambient.b / 255.0) * w->ambient_ratio;
	diffuse[R] = 0.0;
	diffuse[G] = 0.0;
	diffuse[B] = 0.0;
}

static void	set_light(double *light, double *ambient, double *diffuse)
{
	light[R] = ambient[R] + diffuse[R];
	light[G] = ambient[G] + diffuse[G];
	light[B] = ambient[B] + diffuse[B];
	if (light[R] > 1.0)
		light[R] = 1.0;
	if (light[G] > 1.0)
		light[G] = 1.0;
	if (light[B] > 1.0)
		light[B] = 1.0;
}

void	light(t_world *w, t_hit *hit, mlx_color *color)
{
	t_vec				light_dir;
	double				coef_diffuse;
	double				light_norm;
	t_light_managment	l;
	t_vec				shadow;

	init_vars(w, l.ambient, l.diffuse);
	light_dir = vec_sub(w->lights.position, hit->point);
	light_norm = vec_norm(light_dir);
	vec_normalize(&light_dir);
	coef_diffuse = vec_dot(hit->normal, light_dir);
	if (coef_diffuse <= EPS && is_light_inside(w))
		coef_diffuse = fabs(coef_diffuse);
	shadow =  shadow_ray(w, hit, light_dir, light_norm);
	if (coef_diffuse > EPS && (shadow.x > 0.0 || shadow.y > 0.0 || shadow.z > 0.0))
	{
		l.diffuse[R] = (w->lights.color.r / 255.0) * coef_diffuse
			* w->lights.intensity * shadow.x;
		l.diffuse[G] = (w->lights.color.g / 255.0) * coef_diffuse
			* w->lights.intensity * shadow.y;
		l.diffuse[B] = (w->lights.color.b / 255.0) * coef_diffuse
			* w->lights.intensity * shadow.z;
	}
	set_light(l.light, l.ambient, l.diffuse);
	color->r = hit->pixel_color.r * l.light[R];
	color->g = hit->pixel_color.g * l.light[G];
	color->b = hit->pixel_color.b * l.light[B];
	color->a = 255;
}
