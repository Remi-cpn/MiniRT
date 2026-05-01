/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_merge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 09:46:02 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/27 09:57:36 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static int	shadow_ray(t_world *w, t_hit *hit_origin, t_vec light_dir,
		double light_n)
{
	t_ray	shadow_ray;
	t_hit	hit;

	shadow_ray.dir = light_dir;
	shadow_ray.origin = vec_add(hit_origin->point,
			vec_mult_scalar(hit_origin->normal, 0.01));
	hit = find_closest_hit(w, shadow_ray, 1);
	if (hit.hit && hit.t > 0 && hit.t < light_n && hit.t < SHADOW_DIST)
		return (1);
	return (0);
}

static double	calc_specular(t_hit *hit, double coef_diffuse,
		t_vec light_dir, t_vec cam)
{
	t_vec	reflect;
	t_vec	view_dir;

	reflect = vec_sub(vec_mult_scalar(hit->normal, 2.0 * coef_diffuse),
			light_dir);
	vec_normalize(&reflect);
	view_dir = vec_sub(cam, hit->point);
	vec_normalize(&view_dir);
	return (vec_dot(reflect, view_dir));
}

void	calc_one_light(t_world *w, t_hit *hit, t_light *light,
		t_light_managment *l)
{
	t_vec	light_dir;
	double	light_norm;
	double	coef_d;
	double	coef_specular;

	light_dir = vec_sub(light->position, hit->point);
	light_norm = vec_norm(light_dir);
	vec_normalize(&light_dir);
	coef_d = vec_dot(hit->normal, light_dir);
	if (!(coef_d <= 0.001 || shadow_ray(w, hit, light_dir,
				light_norm)))
	{
		l->diffuse[R] += (light->color.r / 255.0) * coef_d * light->intensity;
		l->diffuse[G] += (light->color.g / 255.0) * coef_d * light->intensity;
		l->diffuse[B] += (light->color.b / 255.0) * coef_d * light->intensity;
		coef_specular = calc_specular(hit, coef_d, light_dir, w->camera.origin);
		if (coef_specular > EPS)
		{
			coef_specular = pow(coef_specular, SHINY) * KS * light->intensity;
			l->specular[R] += (light->color.r / 255.0) * coef_specular;
			l->specular[G] += (light->color.g / 255.0) * coef_specular;
			l->specular[B] += (light->color.b / 255.0) * coef_specular;
		}
	}
}
