/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/06 18:42:38 by douglas           #+#    #+#             */
/*   Updated: 2017/08/02 13:38:44 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void		ft_error(char *message)
{
	ft_putstr(RED_COLOR);
	ft_printf("Error: %s\n", message);
	ft_putstr(NORMAL_COLOR);
	exit(-1);
}

int			ft_strcpytill_in(char *dst, char *src, char c)
{
	int len;

	len = ft_strlen_till(src, c);
	ft_memmove(dst, src, len);
	return (len);
}
