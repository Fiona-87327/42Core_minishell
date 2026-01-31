/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:19:12 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/26 20:28:29 by jiyawang         ###   ########.fr       */
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
		if (shell->should_exit)
			break ;
		input = get_input();
		if (!input)
		{
			if (isatty(STDIN_FILENO))
				ft_putstr_fd("exit\n", STDOUT_FILENO);
			shell->should_exit = 1;
			break ;
		}
		if (*input)
		{
			if (isatty(STDIN_FILENO))
				add_history(input);
			handle_input(input, shell);
		}
		free(input);
		if (shell->should_exit)
			break ;
	}
}

static void	update_shlvl(t_minishell *sh)
{
	char	*current_val;
	int		lvl;
	char	*new_val;
	char	*tmp;

	current_val = get_env_value(sh->env, "SHLVL");
	if (current_val)
		lvl = ft_atoi(current_val);
	else
		lvl = 0;
	lvl++;
	new_val = ft_itoa(lvl);
	tmp = ft_strjoin("SHLVL=", new_val);
	add_to_env(sh, tmp);
	free(new_val);
	free(tmp);
}

int	main(int ac, char **av, char **envp)
{
	t_minishell	shell;

	(void)ac;
	(void)av;
	setup_signal();
	rl_event_hook = mis_check_signal_event;
	shell.env = dup_env(envp);
	update_shlvl(&shell);
	if (!shell.env || !shell.env[0])
		shell.env = init_min_env();
	shell.exit_status = 0;
	shell.should_exit = 0;
	shell.cmds = NULL;
	minishell_loop(&shell);
	ft_free_array(shell.env);
	return (shell.exit_status);
}
