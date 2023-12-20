/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebronen <lebronen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:02:37 by rshay             #+#    #+#             */
/*   Updated: 2023/12/20 12:30:47 by lebronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export(char *commande, t_data *data)
{
	t_list	*current;
	t_list	*new;
	int		here;

	here = 0;
	current = data->envp;
	while (current)
	{
		if (!ft_strncmp(current->content, commande, ft_index(commande, '=')))
		{
			free(current->content);
			current->content = commande;
			here = 1;
		}
		current = current->next;
	}
	if (!here)
	{
		new = ft_lstdupnew(commande);
		ft_lstadd_back(&(data->envp), new);
		if (!ft_strncmp(commande, "PATH", 4))
			return (1);
	}
	return (0);
}

int	unset(char *commande, t_data *data)
{
	t_list	*current;
	t_list	*next;

	if (!ft_strcmp(commande, "PATH"))
		data->is_path = 0;
	if (!ft_strcmp(data->envp->content, commande))
		free_first(&(data->envp));
	else
	{
		current = data->envp;
		while (current && current ->next)
		{
			if (ft_str_only_ncmp(current->next->content,
					commande, ft_strlen(commande)))
			{
				next = current->next->next;
				free(current->next->content);
				free(current->next);
				current->next = next;
			}
			current = current->next;
		}
	}
	data->envlen -= 1;
	return (0);
}

int	update_pwd(char *cwd, t_data *data)
{
	char	*oldpwd;
	char	*current;
	char	nwd[256];
	char	*tmp;

	tmp = ft_strdup("OLDPWD=");
	oldpwd = ft_strjoin(tmp, cwd);
	getcwd(nwd, sizeof(nwd));
	free(tmp);
	tmp = ft_strdup("PWD=");
	current = ft_strjoin(tmp, nwd);
	export(oldpwd, data);
	export(current, data);
	free(tmp);
	return (0);
}

int	n_parsing(char **str)
{
	int	i;
	int	non;
	int	j;

	i = 1;
	non = 1;
	while (str[i] && !ft_strcmp(str[i], "-n"))
	{
		j = 2;
		while (str[i][j])
		{
			if (str[i][j] != 'n')
			{
				non = 0;
				break ;
			}
			j++;
		}
		if (!non)
			break ;
		i++;
	}
	return (i);
}

void	loop_export(char **commande, t_data *data)
{
	int		i;
	char	*str;

	i = 1;
	if (!commande[1])
		only_export(data);
	while (commande[i])
	{
		if (ft_index(commande[i], '=') != -1)
		{	
			str = ft_strdup(commande[i]);
			data->is_env += export(str, data);
			data->is_path = data->is_env;
		}
		i++;
	}
}
