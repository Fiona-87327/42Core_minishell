/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:19:12 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/23 15:26:16 by jiyawang         ###   ########.fr       */
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

// int	main(int ac, char **av, char **envp)
// {
// 	char		*input;
// 	t_minishell	shell;

// 	(void)ac;
// 	(void)av;
// 	signal(SIGINT, mis_signal_handler);
// 	signal(SIGQUIT, SIG_IGN);
// 	rl_event_hook = mis_check_signal_event;
// 	shell.env = dup_env(envp);
// 	shell.exit_status = 0;
// 	while (1)
// 	{
// 		input = readline("minishell$ ");
// 		if (!input)
// 		{
// 			printf("exit\n");
// 			break ;
// 		}
// 		handle_input(input, &shell);
// 		free(input);
// 	}
// 	ft_free_array(shell.env);
// 	return (0);
// }

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
	signal(SIGINT, mis_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	rl_event_hook = mis_check_signal_event;
	shell.env = dup_env(envp);
	shell.exit_status = 0;
	minishell_loop(&shell);
	ft_free_array(shell.env);
	return (shell.exit_status);
}
