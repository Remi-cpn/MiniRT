/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 14:58:56 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/23 10:26:39 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"
#include <stdio.h>
#include "../../include/parsing_bonus.h"

static int	init_nb_obj(t_parsing *p, int nb_light)
{
	int	nb_obj;

	nb_obj = 0;
	if (p->count_line < 3)
		exit_prog_pars(p, ERROR_FILE_ARGS, ERROR_FILE_ARGS_MSG);
	else if (p->count_line == 2 + nb_light)
		nb_obj = 0;
	else
		nb_obj = p->count_line - 2 - nb_light;
	return (nb_obj);
}

static int	check_file_name(t_data *d, char *file_name)
{
	if (ft_strnstr(file_name, ".rt", ft_strlen(file_name)))
		return (1);
	if (ft_strnstr(file_name, ".solar", ft_strlen(file_name)))
	{
		d->solar_file = true;
		return (1);
	}
	return (0);
}

static void	pars_file(t_parsing *p, t_world *w, char *file_name, bool solar)
{
	p->fd = open(file_name, O_RDONLY);
	if (p->fd < 0)
		exit_prog_pars(p, ERROR_FILE_NAME, ERROR_FILE_NAME_MSG);
	p->line = ft_get_next_line(p->fd);
	while (p->line)
	{
		if (p->line[0] != '\n' && p->line[0] != '#')
		{
			if (p->line[ft_strlen(p->line) - 1] == '\n')
				p->line[ft_strlen(p->line) - 1] = '\0';
			pars_line_dispatch(p, w, p->line, solar);
		}
		p->line = ft_freenull(p->line);
		p->line = ft_get_next_line(p->fd);
	}
	close(p->fd);
	p->fd = -1;
}

t_world	parsing(t_data *d, char *file_name)
{
	t_parsing	p;
	t_world		w;

	ft_memset(&p, 0, sizeof(t_parsing));
	p.fd = -1;
	p.mlx = d->mlx;
	ft_memset(&w, 0, sizeof(t_world));
	p.world = &w;
	p.data = d;
	if (!check_file_name(d, file_name))
		exit_prog_pars(&p, ERROR_FILE_NAME, ERROR_FILE_NAME_MSG);
	p.count_line = count_line(&p, file_name, &w);
	w.nb_obj = init_nb_obj(&p, w.nb_light);
	w.lights = ft_calloc(w.nb_light, sizeof(t_light));
	w.suns = ft_calloc(w.nb_sun, sizeof(t_sun));
	if (w.nb_obj > 0)
		w.objects = ft_calloc(w.nb_obj, sizeof(t_object));
	if (!w.lights || !w.suns || (w.nb_obj > 0 && !w.objects))
		exit_prog_pars(&p, ERROR_MALLOC, ERROR_MALLOC_MSG);
	pars_file(&p, &w, file_name, d->solar_file);
	if (p.cam == false || p.al == false)
		exit_prog_pars(&p, ERROR_FILE_ARGS, ERROR_FILE_ARGS_MSG);
	init_world(d, &w);
	free_parsing(&p);
	return (w);
}
