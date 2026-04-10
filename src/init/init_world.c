/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 08:42:27 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/10 09:07:35 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_world	init_world(t_data *data)
{
	t_world	w;

	(void)data;
	ft_memset(&w, 0, sizeof(t_world));
	w.sphere.center = (t_vec){2, 0, 0};
	w.sphere.radius = 1;
	w.sphere.color = (t_color){255, 0, 0};
	w.cam.pos = (t_vec){0, 0, -5};
	w.cam.dir = (t_vec){0, 0, 1};
	w.cam.fov = FOV;
	w.light.pos = (t_vec){2, 2, -2};
	w.light.color = (t_color){255, 255, 255};
	return (w);
}
