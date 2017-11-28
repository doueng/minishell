/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 14:16:29 by douglas           #+#    #+#             */
/*   Updated: 2017/11/19 22:45:49 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int				start_program(char *cmd_path, char **cmd, char **environ)
{
	pid_t	pid;

	if (access(cmd_path, X_OK))
		return (-1);
	if ((pid = fork()) < 0)
		ft_error("fork failed");
	if (pid == 0)
		exit(execve(cmd_path, cmd, environ));
	else
		wait(&pid);
	if (WIFEXITED(pid))
		return (WEXITSTATUS(pid));
	return (-1);
}

static int		exe_cmd(char **split, char **environ)
{
	return (start_program(split[0], split, environ));
}

char			**lst_to_environ(t_list *env)
{
	char	**environ;
	char	*e;
	char	*key;
	char	*value;
	int		i;

	if (!env)
		return (NULL);
	environ = (char**)ft_malloc_e(sizeof(char*) * (ft_lst_len(env) + 1));
	i = 0;
	while (env)
	{
		key = ((t_env*)env->content)->key;
		value = ((t_env*)env->content)->value;
		e = ft_strnew_e(ft_strlen(key) + ft_strlen("=") + ft_strlen(value));
		environ[i++] = e;
		e = ft_strcat_end(e, key);
		e = ft_strcat_end(e, "=");
		e = ft_strcat_end(e, value);
		env = env->next;
	}
	environ[i] = NULL;
	return (environ);
}

void			do_cmds(char *line, t_list *env)
{
	char **split;
	char *cwd;
	char *path;
	char **environ;

	environ = lst_to_environ(env);
	if (!(cwd = getcwd(NULL, 0)))
		ft_error("getcwd failed");
	path = ft_strjoin_e("PWD=", cwd);
	setenv_cmd(path, env);
	free(path);
	split = ft_strsplit_e(line, ' ');
	replacer(env, split);
	if (0 == builtin_cmd(split, env, cwd))
		;
	else if (0 == system_cmd(split, env, environ))
		;
	else if (0 == exe_cmd(split, environ))
		;
	else
		ft_printf("command not found: %s\n", line);
	free(cwd);
	ft_free_split(split);
	ft_free_split(environ);
}
