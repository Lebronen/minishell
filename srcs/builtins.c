/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebronen <lebronen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:50:04 by rshay             #+#    #+#             */
/*   Updated: 2023/12/04 15:00:55 by lebronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char *path, t_list *env)
{
	struct stat	buf;
	mode_t		mode;
	char		cwd[256];

	if (!path)
		path = "/home/lebronen";
	stat(path, &buf);
	mode = buf.st_mode;
	getcwd(cwd, sizeof(buf));
	if (chdir(path) < 0)
	{
		if (access(path, F_OK))
			ft_printf("No such file or directory\n");
		else if (!S_ISDIR(mode))
			ft_printf("cd: not a directory: %s\n", path);
		else if (!(mode & S_IXUSR))
			ft_printf("cd: permission denied: %s\n", path);
		return (1);
	}
	return (update_pwd(cwd, env));
}

int	pwd(void)
{
	char	cwd[256];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		ft_printf("getcwd error\n");
		return (1);
	}
	else
		ft_printf("%s\n", cwd);
	return (0);
}

int	env(t_data *data)
{
	t_list	*current;

	if (!data->envp)
	{
		ft_printf("env error\n");
		return (127);
	}
	current = data->envp;
	while (current)
	{
		ft_printf("%s\n", current->content);
		current = current->next;
	}
	return (0);
}

int	echo(char *str, int option, int fd)
{
	if (write(fd, str, ft_strlen(str)) == -1)
	{
		ft_printf("write error\n");
		return (1);
	}
	if (!option)
		ft_putchar_fd('\n', fd);
	return (0);
}
