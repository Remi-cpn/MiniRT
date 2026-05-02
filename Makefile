# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/13 11:16:05 by rcompain          #+#    #+#              #
#    Updated: 2026/05/01 10:34:15 by rcompain         ###   ########.fr        #
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
			  light_calc.c \
			  ray.c

SRC_PARSING = parsing.c \
			  parsing_line.c \
			  utils.c \
			  format_unique.c \
			  format_form_rt.c

SRC_THREADS	=

ifeq ($(MAKECMDGOALS),bonus)
SRC_SCENE	+= textures_uv.c \
			   textures_manager.c \
			   textures_bump_map.c \
			   light_merge.c \
			   fill_hit.c \
			   calc_acc.c \
			   snap_cam.c \
			   find_closest_hit.c \
			   hit_cone.c

SRC_PARSING	+= format_form_solar.c \
			   textures.c

SRC_MOVE	+= physics.c \

SRC_THREADS	= init_threads.c \
			  routine.c

SUB_DIRS	+= threads

endif

VPATH := $(SRC_DIR) \
         $(addprefix $(SRC_DIR)/, $(SUB_DIRS))

SRCS		= main.c $(SRC_MOVE) $(SRC_INIT) $(SRC_EXIT) $(SRC_SCENE) $(SRC_LRT) $(SRC_PARSING) $(SRC_THREADS)

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
