/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 13:33:52 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/07 08:30:27 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

/* ——— Lib Intern ——————————————————————————————————————————————————————————— */
# include "../libft/libft.h"
# include "exit.h"

/* ——— Lib Graphique ———————————————————————————————————————————————————————— */
# include "../MacroLibX/includes/mlx.h"

/* ——— Lib Extern ——————————————————————————————————————————————————————————— */
# include "stdlib.h"
# include "unistd.h"

/* ——— Structs data ————————————————————————————————————————————————————————— */
typedef struct s_data
{
	mlx_context				mlx_init;
	mlx_window_create_info	win_info;
	mlx_window				win;
}	t_data;

/* ——— Function prototypes —————————————————————————————————————————————————— */
t_data					init_program(void);

#endif // !DEBUG
