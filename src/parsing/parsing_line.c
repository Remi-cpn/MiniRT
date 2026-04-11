/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:49:29 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/11 15:56:55 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/parsing.h"

static void	check_format(t_parsing *p, t_world *w, char *line)
{
	static int	i = 0;

	p->line_split = ft_split(line, ' ');
	if (!p->line_split || !p->line_split[0])
		exit_prog_pars(p, ERROR_MALLOC, ERROR_MALLOC_MSG);
	if (!ft_strncmp(p->line_split[0], "A ", 1))
		add_al(p, w, p->line_split);
	else if (!ft_strncmp(p->line_split[0], "C ", 1))
		add_cam(p, w, p->line_split);
	else if (!ft_strncmp(p->line_split[0], "L ", 1))
		add_light(p, w, p->line_split);
	else if (!ft_strncmp(p->line_split[0], "sp ", 2))
		add_sp(p, &w->objects[i], p->line_split);
	else if (!ft_strncmp(p->line_split[0], "pl ", 2))
		add_pl(p, &w->objects[i], p->line_split);
	else if (!ft_strncmp(p->line_split[0], "cy ", 2))
		add_cy(p, &w->objects[i], p->line_split);
	else
		exit_prog_pars(p, ERROR_FILE_ARGS, ERROR_FILE_ARGS_MSG);
	ft_freedb_ptr((void **)&p->line_split);
	p->line_split = NULL;
	i++;
}

void	pars_line(t_parsing *p, t_world *w, char *line)
{
	w->objects = ft_calloc(w->nb_obj, sizeof(t_object));
	if (!w->objects)
		exit_prog_pars(p, ERROR_MALLOC, ERROR_MALLOC_MSG);
	check_format(p, w, line);
}
