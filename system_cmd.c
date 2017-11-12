/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 13:10:43 by dengstra          #+#    #+#             */
/*   Updated: 2017/09/14 14:58:23 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static char		*path_maker(char *path, char *str)
{
	char *new_path;

	if (!(new_path = ft_strjoinfree(0, path, 0, "/")))
		ft_error("Malloc failed");
	if (!(new_path = ft_strjoinfree(1, new_path, 0, str)))
		ft_error("Malloc failed");
	return (new_path);
}

static char		*get_cmd(char *line)
{
	char *res;

	res = NULL;
	while (*line)
	{
		if (*line++ == '/')
			res = line;
	}
	return (res);
}

static int		contains_cmd(char *path, char *cmd)
{
	DIR				*dir;
	struct dirent	*file;
	int				result;

	result = 0;
	if (!(dir = opendir(path)))
		return (result);
	while ((file = readdir(dir)))
	{
		if ((result = ft_strequ(file->d_name, cmd)))
			break ;
	}
	closedir(dir);
	return (result);
}

static int		start(char *value, char **split, char **environ)
{
	char	**paths;
	int		i;
	char	*cmd_path;

	i = 0;
	paths = ft_strsplit_e(value, ':');
	while (paths[i])
	{
		if (contains_cmd(paths[i], split[0]))
		{
			cmd_path = path_maker(paths[i], split[0]);
			if (0 == start_program(cmd_path, split, environ))
			{
				free(cmd_path);
				ft_free_split(paths);
				return (0);
			}
			free(cmd_path);
		}
		i++;
	}
	ft_free_split(paths);
	return (-1);
}

int				system_cmd(char **split, t_list *env, char **environ)
{
	char	*value;
	char	*cmd;
	int		dir_path_len;

	cmd = get_cmd(split[0]);
	if (cmd)
	{
		dir_path_len = ft_strlen(split[0]) - ft_strlen(cmd);
		split[0][dir_path_len - 1] = '\0';
	}
	if (contains_cmd(split[0], cmd))
	{
		split[0][dir_path_len - 1] = '/';
		return (start_program(split[0], split, environ));
	}
	if (!(value = get_value(env, "PATH", '\0')))
		return (-1);
	return (start(value, split, environ));
}
