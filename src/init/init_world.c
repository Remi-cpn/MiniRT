/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 08:42:27 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/08 13:27:39 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_world	init_world(t_data *data)
{
	t_world	w;

	ft_memset(&w, 0, sizeof(t_world));
	w.sphere.center = (t_vec){ 0, 0, 0};
	w.sphere.radius = 1;
	w.sphere.color = (t_color){ 255, 0, 0};
	return (w);
}