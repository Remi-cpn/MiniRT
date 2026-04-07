
NAME		= minirt
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -I MacroLibX/includes
RM			= rm -f
MLX_DIR 	= MacroLibX
MLX 		= $(MLX_DIR)/libmlx.so
SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= include
LIBRT_DIR		= librt
LIBFT_DIR	= libft
LIBFT_A		= $(LIBFT_DIR)/libft.a

# --- Sous-dossiers sources --------------------------------------------------
SUB_DIRS := draw exit init

# ——— Sources ——————————————————————————————————————————————————————————————— #
SRC_INIT	= init_program.c

SRC_EXIT	= exit_program.c

SRC_DRAW	= draw.c

SRC_LRT		= vec_norm.c vec_operator.c

VPATH := $(SRC_DIR) \
         $(addprefix $(SRC_DIR)/, $(SUB_DIRS)) \
         $(LIBRT_DIR)

SRCS		= $(SRC_INIT) $(SRC_EXIT) $(SRC_DRAW) $(SRC_LRT)

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
all: banner $(MLX) $(LIBFT_A) $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -I$(INC_DIR) $(OBJ) $(LIBFT_A) $(MLX) -o $(NAME) -lSDL2
	@printf "\r\033[2K$(CYAN)📝 Sources     $(BOLD)$(GREEN)[OK]$(R)\n"
	@printf "$(BOLD)$(GREEN)\n    ✅  minirt compiled successfully\n\n$(R)"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@
	@printf "\r\033[2K$(CYAN)📝 Compiling   %s$(R)" "$<"

$(LIBFT_A):
	@make -s -C $(LIBFT_DIR)
	@printf "\r\033[2K$(CYAN)📚 Libft       $(BOLD)$(GREEN)[OK]$(R)\n"

$(MLX):
	@printf "$(DIM)$(CYAN)⚙  Building MacroLibX...$(R)\n"
	@make -s -C $(MLX_DIR)
	@printf "\r\033[2K$(CYAN)🖼  MacroLibX   $(BOLD)$(GREEN)[OK]$(R)\n"

banner:
	@printf "$$BANNER"

# ——— Cleanup ——————————————————————————————————————————————————————————————— #
clean:
	@make clean -s -C $(LIBFT_DIR)
	@$(RM) -r $(OBJ_DIR)
	@printf "$(CYAN)🗑  Object files removed$(R)\n"

fclean: clean
	@make fclean -s -C $(LIBFT_DIR)
	@$(RM) $(NAME)
	@printf "$(CYAN)🗑  Executable removed$(R)\n"

re: fclean all

mlxclean:
	@make clean -s -C $(MLX_DIR)

mlxfclean:
	@make fclean -s -C $(MLX_DIR)

.PHONY: all clean fclean re banner mlxclean mlxfclean
