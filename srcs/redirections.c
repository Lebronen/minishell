/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:05:03 by cgermain          #+#    #+#             */
/*   Updated: 2023/11/03 16:22:25 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_out(t_token *token, int fd_in)
{
	int	fd;

	fd = 1;
	while (fd_in != -1 && token && token->type != PIPE)
	{
		if (token->type_2 == OUT)
		{
			if (fd != 1)
				close(fd);
			fd = open(token->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (-1);
		}
		if (token->type_2 == APPEND)
		{
			if (fd != 1)
				close(fd);
			fd = open(token->next->str, O_CREAT | O_RDWR | O_APPEND,
					S_IRUSR | S_IWUSR, 0644);
			if (fd == -1)
				return (-1);
		}
		token = token->next;
	}
	return (fd);
}

int	has_heredoc(t_token *token)
{
	while (token && token->type != PIPE)
	{
		if (token->type_2 == EOF)
			return (1);
		token = token->next;
	}
	return (0);
}

int	init_in(t_token *token, t_data *data)
{
	int	fd;

	fd = 0;
	while (token && token->type != PIPE)
	{
		if (token->type_2 == IN)
		{
			if (fd != 0 && fd != -2)
				close(fd);
			fd = open(token->next->str, O_RDONLY);
			if (fd == -1)
				return (input_error(token->next->str, data));
		}
		else if (token->type_2 == ENDOF)
		{
			if (fd != 0 && fd != -2)
				close(fd);
			fd = -2;
		}
		token = token->next;
	}
	return (fd);
}
