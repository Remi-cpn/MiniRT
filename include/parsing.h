/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:11:23 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/10 15:55:17 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/* ——— Lib Extern ——————————————————————————————————————————————————————————— */
#include <fcntl.h>

/* ——— Struct prototypes ———————————————————————————————————————————————————— */
typedef struct s_parsing
{
	char	**lines;
}	t_parsing;

/* ——— Function prototypes —————————————————————————————————————————————————— */
void	parsing(t_data *d, char *file_name);
int		count_line(t_data *d, char *file_name);

#endif