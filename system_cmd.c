/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 13:10:43 by dengstra          #+#    #+#             */
/*   Updated: 2017/11/17 12:12:21 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static char		*path_maker(char *path, char *cmd)
{
	char *new_path;
	char *tmp;

	new_path = ft_strnew_e(ft_strlen(path) + sizeof('/') + ft_strlen(cmd));
	tmp = ft_strcat_end(new_path, path);
	tmp = ft_strcat_end(tmp, "/");
	ft_strcat_end(tmp, cmd);
	return (new_path);
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

int				system_cmd(char **split, t_list *env, char **environ)
{
	char	**paths;
	int		i;
	char	*cmd_path;
	char	*path_env;

	i = 0;
	if (!(path_env = get_value(env, "PATH", '\0')))
		return (-1);
	paths = ft_strsplit_e(path_env, ':');
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
