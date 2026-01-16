/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 20:19:12 by jiyawang          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2026/01/11 12:04:07 by mhnatovs         ###   ########.fr       */
=======
/*   Updated: 2026/01/16 17:04:46 by mhnatovs         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

void	execute_command(t_command *cmd, t_minishell *shell)
{
	t_command	*cur;

	cur = cmd;
	while (cur)
	{
		if (!cur->args || !cur->args[0])
		{
			cur = cur->next;
			continue ;
		}
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
		cur = cur->next;
	}
}

void	handle_input(char *input, t_minishell *shell)
{
	t_token		*tokens;
	t_command	*cmds;
	

	if (!*input)
		return ;
	add_history(input);
	tokens = tokenize(input);
	if (!tokens || check_syntax(tokens))
	{
		shell->exit_status = 2;
		free(tokens);//free_tokens?
		return ;
	}
	cmds = parse_tokens(tokens, shell);
	expand_cmds(cmds, shell);
	execute_command(cmds, shell);
	free_tokens(tokens);
	// free_commands(cmds);
}

void	free_tokens(t_token *t)
{
	t_token	*tmp;

	while (t)
	{
		tmp = t->next;
		free(t->value);
		free(t);
		t = tmp;
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
	signal(SIGINT, mis_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	// signal(SIGTSTP, SIG_IGN);
	rl_event_hook = mis_check_signal_event;
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
