/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/19 23:23:47 by douglas           #+#    #+#             */
/*   Updated: 2017/11/17 12:11:21 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat_end(char *dest, char *src)
{
	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	return (dest);
}
