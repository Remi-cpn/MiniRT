/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 09:46:02 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/10 10:23:10 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static int	shadow_ray(t_world *w, t_vec p, t_vec light_dir)
{
	t_ray	shadow_ray;
	t_hit	hit;

	shadow_ray.dir = light_dir;
	shadow_ray.origin = vec_add(p, vec_mult_scalar(shadow_ray.dir, 0.001));
	hit = find_closest_hit(w, shadow_ray);
	if (hit.hit && hit.t > 0)
		return (1);
	return (0);
}

static void	init_vars(t_world *w, double *ambient, double *diffuse)
{
	ambient[0] = (w->ambient.r / 255.0) * w->ambient_ratio;
	ambient[1] = (w->ambient.g / 255.0) * w->ambient_ratio;
	ambient[2] = (w->ambient.b / 255.0) * w->ambient_ratio;
	diffuse[0] = 0;
	diffuse[1] = 0;
	diffuse[2] = 0;
}

static void	set_light(double *light, double *ambient, double *diffuse)
{
	light[0] = ambient[0] + diffuse[0];
	light[1] = ambient[1] + diffuse[1];
	light[2] = ambient[2] + diffuse[2];
	if (light[0] > 1.0)
		light[0] = 1.0;
	if (light[1] > 1.0)
		light[1] = 1.0;
	if (light[2] > 1.0)
		light[2] = 1.0;
}

void	light(t_world *w, t_hit *hit, mlx_color *color)
{
	t_vec	light_dir;
	double	coef_diffuse;
	double	diffuse[3];
	double	ambient[3];
	double	light[3];

	init_vars(w, ambient, diffuse);
	light_dir = vec_sub(w->lights.position, hit->point);
	vec_normalize(&light_dir);
	coef_diffuse = vec_dot(hit->normal, light_dir);
	if (!(coef_diffuse <= 0 || shadow_ray(w, hit->point, light_dir)))
	{
		diffuse[0] = (w->lights.color.r / 255.0) * coef_diffuse * w->lights.intensity;
		diffuse[1] = (w->lights.color.g / 255.0) * coef_diffuse * w->lights.intensity;
		diffuse[2] = (w->lights.color.b / 255.0) * coef_diffuse * w->lights.intensity;
	}
	set_light(light, ambient, diffuse);
	color->r = hit->object->color.r * light[0];
	color->g = hit->object->color.g * light[1];
	color->b = hit->object->color.b * light[2];
	color->a = 255;
}
