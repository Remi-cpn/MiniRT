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
	return (-1.0);
}

t_hit	find_closest_hit(t_world *w, t_ray ray, int flag_dist)
{
	t_hit	closest;
	double	t;
	int		i;

	closest.hit = 0;
	closest.t = RENDER_DIST;
	i = -1;
	while (++i < w->nb_obj)
	{
		t = get_intersection_t(&w->objects[i], ray);
		if (t > 0.001 && t < closest.t)
		{
			closest.t = t;
			closest.object = &w->objects[i];
			closest.hit = 1;
		}
	}
	if (closest.hit && flag_dist == 0)
		fill_hit_details(&closest, ray);
	return (closest);
}

void	pixel_color(t_world *w, t_ray ray, mlx_color *color)
{
	t_hit	hit;

	hit = find_closest_hit(w, ray, 0);
	if (!hit.hit)
	{
		color->rgba = 0x81CEFAFF;
		return ;
	}
	if (hit.object->texture.type != TEX_NONE)
		hit.pixel_color = get_texture(&hit);
	else
		hit.pixel_color = hit.object->color;
	light(w, &hit, color);
}
