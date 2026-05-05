# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/13 11:16:05 by rcompain          #+#    #+#              #
#    Updated: 2026/05/05 11:42:15 by rcompain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minirt
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -I MacroLibX/includes -O3
RM			= rm -f
MLX_DIR 	= MacroLibX
MLX 		= $(MLX_DIR)/libmlx.so
LIBRT_DIR	= librt
LIBFT_DIR	= libft
LIBRT_A		= $(LIBRT_DIR)/librt.a
LIBFT_A		= $(LIBFT_DIR)/libft.a

# ——— Dossier cible ————————————————————————————————————————————————————————— #
CC_DIR		= Mandatory
ifeq ($(MAKECMDGOALS),bonus)
CC_DIR		= Bonus
endif

SRC_DIR		= $(CC_DIR)/src
OBJ_DIR		= obj/$(CC_DIR)
INC_DIR		= $(CC_DIR)/include

# --- Sous-dossiers sources --------------------------------------------------
SUB_DIRS := scene exit moves init parsing

# ——— Sources ——————————————————————————————————————————————————————————————— #
SRC_INIT	= init_program.c \
			  init_world.c

SRC_MOVE	= hook.c \
			  camera.c \

SRC_EXIT	= exit_program.c

SRC_SCENE	= draw.c \
			  get_colors.c \
			  hit_cylinder.c \
			  hit_plane.c \
			  hit_sphere.c \
			  hit_cap.c \
			  light_calc.c \
			  ray.c

SRC_PARSING = parsing.c \
			  parsing_line.c \
			  utils.c \
			  format_unique.c \
			  format_form_rt.c

SRC_THREADS	=

ifeq ($(MAKECMDGOALS),bonus)
SRC_INIT	= init_program_bonus.c \
			  init_speed_sim_bonus.c \
			  init_world_bonus.c

SRC_MOVE	= hook_bonus.c \
			  camera_bonus.c \
			  cam_fix_bonus.c \
			  cam_relativ_bonus.c \

SRC_EXIT	= exit_program_bonus.c \
			  free_bonus.c

SRC_SCENE	= draw_bonus.c \
			  get_colors_bonus.c \
			  hit_cylinder_bonus.c \
			  hit_plane_bonus.c \
			  hit_sphere_bonus.c \
			  hit_cap_bonus.c \
			  light_calc_bonus.c \
			  ray_bonus.c \
			  textures_uv_bonus.c \
			  textures_uv2_bonus.c \
			  textures_manager_bonus.c \
			  textures_bump_map_bonus.c \
			  light_merge_bonus.c \
			  fill_hit_bonus.c \
			  calc_acc_bonus.c \
			  hit_ring_bonus.c \
			  find_closest_hit_bonus.c \
			  hit_cone_bonus.c

SRC_PARSING	= parsing_bonus.c \
			  parsing_line_bonus.c \
			  utils_bonus.c \
			  format_unique_bonus.c \
			  format_form_rt_bonus.c \
			  format_form_solar_bonus.c \
			  textures_bonus.c

SRC_MOVE	+= physics_bonus.c \

SRC_THREADS	= init_threads_bonus.c \
			  routine_bonus.c

SUB_DIRS	+= threads \
			   scene/hit \
			   scene/light \
			   scene/textures \
			   parsing/format

endif

VPATH := $(SRC_DIR) \
         $(addprefix $(SRC_DIR)/, $(SUB_DIRS))

ifeq ($(MAKECMDGOALS),bonus)
SRCS		= main_bonus.c $(SRC_MOVE) $(SRC_INIT) $(SRC_EXIT) $(SRC_SCENE) $(SRC_LRT) $(SRC_PARSING) $(SRC_THREADS)
else
SRCS		= main.c $(SRC_MOVE) $(SRC_INIT) $(SRC_EXIT) $(SRC_SCENE) $(SRC_LRT) $(SRC_PARSING) $(SRC_THREADS)
endif

OBJ			= ${SRCS:%.c=$(OBJ_DIR)/%.o}

