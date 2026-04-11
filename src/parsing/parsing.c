/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 14:58:56 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/11 14:38:33 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/parsing.h"

static int	check_file_name(char *file_name)
{
	if (!ft_strnstr(file_name, ".rt", ft_strlen(file_name)))
		return (0);
	return (1);
}

static void	pars_file(t_parsing *p, t_world *w, char *file_name)
{
	p->fd = open(file_name, O_RDONLY);
	if (p->fd < 0)
		exit_prog_pars(p, ERROR_FILE_NAME, ERROR_FILE_NAME_MSG);
	p->line = ft_get_next_line(p->fd);
	while (p->line)
	{
		if (p->line[0] != '\n')
			pars_line(p, w, p->line);
		ft_freenull((void **)&p->line);
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
	ft_memset(&w, 0, sizeof(t_world));
	if (!check_file_name(file_name))
		exit_prog_pars(p, ERROR_FILE_NAME, ERROR_FILE_NAME_MSG);
	p.count_line = count_line(&p, file_name);
	pars_file(&p, &w, file_name);
	free_parsing(&p);
	return (w);
}
