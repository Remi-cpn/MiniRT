
#include "../../include/minirt.h"

static double	get_intersection_t(t_object *obj, t_ray ray)
{
	if (obj->type == OBJ_SPHERE)
		return (hit_sphere(obj->shape.sphere, ray));
	else if (obj->type == OBJ_PLANE)
		return (hit_plane(obj->shape.plane, ray));
	// else if (obj->type == OBJ_CYLINDER)
	// 	return (hit_cylinder_t(&obj->shape.cylinder, ray));
	return (-1.0);
}

static void	fill_hit_details(t_hit *hit, t_ray ray)
{
	hit->point = vec_add(ray.origin, vec_mult_scalar(ray.dir, hit->t));
	if (hit->object->type == OBJ_SPHERE)
	{
		hit->normal = vec_sub(hit->point, hit->object->shape.sphere.center);
		vec_normalize(&hit->normal);
	}
	else if (hit->object->type == OBJ_PLANE)
		hit->normal = hit->object->shape.plane.normal;
	// else if (hit->object->type == OBJ_CYLINDER)
	// 	hit->normal = ???
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
	light(w, &hit, color);
}
