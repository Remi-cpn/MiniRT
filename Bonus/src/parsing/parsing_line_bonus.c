/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:49:29 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/05 11:44:13 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt_bonus.h"
#include "../../include/parsing_bonus.h"
#include <stdio.h>

static void	pars_line_solar(t_parsing *p, t_world *w, char *line)
{
	static int	i = 0;
	static int	j = 0;

	p->line_split = ft_split(line, ' ');
	if (!p->line_split || !p->line_split[0])
		exit_prog_pars(p, ERROR_MALLOC, ERROR_MALLOC_MSG);
	if (!ft_strncmp(p->line_split[0], "A", 2))
		add_al(p, w, p->line_split);
	else if (!ft_strncmp(p->line_split[0], "C", 2))
		add_cam(p, w, p->line_split);
	else if (!ft_strncmp(p->line_split[0], "so", 3))
		add_so(p, &w->suns[j++], p->line_split);
	else if (!ft_strncmp(p->line_split[0], "sp", 3))
		add_sp_solar(p, &w->objects[i++], p->line_split);
	else if (!ft_strncmp(p->line_split[0], "ri", 3))
	{
		add_ri(p, &w->objects[i], p->line_split, i);
		i++;
	}
	else
		exit_prog_pars(p, ERROR_FILE_ARGS, ERROR_FILE_ARGS_MSG);
	ft_free_array(p->line_split);
	i = (i != w->nb_obj) * i;
	j = (j != w->nb_sun) * j;
	p->line_split = NULL;
}

static void	pars_line_rt(t_parsing *p, t_world *w, char *line)
{
	static int	i = 0;

	p->line_split = ft_split(line, ' ');
	if (!p->line_split || !p->line_split[0])
		exit_prog_pars(p, ERROR_MALLOC, ERROR_MALLOC_MSG);
	if (!ft_strncmp(p->line_split[0], "A", 2))
		add_al(p, w, p->line_split);
	else if (!ft_strncmp(p->line_split[0], "C", 2))
		add_cam(p, w, p->line_split);
	else if (!ft_strncmp(p->line_split[0], "L", 2))
		add_light(p, w, p->line_split);
	else if (!ft_strncmp(p->line_split[0], "sp", 3))
		add_sp(p, &w->objects[i++], p->line_split);
	else if (!ft_strncmp(p->line_split[0], "pl", 3))
		add_pl(p, &w->objects[i++], p->line_split);
	else if (!ft_strncmp(p->line_split[0], "cy", 3))
		add_cy(p, &w->objects[i++], p->line_split);
	else if (!ft_strncmp(p->line_split[0], "co", 3))
		add_co(p, &w->objects[i++], p->line_split);
	else
		exit_prog_pars(p, ERROR_FILE_ARGS, ERROR_FILE_ARGS_MSG);
	ft_free_array(p->line_split);
	if (i == w->nb_obj)
		i = 0;
	p->line_split = NULL;
}

void	pars_line_dispatch(t_parsing *p, t_world *w, char *l, bool solar)
{
	if (solar == true)
		pars_line_solar(p, w, l);
	else
		pars_line_rt(p, w, l);
}
