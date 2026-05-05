/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 11:35:32 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/05 11:41:34 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"
#include <stdlib.h>

static void	free_suns(t_world *w)
{
	int i;
	
	i = 0;
	while (i < w->nb_sun)
	{
		if (w->suns[i].texture.img.pixels)
		{
			free(w->suns[i].texture.img.pixels);
			w->suns[i].texture.img.pixels = NULL;
		}
		i++;
	}	
}

void	free_obj_and_light(t_world *w)
{
	int	i;

	i = 0;
	while (i < w->nb_obj)
	{
		if (w->objects[i].texture.img.pixels)
		{
			free(w->objects[i].texture.img.pixels);
			w->objects[i].texture.img.pixels = NULL;
		}
		if (w->objects[i].texture.bump_map.pixels)
		{
			free(w->objects[i].texture.bump_map.pixels);
			w->objects[i].texture.bump_map.pixels = NULL;
		}
		i++;
	}
	if (w->nb_sun != 0)
		free_suns(w);
	if (w->lights)
		free(w->lights);
	if (w->suns)
		free(w->suns);
	free(w->objects);
}

void	free_parsing(t_parsing *p)
{
	if (p->line)
	{
		while (p->line)
		{
			p->line = ft_freenull(p->line);
			p->line = ft_get_next_line(p->fd);
		}
		close(p->fd);
	}
	if (p->line_split)
		ft_free_array(p->line_split);
}