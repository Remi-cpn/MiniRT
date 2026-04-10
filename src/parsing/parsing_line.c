/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:49:29 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/10 16:49:01 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"
#include "../../include/parsing.h"

static void	check_format(t_parsing *p, char *line)
{
	if (ft_strncmp(line, "A ", 2))
		//fonction
		;
	else if (ft_strncmp(line, "C ", 2))
		//fonction;
		;
	else if (ft_strncmp(line, "L ", 2))
		//fonction;
		;
	else if (ft_strncmp(line, "sp ", 3))
		//fonction;
		;
	else if (ft_strncmp(line, "pl ", 3))
		//fonction;
		;
	else if (ft_strncmp(line, "cy ", 3))
		//fonction;
		;
	else
		exit_prog_pars(p, ERROR_FILE_ARGS, ERROE_FILE_ARGS_MSG);
}

void	pars_line(t_parsing *p, char *line)
{
	check_format(p, line);
}