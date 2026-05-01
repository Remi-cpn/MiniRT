/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 15:11:23 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/01 13:27:35 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/* ——— Lib Extern ——————————————————————————————————————————————————————————— */
# include <fcntl.h>
# include <stdbool.h>
# include "../../MacroLibX/includes/mlx.h"
# include "../../librt/librt.h"


/* ——— Define ——————————————————————————————————————————————————————————————— */
# define TYPE 1
# define COLOR 2
# define POS 3

/* ——— Forward declare —————————————————————————————————————————————————— */
typedef struct s_data	t_data;
typedef struct s_world	t_world;
typedef struct s_object	t_object;

/* ——— Struct prototypes ———————————————————————————————————————————————————— */
typedef struct s_parsing
{
	int			fd;
	char		*line;
	char		**line_split;
	int			count_line;
	bool		cam;
	bool		al;
	mlx_context	mlx;
	t_world		*world;
	t_data		*data;
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
void		pars_line_dispatch(t_parsing *p, t_world *w, char *l, bool solar);
int			count_line(t_parsing *p, char *file_name);
int			count_light(t_parsing *p, char *file_name);
mlx_color	get_color(t_parsing *p, char *s);
t_vec		get_vec(t_parsing *p, char *s);
double		get_mass(char *s);

/* Formatters functions */
void		add_al(t_parsing *p, t_world *w, char **line_split);
void		add_cam(t_parsing *p, t_world *w, char **line_split);
void		add_light(t_parsing *p, t_world *w, char **line_split);
void		add_sp(t_parsing *p, t_object *o, char **line_split);
void		add_sp_solar(t_parsing *p, t_object *o, char **line_split);
void		add_pl(t_parsing *p, t_object *o, char **line_split);
void		add_cy(t_parsing *p, t_object *o, char **line_split);
void		add_co(t_parsing *p, t_object *o, char **line_split);

/* Textures functions */
void		pars_chessboard(t_parsing *p, t_object *o, char *scale,
				char *color);
void		pars_texture_map(t_parsing *p, t_texture *t, char *texture_file,
				char *bump_file);

#endif
