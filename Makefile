NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror

LDFLAGS = -lreadline

SRCS = mis_cd.c \
	   mis_echo.c \
	   mis_env.c \
	   mis_exit.c \
	   mis_export.c \
	   mis_pwd.c \
	   mis_unset.c \
	   mis_exec.c \
	   main.c
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I include -I $(LIBFT_DIR)/include

all: $(NAME)
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LIBFT) $(LDFLAGS)
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean c:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean f: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all