# ——— Colors ———————————————————————————————————————————————————————————————— #
R           = \033[0m
BOLD        = \033[22m\033[1m
DIM         = \033[2m
GREEN       = \033[32m
CYAN        = \033[36m
ORANGE      = \033[38;5;183m
RED         = \033[38;5;210m

# ——— Banner ———————————————————————————————————————————————————————————————— #
define BANNER
$(BOLD)$(ORANGE)\n  ███$(DIM)╗   $(BOLD)███$(DIM)╗$(BOLD)██$(DIM)╗$(BOLD)███$(DIM)╗   $(BOLD)██$(DIM)╗$(BOLD)██$(DIM)╗$(RED)$(BOLD)██████$(DIM)╗ $(BOLD)████████$(DIM)╗$(R)
$(BOLD)$(ORANGE)  ████$(DIM)╗ $(BOLD)████$(DIM)║$(BOLD)██$(DIM)║$(BOLD)████$(DIM)╗  $(BOLD)██$(DIM)║$(BOLD)██$(DIM)║$(RED)$(BOLD)██$(DIM)╔══$(BOLD)██$(DIM)╗$(BOLD)╚══██$(DIM)╔══╝$(R)
$(BOLD)$(ORANGE)  ██$(DIM)╔$(BOLD)████$(DIM)╔$(BOLD)██$(DIM)║$(BOLD)██$(DIM)║$(BOLD)██$(DIM)╔$(BOLD)██$(DIM)╗ $(BOLD)██$(DIM)║$(BOLD)██$(DIM)║$(RED)$(BOLD)██████$(DIM)╔╝   $(BOLD)██$(DIM)║$(R)
$(BOLD)$(ORANGE)  ██$(DIM)║╚$(BOLD)██$(DIM)╔╝$(BOLD)██$(DIM)║$(BOLD)██$(DIM)║$(BOLD)██$(DIM)║╚$(BOLD)██$(DIM)╗$(BOLD)██$(DIM)║$(BOLD)██$(DIM)║$(RED)$(BOLD)██$(DIM)╔══$(BOLD)██$(DIM)╗   $(BOLD)██$(DIM)║$(R)
$(BOLD)$(ORANGE)  ██$(DIM)║ ╚═╝ $(BOLD)██$(DIM)║$(BOLD)██$(DIM)║$(BOLD)██$(DIM)║ ╚$(BOLD)████$(DIM)║$(BOLD)██$(DIM)║$(RED)$(BOLD)██$(DIM)║  $(BOLD)██$(DIM)║   $(BOLD)██$(DIM)║$(R)
$(DIM)$(ORANGE)  ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝$(RED)╚═╝  ╚═╝   ╚═╝  $(R)
$(DIM)                    by pchazal & rcompain — 42 Angoulême\n\n$(R)

endef
export BANNER

# ——— Rules ————————————————————————————————————————————————————————————————— #
all: banner $(MLX) $(LIBFT_A) $(LIBRT_A) $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -I$(INC_DIR) $(OBJ) $(LIBRT_A) $(LIBFT_A) $(MLX) -o $(NAME) -lSDL2 -lm -lpthread
	@printf "\r\033[2K$(CYAN)📝 Sources     $(BOLD)$(GREEN)[OK]$(R)\n"
	@printf "$(BOLD)$(GREEN)\n    ✅  minirt compiled successfully\n\n$(R)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@
	@printf "\r\033[2K$(CYAN)📝 Compiling   %s$(R)" "$<"

$(LIBFT_A):
	@make -s -C $(LIBFT_DIR)
	@printf "\r\033[2K$(CYAN)📚 Libft       $(BOLD)$(GREEN)[OK]$(R)\n"

$(LIBRT_A):
	@make -s -C $(LIBRT_DIR)
	@printf "\r\033[2K$(CYAN)🪐 Librt       $(BOLD)$(GREEN)[OK]$(R)\n"

$(MLX):
	@printf "$(DIM)$(CYAN)⚙  Building MacroLibX...$(R)\n"
	@make -s -C $(MLX_DIR)
	@printf "\r\033[2K$(CYAN)🖼  MacroLibX   $(BOLD)$(GREEN)[OK]$(R)\n"

banner:
	@printf "$$BANNER"

# ——— Cleanup ——————————————————————————————————————————————————————————————— #
clean:
	@make clean -s -C $(LIBFT_DIR)
	@make clean -s -C $(LIBRT_DIR)
	@$(RM) -r obj
	@printf "$(CYAN)🗑  Object files removed$(R)\n"

fclean: clean
	@make fclean -s -C $(LIBFT_DIR)
	@make fclean -s -C $(LIBRT_DIR)
	@$(RM) $(NAME)
	@printf "$(CYAN)🗑  Executable removed$(R)\n"

bonus: banner $(MLX) $(LIBFT_A) $(LIBRT_A) $(NAME)

re: fclean all

mlxclean:
	@make clean -s -C $(MLX_DIR)

mlxfclean:
	@make fclean -s -C $(MLX_DIR)

.PHONY: all bonus clean fclean re banner mlxclean mlxfclean
