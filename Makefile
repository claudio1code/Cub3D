NAME = fractol

CC = cc
CFLAGS = -Wall -Werror -Wextra -O3

SRCS_DIR = srcs/
OBJS_DIR = objs/
INCS_DIR = includes/
LIBFT_DIR = libft/
MLX_DIR = minilibx-linux/

SRCS_LIST = 	

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_LIST))
OBJS = $(addprefix $(OBJS_DIR), $(SRCS_LIST:.c=.o))

LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx.a

INCLUDES = -I $(INCS_DIR) -I $(LIBFT_DIR)/includes -I $(MLX_DIR)
LDFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

GREEN = \033[0;92m
YELLOW = \033[0;96m
BLUE = \033[1;96m
RED = \033[1;31m
RESET = \033[0;39m

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	@printf "$(YELLOW)Linking $(NAME)... $(RESET)"
	@sh -c '(while kill -0 $$PPID 2>/dev/null; do \
		echo -n "\b|"; sleep 0.05; \
		echo -n "\b/"; sleep 0.05; \
		echo -n "\b-"; sleep 0.05; \
		echo -n "\b\\"; sleep 0.05; \
	done) & trap "kill $$!" EXIT; \
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME) '
	@printf "\b$(GREEN)OK!$(RESET)\n"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(dir $@)
	@printf "$(BLUE)Compiling $<... $(RESET)"
	@sh -c '(while kill -0 $$PPID 2>/dev/null; do \
		echo -n "\b|"; sleep 0.05; \
		echo -n "\b/"; sleep 0.05; \
		echo -n "\b-"; sleep 0.05; \
		echo -n "\b\\"; sleep 0.05; \
	done) & trap "kill $$!" EXIT; \
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@'
	@printf "\b$(GREEN)OK!$(RESET)\n"

$(LIBFT):
	@make -sC $(LIBFT_DIR)

$(MLX_LIB):
	@make -sC $(MLX_DIR)
clean:
	@rm -rf $(OBJS_DIR)
	@make -sC $(LIBFT_DIR) clean
	@make -sC $(MLX_DIR) clean
	@printf "$(RED) Objects cleaned!$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@make -sC $(LIBFT_DIR) fclean
	@printf "$(RED) Executable cleaned!$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re