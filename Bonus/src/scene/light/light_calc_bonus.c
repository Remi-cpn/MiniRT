/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_calc_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 09:46:02 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/04 16:03:57 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minirt_bonus.h"

static void	apply_light_gamma(t_world *w, t_hit *hit, mlx_color *color,
	t_light_managment *l)
{
	if (w->solar_file == true && hit->object->physics_enabled == false)
	{
		color->r = hit->pixel_color.r * l->light[R];
		color->g = hit->pixel_color.g * l->light[G];
		color->b = hit->pixel_color.b * l->light[B];
	}
	else
	{
		color->r = 255 * pow((hit->pixel_color.r / 255.0) * l->light[R], GAMMA);
		color->g = 255 * pow((hit->pixel_color.g / 255.0) * l->light[G], GAMMA);
		color->b = 255 * pow((hit->pixel_color.b / 255.0) * l->light[B], GAMMA);
	}
	color->a = 255;
}

static void	init_vars(t_world *w, double *ambient,
		double *diffuse, double *specular)
{
	ambient[R] = (w->ambient.r / 255.0) * w->ambient_ratio;
	ambient[G] = (w->ambient.g / 255.0) * w->ambient_ratio;
	ambient[B] = (w->ambient.b / 255.0) * w->ambient_ratio;
	diffuse[R] = 0;
	diffuse[G] = 0;
	diffuse[B] = 0;
	specular[R] = 0;
	specular[G] = 0;
	specular[B] = 0;
}

static void	set_light(double *light, double *ambient,
		double *diffuse, double *specular)
{
	light[R] = ambient[R] + diffuse[R] + specular[R];
	light[G] = ambient[G] + diffuse[G] + specular[G];
	light[B] = ambient[B] + diffuse[B] + specular[B];
	if (light[R] > 1.0)
		light[R] = 1.0;
	if (light[G] > 1.0)
		light[G] = 1.0;
	if (light[B] > 1.0)
		light[B] = 1.0;
}

void	light(t_world *w, t_hit *hit, mlx_color *color)
{
	t_light_managment	l;
	t_light				sun;
	int					i;

	init_vars(w, l.ambient, l.diffuse, l.specular);
	i = -1;
	while (++i < w->nb_light)
		calc_one_light(w, hit, &w->lights[i], &l);
	i = -1;
	while (++i < w->nb_sun)
	{
		sun.position = w->suns[i].param.cur_pos;
		sun.color = w->suns[i].color;
		sun.intensity = w->suns[i].intensity;
		calc_one_light(w, hit, &sun, &l);
	}
	set_light(l.light, l.ambient, l.diffuse, l.specular);
	apply_light_gamma(w, hit, color, &l);
}
