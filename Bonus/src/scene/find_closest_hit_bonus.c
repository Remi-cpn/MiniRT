/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:19:12 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/22 16:53:58 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"
#include "../../include/world_bonus.h"

static double	get_intersection_t(t_object *obj, t_ray ray)
{
	if (obj->type == OBJ_SPHERE)
		return (hit_sphere(obj->shape.sphere, ray));
	else if (obj->type == OBJ_PLANE)
		return (hit_plane(obj->shape.plane, ray));
	else if (obj->type == OBJ_CYLINDER)
		return (hit_cylinder(obj->shape.cylinder, ray));
	else if (obj->type == OBJ_CONE)
		return (hit_cone(obj->shape.cone, ray));
	return (-1.0);
}

static void	check_objects(t_world *w, t_ray ray, t_hit *closest)
{
	double	t;
	int		i;

	i = -1;
	while (++i < w->nb_obj)
	{
		t = get_intersection_t(&w->objects[i], ray);
		if (t > 0.001 && t < closest->t)
		{
			closest->t = t;
			closest->object = &w->objects[i];
			closest->hit = 1;
			closest->sun_idx = -1;
		}
	}
}

static void	check_suns(t_world *w, t_ray ray, t_hit *closest)
{
	t_sphere	sun_sphere;
	double		t;
	int			i;

	i = -1;
	while (++i < w->nb_sun)
	{
		sun_sphere.center = w->suns[i].param.cur_pos;
		sun_sphere.radius = w->suns[i].radius;
		t = hit_sphere(sun_sphere, ray);
		if (t > 0.001 && t < closest->t)
		{
			closest->t = t;
			closest->hit = 2;
			closest->sun_idx = i;
			closest->object = NULL;
		}
	}
}

static void	fill_closest(t_world *w, t_ray ray, t_hit *closest)
{
	if (closest->hit == 1)
		fill_hit_details(closest, ray);
	else if (closest->hit == 2)
	{
		closest->point = vec_add(ray.origin,
				vec_mult_scalar(ray.dir, closest->t));
		closest->normal = vec_sub(closest->point,
				w->suns[closest->sun_idx].param.cur_pos);
		vec_normalize(&closest->normal);
	}
}

t_hit	find_closest_hit(t_world *w, t_ray ray, int flag_dist)
{
	t_hit	closest;

	closest.hit = 0;
	closest.t = RENDER_DIST;
	closest.sun_idx = -1;
	check_objects(w, ray, &closest);
	if (flag_dist == 0)
		check_suns(w, ray, &closest);
	fill_closest(w, ray, &closest);
	return (closest);
}
