/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:50:04 by rshay             #+#    #+#             */
/*   Updated: 2023/12/01 18:39:11 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char *path)
{
	struct stat	buf;
	mode_t		mode;
	//char		*oldpwd;
	//char		*current;
	//char		cwd[256];
	//char		*swd;

	if (!path)
		path = getenv("HOME");
	stat(path, &buf);
	mode = buf.st_mode;
	//getcwd(cwd, sizeof(cwd));
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
	/*
	oldpwd = ft_strdup("OLDPWD=");
	swd = ft_strdup(cwd);
	ft_printf("swd = %s est de taille %d\n", swd, ft_strlen(swd));
	ft_strlcat(oldpwd, swd, 8 + ft_strlen(swd));
	getcwd(cwd, sizeof(cwd));
	current = ft_strdup("PWD=");
	swd = ft_strdup(cwd);
	ft_strlcat(current, swd, 5 + ft_strlen(swd));
	export(oldpwd, env);
	export(current, env);
	free(oldpwd);
	free(current);
	free(swd);
	*/
	return (0);
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

int	echo(char **str, int option, int fd)
{
	int	i;
	int	j;

	i = 1;
	while (str[i] && !ft_strcmp(str[i], "-n"))
	{
		j = 2;
		while (str[i][j])
		{
			if (str[i][j] != 'n')
			{
				i = 0;
				break;
			}
			j++;
		}
		if (!i)
		{
			i = 1;
			break;
		}
		i++;
	}
	while (str[i])
	{
		if (write(fd, str[i], ft_strlen(str[i])) == -1)
			ft_printf("write error\n");
		if (str[i + 1])
			write(fd, " ", 1);
		i++;
	}
	if (!option)
		ft_putchar_fd('\n', fd);
	return (0);
}

void	ft_exit(char **commande, t_data *data)
{
	int	err;

	err = data->last_error;
	if (commande[1])
		err = ft_atoi(commande[1]);
	data->malloc_error = 2;
	exit(err);
}
