/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:19:12 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/07 13:59:32 by jiyawang         ###   ########.fr       */
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
	char		**args;
	t_command	cmd;

	if (*input)
	{
		add_history(input);
		args = ft_split(input, ' ');
		if (args && args[0])
		{
			cmd.args = args;
			cmd.next = NULL;
			execute_command(&cmd, shell);
			ft_free_array(args);
		}
		else if (args)
			free(args);
	}
}

int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_minishell	shell;

	(void)ac;
	(void)av;
	shell.env = dup_env(envp);
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
