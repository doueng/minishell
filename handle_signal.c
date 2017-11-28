/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 22:42:15 by douglas           #+#    #+#             */
/*   Updated: 2017/11/20 16:18:31 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void		handle_signal(int sig_num)
{
	if (sig_num == SIGINT)
		;
		// signal(SIGINT, handle_signal);
	else if (sig_num == SIGTSTP)
		;
		// signal(SIGTSTP, handle_signal);
}
