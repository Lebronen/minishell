/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rshay <rshay@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:02:37 by rshay             #+#    #+#             */
/*   Updated: 2023/12/28 19:28:52 by rshay            ###   ########.fr       */
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
		if (!ft_strlencmp(commande, current->content, ft_index(commande, '=')))
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
	if (!ft_strcmp(commande, "PATH"))
		data->is_path = 0;
	if (!ft_strlencmp(data->envp->content, commande,
			ft_index(data->envp->content, '=')))
		free_first(&(data->envp));
	else
		remove_loop(data, commande);
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

	i = 1;
	non = 1;
	while (str[i] && is_n_good(str[i]))
	{
		non = 0;
		i++;
	}
	return (echo(str, i, non));
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
			if (ft_strlen(commande[i]) == 1 && !isalpha(commande[i][0]))
			{
				ft_printf("export: '%c' : not a valid identifier\n",
					commande[i][0]);
				data->last_error = 1;
			}
			else
			{
				str = ft_strdup(commande[i]);
				data->is_env += export(str, data);
				data->is_path = data->is_env;
			}
		}
		i++;
	}
}
