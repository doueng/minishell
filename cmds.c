/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/15 14:16:29 by douglas           #+#    #+#             */
/*   Updated: 2017/09/14 15:33:15 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int				start_program(char *cmd_path, char **cmd, char **environ)
{
	pid_t	pid;

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

static int		exe_cmd(char **split, char *cwd, char **environ)
{
	char	*exe;
	int		success;

	exe = ft_strjoin_e(cwd, &split[0][1]);
	success = start_program(exe, split, environ);
	free(exe);
	return (success);
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
	if (!contains_alnum(line))
		return ;
	if (!(cwd = getcwd(NULL, 0)))
		ft_error("getcwd failed");
	path = ft_strjoin_e("PWD=", cwd);
	setenv_cmd(path, env);
	free(path);
	split = ft_strsplit_e(line, ' ');
	if (0 == builtin_cmd(line, split, env, cwd))
		;
	else if (0 == system_cmd(split, env, environ))
		;
	else if (0 == exe_cmd(split, cwd, environ))
		;
	else
		ft_printf("command not found: %s\n", line);
	free(cwd);
	ft_free_split(split);
	ft_free_split(environ);
}
