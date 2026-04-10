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
	double	t_sphere;
	double	t_plane;

	shadow_ray.dir = light_dir;
	shadow_ray.origin = vec_add(p, vec_mult_scalar(shadow_ray.dir, 0.001));
	t_sphere = hit_sphere(w, shadow_ray);
	t_plane = hit_plane(w, shadow_ray);
	if (t_sphere > 0 || t_plane > 0)
		return (1);
	return (0);
}

static void	set_color(t_world *w, mlx_color *color, t_obj *hit,
	double light_intensity)
{
	if (*hit == OBJ_NONE)
	{
		color->rgba = 0x000000FF;
		return ;
	}
	else if (*hit == OBJ_PLANE)
	{
		color->r = w->plane.color.r * light_intensity;
		color->g = w->plane.color.g * light_intensity;
		color->b = w->plane.color.b * light_intensity;
		color->a = 255;
		return ;
	}
	else if (*hit == OBJ_SPHERE)
	{
		color->r = w->sphere.color.r * light_intensity;
		color->g = w->sphere.color.g * light_intensity;
		color->b = w->sphere.color.b * light_intensity;
		color->a = 255;
		return ;
	}
}

static double	light(t_world *w, t_vec p, t_vec normal)
{
	t_vec	light_dir;
	double	len;
	double	light_intensity;

	light_dir = vec_sub(w->light.pos, p);
	len = vec_norm(light_dir);
	light_dir = vec_mult_scalar(light_dir, 1 / len);
	light_intensity = vec_dot(normal, light_dir);
	// pas de couleur negative ca fou la merde
	if (light_intensity < 0 || shadow_ray(w, p, light_dir))
		light_intensity = 0;
	light_intensity += w->ambient_light;
	if (light_intensity > 1)
		light_intensity = 1;
	return (light_intensity);
}

static double	find_t(t_world *w, t_ray ray, t_obj *hit)
{
	double	t_sphere;
	double	t_plane;

	t_sphere = hit_sphere(w, ray);
	t_plane = hit_plane(w, ray);
	if (t_sphere < 0 && t_plane < 0)
		*hit = OBJ_NONE;
	else if (t_sphere < 0)
		*hit = OBJ_PLANE;
	else if (t_plane < 0)
		*hit = OBJ_SPHERE;
	else if (t_sphere < t_plane)
		*hit = OBJ_SPHERE;
	else
		*hit = OBJ_PLANE;
	if (*hit == OBJ_SPHERE)
		return (t_sphere);
	else if (*hit == OBJ_PLANE)
		return (t_plane);
	return (-1);
}

void	pixel_color(t_world *w, t_ray ray, mlx_color *color)
{
	double	t;
	double	len;
	t_vec	p;
	t_vec	normal;
	t_obj	hit;

	ft_memset(&hit, 0, sizeof(t_obj));
	t = find_t(w, ray, &hit);
	if (t < 0)
		color->rgba = 0x000000FF;
	else if (hit == OBJ_PLANE)
	{
		p = vec_add(ray.origin, vec_mult_scalar(ray.dir, t));
		set_color(w, color, &hit, light(w, p, w->plane.normal));
	}
	else if (hit == OBJ_SPHERE)
	{
		p = vec_add(ray.origin, vec_mult_scalar(ray.dir, t));
		normal = vec_sub(p, w->sphere.center);
		len = vec_norm(normal);
		normal = vec_mult_scalar(normal, 1 / len);
		set_color(w, color, &hit, light(w, p, normal));
	}
}
