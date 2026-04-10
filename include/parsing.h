/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:11:23 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/10 16:53:26 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/* ——— Lib Extern ——————————————————————————————————————————————————————————— */
#include <fcntl.h>

/* ——— Define ——————————————————————————————————————————————————————————————— */
# define TYPE 1
# define COLOR 2
# define POS 3

/* ——— Struct prototypes ———————————————————————————————————————————————————— */
typedef struct s_obj
{
	int	kind;
}	t_obj;

typedef struct s_parsing
{
	char	**lines;
	int		count_line;
}	t_parsing;

/* ——— Function prototypes —————————————————————————————————————————————————— */
t_parsing	parsing(char *file_name);
void		pars_line(t_parsing *p, char *line);
int			count_line(t_parsing *p, char *file_name);

#endif