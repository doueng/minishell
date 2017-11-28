/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/14 20:29:22 by douglas           #+#    #+#             */
/*   Updated: 2017/11/22 14:56:05 by douglas          ###   ########.fr       */
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
	ft_putstr(" 👉  ");
	free(cwd);
}

static void	delone(void *content, size_t size)
{
	(void)size;
	free(((t_env*)content)->key);
	free(((t_env*)content)->value);
	free(content);
}

static char	*ft_read_line(void)
{
	char		*line;
	int			size;
	int			read_return;

	size = 512;
	line = ft_strnew_e(size);
	read_return = read(0, line, size);
	if (read_return == -1)
		ft_error("read error");
	line[ft_strlen(line) - 1] = 0;
	return (line);
}

int			main(int argc, char *argv[], char *envp[])
{
	char	*line;
	t_list	*env;

	(void)argc;
	(void)argv;
	env = env_to_lst(envp);
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		print_prompt();
		ft_putstr(BOLD_TEXT);
		line = ft_read_line();
		ft_putstr(NORMAL_COLOR);
		if (ft_strequ(line, "exit") || ft_strequ(line, "q"))
			exit(0);
		do_all_cmds(line, env);
		free(line);
	}
	ft_lstdel(env, delone);
	return (0);
}
