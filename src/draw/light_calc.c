/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_calc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 09:46:02 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/13 16:59:34 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static int	shadow_ray(t_world *w, t_vec p, t_vec light_dir, double light_n)
{
	t_ray	shadow_ray;
	t_hit	hit;

	shadow_ray.dir = light_dir;
	shadow_ray.origin = vec_add(p, vec_mult_scalar(shadow_ray.dir, 0.001));
	hit = find_closest_hit(w, shadow_ray, 1, light_n);
	if (hit.hit && hit.t > 0 && hit.t < light_n)
		return (1);
	return (0);
}

static void	init_vars(t_world *w, double *ambient, double *diffuse)
{
	ambient[R] = (w->ambient.r / 255.0) * w->ambient_ratio;
	ambient[G] = (w->ambient.g / 255.0) * w->ambient_ratio;
	ambient[B] = (w->ambient.b / 255.0) * w->ambient_ratio;
	diffuse[R] = 0;
	diffuse[G] = 0;
	diffuse[B] = 0;
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
	t_vec	light_dir;
	double	coef_diffuse;
	double	diffuse[RGB];
	double	ambient[RGB];
	double	light[RGB];
	double	light_n;

	init_vars(w, ambient, diffuse);
	light_dir = vec_sub(w->lights.position, hit->point);
	light_n = vec_norm(light_dir);
	vec_normalize(&light_dir);
	coef_diffuse = vec_dot(hit->normal, light_dir);
	if (!(coef_diffuse <= 0.001 || shadow_ray(w, hit->point, light_dir, light_n)))
	{
		diffuse[R] = (w->lights.color.r / 255.0) * coef_diffuse * w->lights.intensity;
		diffuse[G] = (w->lights.color.g / 255.0) * coef_diffuse * w->lights.intensity;
		diffuse[B] = (w->lights.color.b / 255.0) * coef_diffuse * w->lights.intensity;
	}
	set_light(light, ambient, diffuse);
	color->r = hit->object->color.r * light[R];
	color->g = hit->object->color.g * light[G];
	color->b = hit->object->color.b * light[B];
	color->a = 255;
}
