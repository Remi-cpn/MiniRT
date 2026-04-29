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

static void	fill_hit_details_cylinder(t_hit *hit)
{
	t_vec	oc;
	t_vec	new_center;
	double	proj;

	oc = vec_sub(hit->point, hit->object->shape.cylinder.center);
	new_center = vec_proj(oc, hit->object->shape.cylinder.axis);
	proj = vec_dot(oc, hit->object->shape.cylinder.axis);
	if (fabs(proj - hit->object->shape.cylinder.height / 2.0) < 0.001)
		hit->normal = hit->object->shape.cylinder.axis;
	else if (fabs(proj + hit->object->shape.cylinder.height / 2.0) < 0.001)
		hit->normal = vec_mult_scalar(hit->object->shape.cylinder.axis, -1.0);
	else
		hit->normal = vec_sub(oc, new_center);
}


static void	fill_hit_details_cone(t_hit *hit)
{
	t_vec	co;
	t_vec	v;
	double	k;
	double	dot;

	co = vec_sub(hit->point, hit->object->shape.cone.apex);
	v = hit->object->shape.cone.axis; // doit être normalisé
	k = pow(tan(hit->object->shape.cone.angle), 2);

	dot = vec_dot(co, v);
	hit->normal = vec_sub(co, vec_mult_scalar(v, (1 + k) * dot));
	vec_normalize(&hit->normal);
}

static void	fill_hit_details(t_hit *hit, t_ray ray)
{
	hit->point = vec_add(ray.origin, vec_mult_scalar(ray.dir, hit->t));
	if (hit->object->type == OBJ_SPHERE)
		hit->normal = vec_sub(hit->point, hit->object->shape.sphere.center);
	else if (hit->object->type == OBJ_PLANE)
		hit->normal = hit->object->shape.plane.normal;
	else if (hit->object->type == OBJ_CONE)
		fill_hit_details_cone(hit);
	else if (hit->object->type == OBJ_CYLINDER)
		fill_hit_details_cylinder(hit);
	if (hit->object->type == OBJ_SPHERE || hit->object->type == OBJ_PLANE
		|| hit->object->type == OBJ_CYLINDER)
		vec_normalize(&hit->normal);
	if (vec_dot(hit->normal, ray.dir) > 0)
		hit->normal = vec_mult_scalar(hit->normal, -1.0);
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
