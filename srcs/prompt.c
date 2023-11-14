/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgermain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:25:00 by cgermain          #+#    #+#             */
/*   Updated: 2023/11/14 12:25:05 by cgermain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_heredoc(t_node *node)
{
	while (node)
	{
		if (node->fd_in == -2 && node->heredoc == NULL)
			return (0);
		node = node->next;
	}
	return (1);
}

void	free_all(char *commande, t_token *token, t_node *node)
{
	free(commande);
	free_lexer(token);
	free_nodes(node);
}

void	prompt(t_data *data)
{
	char	*commande;
	t_token	*token;
	t_node	*node;

	node = NULL;
	while (1)
	{
		commande = readline("$");
		if (!commande)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		while (error_cmd(commande, data))
		{
			free(commande);
			commande = readline("$");
		}
        if  (!strncmp(commande, "exit", 4))
        {
            free(commande);
            break ;
        }
		commande = env_value_checker(commande, data);
		token = lexer(commande, data);
		node = nodizer(token, data);
		if (check_heredoc(node))
        {
            print_node(node);
			//process(node, data->envp);
		    add_history(commande);
        }
		free_all(commande, token, node);
	}
}
