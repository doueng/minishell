/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 23:44:09 by douglas           #+#    #+#             */
/*   Updated: 2017/11/17 09:44:03 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	env_cmd(t_list *env)
{
	while (env)
	{
		ft_putstr(((t_env*)env->content)->key);
		ft_putchar('=');
		ft_putendl(((t_env*)env->content)->value);
		env = env->next;
	}
}

void	setenv_cmd(char *line, t_list *env)
{
	t_list	*node;
	char	*value;

	if (!(value = ft_strchr(line, '=')))
		return ;
	else if ((node = find_node(env, line, '=')))
	{
		free(((t_env*)node->content)->value);
		((t_env*)node->content)->value = ft_strdup_e(value + 1);
	}
	else
		new_env_node(line, &env);
}

void	unsetenv_cmd(char *key, t_list **env)
{

	*env = ft_lstdelfind(*env, lst_del_node, lst_cmp, key);
}
