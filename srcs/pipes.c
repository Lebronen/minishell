/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: rshay <rshay@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/11/12 18:46:18 by lebronen		  #+#	#+#			 */
/*   Updated: 2023/11/29 16:39:49 by rshay            ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

void	child_process(t_node *tmp, int *fd1, int *fd2, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		error(tmp->data);
	if (pid == 0)
	{
		if (tmp->fd_in != STDIN_FILENO)
			ft_redirect_in(tmp, tmp->data);
		else
		{
			if (i)
			{
				dup2(fd2[0], STDIN_FILENO);
			}
		}
		if (tmp->fd_out != STDOUT_FILENO)
			ft_redirect_out(tmp);
		else
			dup2(fd1[1], STDOUT_FILENO);
		close_pipes(fd1, fd2, i);
		execute(tmp->str_options, tmp->data);
	}
}

int	parent_process(t_node *tmp, int *fd1, int *fd2, int nb)
{
	int		in;
	int		out;

	if (is_builtin(tmp->str_options))
	{
		if (!is_only_builtin(tmp->str_options))
		{
			in = dup(STDIN_FILENO);
			out = dup(STDOUT_FILENO);
			ft_redirect_in(tmp, tmp->data);
			ft_redirect_out(tmp);
			is_builtin_exec(tmp->str_options, tmp->data);
			dup2(in, STDIN_FILENO);
			close(in);
			dup2(out, STDOUT_FILENO);
			close(out);
		}
		else if (!nb)
		{
			is_builtin_exec(tmp->str_options, tmp->data);
		}
		return (0);
	}
	pipe_process(tmp, fd1, fd2, nb);
	return (0);
}

int	nb_pipes(t_node *node)
{
	t_node	*current;
	int		i;

	current = node;
	i = 0;
	while (current->next)
	{
		i++;
		current = current->next;
	}
	return (i);
}

void	ft_last_cmd(t_node *node, int *fd1, int *fd2, int nb)
{
	if (is_dir(node->str_options[0]))
	{
		node->data->last_error = 126;
		ft_printf("%s: Is a  directory\n", node->str_options[0]);
		return ;
	}
	if (nb % 2)
			nb -= parent_process(node, fd1, fd2, nb);
	else
			nb -= parent_process(node, fd2, fd1, nb);
	if (nb)
	{
		close(fd1[0]);
		close(fd1[1]);
		if (nb > 1)
		{
			close(fd2[0]);
			close(fd2[1]);
		}
	}
	if (!is_only_builtin(node->str_options))
		node->data->last_error = wait_for_childrens(nb);
}

void	ft_pipe(t_node *tmp, int *fd1, int *fd2, int nb)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (++i < nb)
	{
		if (!tmp->str_options || !tmp->str_options[0]
			|| is_only_builtin(tmp->str_options))
		{
			if (!j)
				fd2[0] = STDIN_FILENO;
			nb--;
		}
		else
		{
			pipe_loop(tmp, fd1, fd2, j);
			j++;
		}
		tmp = tmp->next;
	}
	if (tmp->str_options && tmp->str_options[0])
		ft_last_cmd(tmp, fd1, fd2, nb);
}
