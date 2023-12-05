/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:02:37 by rshay             #+#    #+#             */
/*   Updated: 2023/12/05 16:57:10 by rshay            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export(char *commande, t_list *envp)
{
	t_list	*current;
	t_list	*new;
	int		here;

	here = 0;
	current = envp;
	while (current)
	{
		if (!ft_strncmp(current->content, commande, ft_index(commande, '=')))
		{
			current->content = commande;
			here = 1;
		}
		current = current->next;
	}
	if (!here)
	{
		new = ft_lstdupnew(commande);
		ft_lstadd_back(&envp, new);
		if (!ft_strncmp(commande, "PATH", 4))
			return (1);
	}
	return (0);
}

int	unset(char *commande, t_list *envp)
{
	t_list	*current;
	t_list	*next;

	current = envp;
	while (current && current ->next)
	{
		if (!ft_strncmp(current->next->content, commande, ft_strlen(commande)))
		{
			next = current->next->next;
			ft_lstdelone(current->next, &del);
			current->next = next;
		}
		current = current->next;
	}
	return (0);
}

int	update_pwd(char *cwd, t_list *envp)
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
	export(oldpwd, envp);
	export(current, envp);
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
	while (commande[i])
	{
		if (ft_index(commande[i], '=') != -1)
		{	
			str = ft_strdup(commande[i]);
			data->is_env += export(str, data->envp);
		}
		i++;
	}
}
