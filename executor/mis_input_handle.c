/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mis_input_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhnatovs <mhnatovs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 13:08:14 by jiyawang          #+#    #+#             */
/*   Updated: 2026/01/26 18:53:28 by mhnatovs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_input(char *input, t_token **tokens, t_minishell *shell)
{
	if (check_quotes_balance(input))
	{
		syntax_error("unclosed quotes");
		shell->exit_status = 258;
		return (-1);
	}
	*tokens = tokenize(input);
	if (!*tokens || check_syntax(*tokens))
	{
		shell->exit_status = 2;
		free_tokens(*tokens);
		return (-1);
	}
	return (0);
}

static void	process_and_executor(t_command *cmds, t_minishell *shell)
{
	process_heredocs(cmds, shell);
	expand_cmds(cmds, shell);
	if (cmds->next)
		mis_pipes(cmds, shell);
	else if (cmds->args && cmds->args[0])
		execute_command(cmds, shell);
}

void	handle_input(char *input, t_minishell *shell)
{
	t_token		*tokens;
	t_command	*cmds;

	if (ft_isspaces(input))
		return ;
	if (!*input)
		return ;
	// add_history(input);
	if (validate_input(input, &tokens, shell) == -1)
	{
		if (g_signal != SIGINT)
			return ;
	}
	cmds = parse_tokens(tokens);
	free_tokens(tokens);
	if (!cmds)
	{
		shell->exit_status = 1;
		return ;
	}
	process_and_executor(cmds, shell);
	free_cmds(cmds);
}
