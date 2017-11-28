/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 23:47:16 by douglas           #+#    #+#             */
/*   Updated: 2017/11/19 22:15:21 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static void	cd_cmd(char **split, t_list *env, char *cwd)
{
	char *path;

	if (ft_split_len(split) > 2)
		return ((void)ft_printf("cd: too many arguments\n"));
	if (ft_strequ(split[0], "cd") && !split[1])
		path = get_value(env, "HOME", '\0');
	else if (ft_strequ(split[0], "cd") && ft_strequ(split[1], "-"))
		path = get_value(env, "OLDPWD", '\0');
	else
		path = split[1];
	if (chdir(path) == -1)
		ft_printf("cd: no such file or directory: %s\n", path);
	path = ft_strjoin_e("OLDPWD=", cwd);
	setenv_cmd(path, env);
	free(path);
}

static void	pwd_cmd(char **split, char *cwd)
{
	if (split[1])
		ft_putendl("pwd: too many arguments");
	else
		ft_putendl(cwd);
}

static void	echo_cmd(char **split)
{
	while (*++split)
	{
		ft_putstr(*split);
		if (*(split + 1))
			ft_putchar(' ');
	}
	ft_putchar('\n');
}

int			builtin_cmd(char **split, t_list *env, char *cwd)
{
	t_list *node;

	node = NULL;
	if (ft_strequ(split[0], "echo"))
		echo_cmd(split);
	else if (ft_strequ(split[0], "pwd"))
		pwd_cmd(split, cwd);
	else if (ft_strequ(split[0], "env"))
		env_cmd(env);
	else if (ft_strequ(split[0], "setenv"))
		setenv_cmd(split[1], env);
	else if (ft_strequ(split[0], "unsetenv"))
		unsetenv_cmd(split[1], &env);
	else if (ft_strequ(split[0], "cd"))
		cd_cmd(split, env, cwd);
	else
		return (-1);
	return (0);
}
