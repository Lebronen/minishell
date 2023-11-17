/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebronen <lebronen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:25:00 by cgermain          #+#    #+#             */
/*   Updated: 2023/11/17 17:00:11 by lebronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char    cwd[256];

	node = NULL;
	while (1)
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
            perror("getcwd error\n");
        ft_strlcat(cwd, "~$", 256);
        commande = readline(cwd);
		if (!commande)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		while (error_cmd(commande, data))
		{
			free(commande);
			commande = readline(cwd);
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
			process(node, data);
		    add_history(commande);
        }
		free_all(commande, token, node);
	}
    	rl_clear_history();
}
