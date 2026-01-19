NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror

LDFLAGS = -lreadline

MAKEFLAGS += --no-print-directory

SRCS = executor/built_in/mis_cd.c \
	   executor/built_in/mis_cd_util.c \
	   executor/built_in/mis_echo.c \
	   executor/built_in/mis_env.c \
	   executor/built_in/mis_exit.c \
	   executor/built_in/mis_export.c \
	   executor/built_in/mis_pwd.c \
	   executor/built_in/mis_unset.c \
	   executor/built_in/mis_exec.c \
	   executor/utils/00_utils.c \
	   executor/utils/env_utils.c \
	   executor/mis_redirections.c \
	   executor/mis_pipes_helper.c \
	   executor/mis_execute_cmd.c \
	   executor/mis_pipes.c \
	   parser/expansion.c \
	   parser/lexer.c \
	   parser/lexer_utils.c \
	   parser/syntax_checker.c \
	   parser/mis_input_handle.c \
	   parser/parser.c \
	   parser/quotes.c \
	   parser/mis_heredoc.c \
	   signal/mis_signal.c \
	   main.c
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I $(CURDIR)/include -I $(CURDIR) -I $(CURDIR)/$(LIBFT_DIR)

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

valgrind v: $(NAME)
	valgrind --leak-check=full  --show-leak-kinds=all --track-fds=yes --suppressions=sub.sub  ./minishell

.PHONY: all clean fclean re c f v