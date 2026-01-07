NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror

LDFLAGS = -lreadline


MAKEFLAGS += --no-print-directory

SRCS = buit_in/mis_cd.c \
	   buit_in/mis_echo.c \
	   buit_in/mis_env.c \
	   buit_in/mis_exit.c \
	   buit_in/mis_export.c \
	   buit_in/mis_pwd.c \
	   buit_in/mis_unset.c \
	   buit_in/mis_exec.c \
	   buit_in/mis_export1.c \
	   main.c \
	   utils.c
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I $(CURDIR) -I $(CURDIR)/$(LIBFT_DIR)

all: $(NAME)
	@echo "$(G)[SUCCESS]$(NC) minishell compiled!"
$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)
%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)
G = \033[0;32m
R = \033[0;31m
Y = \033[0;33m
B = \033[0;34m
NC = \033[0m

clean c:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -f $(OBJS)
	@echo "$(Y)[CLEAN]$(NC) Objects deleted!"

fclean f: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "$(R)[FCLEAN]$(NC) $(NAME) has been deleted!"
re: fclean all
