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
	@echo "minishell compiled successfully!"
$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)
%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)
clean c:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean f: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all