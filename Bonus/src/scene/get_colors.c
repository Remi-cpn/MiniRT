/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:19:12 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/02 11:53:06 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/world.h"

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
	else if (obj->type == OBJ_RING)
		return (hit_ring(obj->shape.ring, ray));
	return (-1.0);
}

t_hit	find_closest_hit(t_world *w, t_ray ray, int flag_dist)
{
	t_hit		closest;
	t_sphere	sun_sphere;
	double		t;
	int			i;

	closest.hit = 0;
	closest.t = RENDER_DIST;
	closest.sun_idx = -1;
	i = -1;
	while (++i < w->nb_obj)
	{
		t = get_intersection_t(&w->objects[i], ray);
		if (t > 0.001 && t < closest.t)
		{
			closest.t = t;
			closest.object = &w->objects[i];
			closest.hit = 1;
			closest.sun_idx = -1;
		}
	}
	if (flag_dist == 0)
	{
		i = -1;
		while (++i < w->nb_sun)
		{
			sun_sphere.center = w->suns[i].param.cur_pos;
			sun_sphere.radius = w->suns[i].radius;
			t = hit_sphere(sun_sphere, ray);
			if (t > 0.001 && t < closest.t)
			{
				closest.t = t;
				closest.hit = 2;
				closest.sun_idx = i;
				closest.object = NULL;
			}
		}
	}
	if (closest.hit == 1)
		fill_hit_details(&closest, ray);
	else if (closest.hit == 2)
	{
		closest.point = vec_add(ray.origin,
				vec_mult_scalar(ray.dir, closest.t));
		closest.normal = vec_sub(closest.point,
				w->suns[closest.sun_idx].param.cur_pos);
		vec_normalize(&closest.normal);
	}
	return (closest);
}

static void	init_sun_obj(t_object *sun_obj, t_sun *sun)
{
	sun_obj->type = OBJ_SPHERE;
	sun_obj->color = sun->color;
	sun_obj->texture = sun->texture;
	sun_obj->shape.sphere.center = sun->param.cur_pos;
	sun_obj->shape.sphere.radius = sun->radius;
}

void	pixel_color(t_world *w, t_ray ray, mlx_color *color)
{
	t_hit		hit;
	t_object	sun_obj;

	hit = find_closest_hit(w, ray, 0);
	color->rgba = 0x00000000;
	if (!hit.hit)
		return ;
	if (hit.hit == 2)
	{
		ft_memset(&sun_obj, 0, sizeof(t_object));
		init_sun_obj(&sun_obj, &w->suns[hit.sun_idx]);
		hit.object = &sun_obj;
		if (sun_obj.texture.type != TEX_NONE)
			*color = get_texture(&hit);
		else
			*color = sun_obj.color;
		return ;
	}
	if (hit.object->texture.type != TEX_NONE)
		hit.pixel_color = get_texture(&hit);
	else
		hit.pixel_color = hit.object->color;
	light(w, &hit, color);
}
