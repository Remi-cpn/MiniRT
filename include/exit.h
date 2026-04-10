/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 17:24:21 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/10 16:44:30 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

/* ——— Define exit messages (negative values is personal error codes) ——————— */
/* Exit codes */
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define ERROR_MLX_INIT -1
# define ERROR_MALLOC -2
# define ERROR_MLX_WINDOW -3
# define ERROR_FILE_NAME -4
# define ERROR_FILE_ARGS -5

/* Exit messages */
# define ERROR_MLX_INIT_MSG "Failed to initialize MLX context"
# define ERROR_MALLOC_MSG "Failed to allocate memory"
# define ERROR_MLX_WINDOW_MSG "Failed to create MLX window"
# define ERROE_FILE_NAME_MSG "Incorrect file name"
# define ERROE_FILE_ARGS_MSG "Incorrect file args"

/* ——— Variable prototypes —————————————————————————————————————————————————— */
typedef struct s_data	t_data;

/* ——— Function prototypes —————————————————————————————————————————————————— */
void	print_error(char *message);
void	exit_prog(t_data *data, int exit_code, char *error_message);
void	exit_prog_pars(t_parsing *p, int exit_code, char *error_message);

#endif