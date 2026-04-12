/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:11:23 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/12 13:45:59 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minirt.h"

/* ——— Lib Extern ——————————————————————————————————————————————————————————— */
# include <fcntl.h>
# include <stdbool.h>

/* ——— Define ——————————————————————————————————————————————————————————————— */
# define TYPE 1
# define COLOR 2
# define POS 3
# define P_INT_MAX "2147483647"
# define P_INT_MIN "2147483648"
# define P_LONG_MAX "9223372036854775807"
# define P_LONG_MIN "9223372036854775808"

/* ——— Variable prototypes —————————————————————————————————————————————————— */
typedef struct s_data		t_data;
typedef struct s_world		t_world;
typedef struct s_vec		t_vec;
typedef struct s_object		t_object;

/* ——— Struct prototypes ———————————————————————————————————————————————————— */
typedef struct s_parsing
{
	int			fd;
	char		*line;
	char		**line_split;
	int			count_line;
	bool		cam;
	bool		al;
	bool		light;
}	t_parsing;

typedef enum e_type
{
	INT,
	LONG,
	FLOAT,
	DOUBLE
}	t_type;

/* ——— Function prototypes —————————————————————————————————————————————————— */
t_world		parsing(t_data *d, char *file_name);
void		pars_line(t_parsing *p, t_world *w, char *line);
int			count_line(t_parsing *p, char *file_name);
mlx_color	get_color(t_parsing *p, char *s);
t_vec		get_vec(t_parsing *p, char *s);

/* Formatters functions */
void		add_al(t_parsing *p, t_world *w, char **line_split);
void		add_cam(t_parsing *p, t_world *w, char **line_split);
void		add_light(t_parsing *p, t_world *w, char **line_split);
void		add_sp(t_parsing *p, t_object *o, char **line_split);
void		add_pl(t_parsing *p, t_object *o, char **line_split);
void		add_cy(t_parsing *p, t_object *o, char **line_split);

/* Valid functions */
int			int_valid(char *s);
int			long_valid(char *s);
int			float_valid(char *s);
int			double_valid(char *s);

#endif