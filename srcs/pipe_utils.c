/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: rshay <rshay@student.42.fr>				+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/11/16 21:33:18 by lebronen		  #+#	#+#			 */
/*   Updated: 2023/11/29 16:57:53 by rshay            ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

int	wait_for_childrens(int nb)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i <= nb)
	{
		wait(&status);
		i++;
	}
	return (WEXITSTATUS(status));
}

void	pipe_process(t_node *tmp, int *fd1, int *fd2, int nb)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (tmp->fd_in != STDIN_FILENO)
			ft_redirect_in(tmp, tmp->data);
		else
		{
			if (nb)
			{
				dup2(fd1[0], STDIN_FILENO);
				close(fd1[0]);
				close(fd1[1]);
				if (nb > 1)
				{	
					close(fd2[0]);
					close(fd2[1]);
				}
			}
		}
		ft_redirect_out(tmp);
		exec_cmd(tmp, tmp->data);
	}
}

void	close_pipes(int *fd1, int *fd2, int i)
{
	if (fd1[0] != -1)
		close(fd1[0]);
	if (fd1[1] != -1)
		close(fd1[1]);
	if (i)
	{	
		close(fd2[0]);
		close(fd2[1]);
	}
}

void	pipe_loop(t_node *tmp, int *fd1, int *fd2, int j)
{
	if (is_dir(tmp->str_options[0]))
	{
		tmp->data->last_error = 126;
		ft_printf("%s: Is a  directory\n", tmp->str_options[0]);
		return ;
	}
	if (j % 2 == 0)
	{
		pipe(fd1);
		child_process(tmp, fd1, fd2, j);
	}
	else
	{
		pipe(fd2);
		child_process(tmp, fd2, fd1, j);
	}
}
