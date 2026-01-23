/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:19:12 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/23 16:22:30 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**dup_env(char **envp)
{
	char	**new_env;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

static void	setup_signal(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = mis_signal_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

static void	check_ctrl_c(t_minishell *shell)
{
	if (g_signal == SIGINT)
	{
		shell->exit_status = 130;
		g_signal = 0;
	}
}

static char	*get_input(void)
{
	char	*input;
	char	*line;

	input = NULL;
	line = NULL;
	if (isatty(STDIN_FILENO))
		input = readline("minishell$ ");
	else
	{
		line = get_next_line(STDIN_FILENO);
		if (line)
		{
			input = ft_strtrim(line, "\n");
			free(line);
		}
		else
			input = NULL;
	}
	return (input);
}

void	minishell_loop(t_minishell *shell)
{
	char	*input;

	while (1)
	{
		check_ctrl_c(shell);
		input = get_input();
		if (!input)
			break ;
		if (*input)
		{
			if (isatty(STDIN_FILENO))
				add_history(input);
			handle_input(input, shell);
		}
		free(input);
	}
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", STDOUT_FILENO);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	shell;

	(void)ac;
	(void)av;
	setup_signal();
	rl_event_hook = mis_check_signal_event;
	shell.env = dup_env(envp);
	shell.exit_status = 0;
	minishell_loop(&shell);
	ft_free_array(shell.env);
	return (shell.exit_status);
}
