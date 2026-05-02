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
