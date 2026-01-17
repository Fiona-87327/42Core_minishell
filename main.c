/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:58:33 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/17 16:35:20 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

void	execute_command(t_command *cmd, t_minishell *shell)
{
	if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		mis_pwd(cmd, shell);
	else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		mis_echo(cmd, shell);
	else if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		mis_cd(cmd, shell);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		mis_env(cmd, shell);
	else if (ft_strncmp(cmd->args[0], "exit", 5) == 0)
		mis_exit(cmd, shell);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		mis_export(cmd, shell);
	else if (ft_strncmp(cmd->args[0], "unset", 6) == 0)
		mis_unset(cmd, shell);
	else
		mis_exec(cmd, shell);
}

void	handle_input(char *input, t_minishell *shell)
{
	t_token		*tokens;
	t_command	*cmds;
	t_command	*curr;
	char		**expanded_args;

	if (*input)
	{
		add_history(input);
		tokens = tokenize(input);
		if (!tokens)
			return ;
		cmds = parse_tokens(tokens);
		free_tokens(tokens);
		if (cmds)
		{
			process_heredocs(cmds);
			curr = cmds;
			while (curr)
			{
				expanded_args = expand_args(curr->args, shell);
				if (expanded_args)
				{
					ft_free_array(curr->args);
					curr->args = expanded_args;
				}
				curr = curr->next;
			}
			if (cmds->next)
				mis_pipes(cmds, shell);
			else if (cmds->args && cmds->args[0])
				execute_command(cmds, shell);
			free_cmds(cmds);
		}
	}
}

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

int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_minishell	shell;

	(void)ac;
	(void)av;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	rl_event_hook = check_signal_event;
	shell.env = dup_env(envp);
	shell.exit_status = 0;
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		handle_input(input, &shell);
		free(input);
	}
	ft_free_array(shell.env);
	return (0);
}
