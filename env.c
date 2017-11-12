/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 23:50:05 by douglas           #+#    #+#             */
/*   Updated: 2017/08/02 15:10:37 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_list	*find_node(t_list *node, char *key, char till)
{
	while (node)
	{
		if (ft_cmp_till((((t_env*)node->content)->key), key, till))
			return (node);
		node = node->next;
	}
	return (NULL);
}

char	*get_value(t_list *node, char *key, char till)
{
	t_list	*tmp;

	if (!(tmp = find_node(node, key, till)))
		return (NULL);
	return (((t_env*)tmp->content)->value);
}

void	new_env_node(char *new, t_list **start)
{
	t_env	env_struct;
	char	**split;
	t_list	*node;

	split = ft_strsplit_e(new, '=');
	env_struct.key = ft_strdup_e(split[0]);
	env_struct.value = ft_strdup_e(split[1]);
	if (!(node = ft_lstnew(&env_struct, sizeof(t_env))))
		ft_error("malloc failed");
	ft_lstadd_rev(start, node);
	ft_free_split(split);
}

t_list	*env_to_lst(char **environ)
{
	t_list *start;

	start = NULL;
	while (*environ)
	{
		new_env_node(*environ, &start);
		environ++;
	}
	return (start);
}
