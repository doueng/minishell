/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/14 20:29:22 by douglas           #+#    #+#             */
/*   Updated: 2017/09/02 16:56:19 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	print_prompt(void)
{
	int		slash;
	int		i;
	char	*cwd;

	if (!(cwd = getcwd(NULL, 0)))
		ft_error("getcwd failed");
	i = 0;
	slash = 0;
	while (cwd[i])
		if (cwd[i++] == '/')
			slash = i;
	slash = (slash == 1) ? 0 : slash;
	ft_putstr(BOLD_TEXT);
	ft_print_color(&cwd[slash], CYAN_COLOR);
	ft_putstr(CYAN_COLOR);
	ft_printf("%ls", L" 👉  ");
	ft_putstr(NORMAL_COLOR);
	free(cwd);
}

static char	*replace_all(char c, char *line, char *insert)
{
	char	*res;
	int		cpyed;
	int		count;
	char	*result;
	char	*start;

	if (!ft_strchr(line, c) || !insert)
		return (line);
	start = line;
	count = ft_count_chars(line, c);
	res = ft_strnew_e(ft_strlen(line) + count * ft_strlen(insert) + 10);
	result = res;
	while (count--)
	{
		cpyed = ft_strcpytill_in(res, line, c);
		line += cpyed + 1;
		res += cpyed;
		res += ft_strcpytill_in(res, insert, '\0');
	}
	ft_strcpytill_in(res, line, c);
	free(start);
	return (result);
}

static void	delone(void *content, size_t size)
{
	(void)size;
	free(((t_env*)content)->key);
	free(((t_env*)content)->value);
	free(content);
}

int			main(int argc, char *argv[], char *envp[])
{
	char	*line;
	t_list	*env;

	(void)argc;
	(void)argv;
	env = env_to_lst(envp);
	while (1)
	{
		print_prompt();
		ft_putstr(BOLD_TEXT);
		get_next_line(0, &line);
		ft_putstr(NORMAL_COLOR);
		if (ft_strequ(line, "exit") || ft_strequ(line, "q"))
			exit(0);
		line = replace_all('~', line, get_value(env, "HOME", '\0'));
		do_all_cmds(line, env);
		free(line);
	}
	ft_lstdel(env, delone);
	return (0);
}
