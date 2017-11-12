/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 23:44:54 by douglas           #+#    #+#             */
/*   Updated: 2017/07/16 00:01:10 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void		lst_del_node(void *content, size_t size)
{
	t_env	*env_info;

	(void)size;
	env_info = (t_env*)content;
	free(env_info->key);
	free(env_info->value);
	free(env_info);
}

int			lst_cmp(void *env, void *find)
{
	char	*key;

	key = ((t_env*)env)->key;
	return (ft_strcmp(key, (char*)find));
}
