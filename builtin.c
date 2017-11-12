/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 23:47:16 by douglas           #+#    #+#             */
/*   Updated: 2017/09/14 15:32:33 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	cd_cmd(char *line, char **line_split, t_list *env, char *cwd)
{
	char *path;

	if (ft_split_len(line_split) > 2)
		return ((void)ft_printf("cd: too many arguments\n"));
	line = ft_strtrim(line);
	if (ft_strequ(line, "cd"))
		path = get_value(env, "HOME", '\0');
	else if (ft_strequ(line, "o") || ft_strequ(line, "cd -"))
		path = get_value(env, "OLDPWD", '\0');
	else
		path = line_split[1];
	if (chdir(path) == -1)
		ft_printf("cd: no such file or directory: %s\n", path);
	else
	{
		path = ft_strjoin_e("OLDPWD=", cwd);
		setenv_cmd(path, env);
	}
	free(line);
	free(path);
}

static void	pwd_cmd(char **line, char *cwd)
{
	if (line[1])
		ft_putendl("pwd: too many arguments");
	else
		ft_putendl(cwd);
}

static void	echo_cmd(char *line, t_list *env, t_list *node)
{
	while (*line)
	{
		if (*line == '"')
		{
			while (*line == '"')
				line++;
			line = ft_print_till(line++, '"');
		}
		else if (*line == '$')
		{
			line++;
			if ((node = find_node(env, line, ' ')))
				ft_putstr(((t_env*)node->content)->value);
			if (node)
				line += ft_strlen(((t_env*)node->content)->key) - 1;
		}
		else
		{
			line = ft_print_till(line, ' ');
			if (*line)
				ft_putchar(*line++);
		}
	}
	ft_putchar('\n');
}

int			builtin_cmd(char *line, char **split, t_list *env, char *cwd)
{
	t_list *node;

	node = NULL;
	if (ft_strequ(split[0], "echo"))
		echo_cmd(line + 5, env, node);
	else if (ft_strequ(split[0], "pwd"))
		pwd_cmd(split, cwd);
	else if (ft_strequ(split[0], "env"))
		env_cmd(env);
	else if (ft_strequ(split[0], "setenv"))
		setenv_cmd(split[1], env);
	else if (ft_strequ(split[0], "unsetenv"))
		unsetenv_cmd(split[1], &env);
	else if (ft_strequ(split[0], "cd"))
		cd_cmd(line, split, env, cwd);
	else
		return (-1);
	return (0);
}
