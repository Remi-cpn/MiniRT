/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 17:24:21 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/28 15:18:05 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

/* ——— Define exit messages (negative values is personal error codes) ——————— */
/* Exit codes */
# define EXIT_SUCCESS 0
# define EXIT_ERROR 1
# define ERROR_MLX_INIT -1
# define ERROR_MALLOC -2
# define ERROR_MLX_WINDOW -3
# define ERROR_FILE_NAME -4
# define ERROR_FILE_ARGS -5
# define ERROR_FILE_CAM -6
# define ERROR_FILE_LIGHT -7
# define ERROR_FILE_AL -8
# define ERROR_FILE_OBJ -9
# define ERROR_FILE_TEX -10
# define ERROR_FILE_BUMP -10
# define ERROR_THREAD -11
# define ERROR_MUTEX -12

/* Exit messages */
# define ERROR_MLX_INIT_MSG "Failed to initialize MLX context"
# define ERROR_MALLOC_MSG "Failed to allocate memory"
# define ERROR_MLX_WINDOW_MSG "Failed to create MLX window"
# define ERROR_FILE_NAME_MSG "Incorrect file name"
# define ERROR_FILE_ARGS_MSG "Incorrect file arguments"
# define ERROR_FILE_CAM_MSG "Only one camera needs to be defined in the file"
# define ERROR_FILE_CAM_ARGS_MSG "Camera must be defined with valid arguments"
# define ERROR_FILE_LIGHT_MSG "Only one light needs to be defined in the file"
# define ERROR_FILE_LIGHT_ARGS_MSG "Light must be defined with valid arguments"
# define ERROR_FILE_AL_MSG "Only one ambient light needs to be defined in the \
	file"
# define ERROR_FILE_AL_ARGS_MSG "Ambient light must be defined with valid \
	arguments"
# define ERROR_FILE_SP_ARGS_MSG "Sphere must be defined with valid arguments"
# define ERROR_FILE_SO_ARGS_MSG "Solars must be defined with valid arguments"
# define ERROR_FILE_PL_ARGS_MSG "Plane must be defined with valid arguments"
# define ERROR_FILE_CY_ARGS_MSG "Cylinder must be defined with valid arguments"
# define ERROR_FILE_CO_ARGS_MSG "Cone must be defined with valid arguments"
# define ERROR_FILE_TEX_MSG "Incorrect file texture name"
# define ERROR_FILE_BUMP_MSG "Incorrect file bump_map name"
# define ERROR_THREAD_MSG "Thread creation failed"
# define ERROR_MUTEX_MSG "Mutex initialization failed"

/* ——— Variable prototypes —————————————————————————————————————————————————— */
typedef struct s_data		t_data;
typedef struct s_parsing	t_parsing;

/* ——— Function prototypes —————————————————————————————————————————————————— */
void	exit_prog(t_data *data, int exit_code, char *error_message);
void	exit_prog_pars(t_parsing *p, int exit_code, char *error_message);
void	free_parsing(t_parsing *p);

#endif
