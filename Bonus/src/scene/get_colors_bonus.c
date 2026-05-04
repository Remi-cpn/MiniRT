/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:19:12 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/02 17:26:19 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"
#include "../../include/world_bonus.h"

static void	init_sun_obj(t_object *sun_obj, t_sun *sun)
{
	sun_obj->type = OBJ_SPHERE;
	sun_obj->color = sun->color;
	sun_obj->texture = sun->texture;
	sun_obj->shape.sphere.center = sun->param.cur_pos;
	sun_obj->shape.sphere.radius = sun->radius;
}

static void	apply_transparency(t_world *w, t_ray ray, t_hit *hit,
		mlx_color *color)
{
	mlx_color	bg;
	t_ray		new_ray;
	double		alpha;

	alpha = hit->pixel_color.a / 255.0;
	if (alpha >= 1.0)
		return ;
	bg.rgba = 0;
	new_ray.dir = ray.dir;
	new_ray.origin = vec_add(hit->point, vec_mult_scalar(ray.dir, 0.001));
	pixel_color(w, new_ray, &bg);
	color->r = (uint8_t)(alpha * color->r + (1.0 - alpha) * bg.r);
	color->g = (uint8_t)(alpha * color->g + (1.0 - alpha) * bg.g);
	color->b = (uint8_t)(alpha * color->b + (1.0 - alpha) * bg.b);
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
	apply_transparency(w, ray, &hit, color);
}
