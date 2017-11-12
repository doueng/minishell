/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_all_cmds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 13:17:38 by dengstra          #+#    #+#             */
/*   Updated: 2017/08/06 13:23:07 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int		contains_alnum(char *str)
{
	if (!str)
		return (0);
	while (*str)
		if (ft_isalnum(*str++) || *str == '.' || *str == '/')
			return (1);
	return (0);
}

void	do_all_cmds(char *line, t_list *env)
{
	char	*tmp;

	if (!contains_alnum(line))
		return ;
	if (!(tmp = ft_strchr(line, ';')))
		return (do_cmds(line, env));
	*tmp = '\0';
	do_cmds(line, env);
	do_all_cmds(tmp + 1, env);
}
