/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebronen <lebronen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:02:37 by rshay             #+#    #+#             */
/*   Updated: 2023/12/04 22:23:25 by rshay            ###   ########.fr       */
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
			current->content = ft_strdup(commande);
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

	oldpwd = malloc(9);
	current = malloc(6);
	ft_strlcpy(oldpwd, "OLDPWD=\0", 9);
	ft_strlcpy(current, "PWD=\0", 6);
	oldpwd = realloc(oldpwd, ft_strlen(oldpwd) + ft_strlen(cwd));
	ft_strlcat(oldpwd, cwd, 10 + ft_strlen(cwd));
	oldpwd[10 + ft_strlen(cwd)] = '\0';
	getcwd(nwd, sizeof(nwd));
	current = realloc(current, ft_strlen(current) + ft_strlen(nwd));
	ft_strlcat(current, nwd, 6 + ft_strlen(nwd));
	current[6 + ft_strlen(nwd)] = '\0';
	export(oldpwd, envp);
	export(current, envp);
	free(oldpwd);
	free(current);
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
