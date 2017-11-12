/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dengstra <dengstra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/14 20:29:58 by douglas           #+#    #+#             */
/*   Updated: 2017/08/06 13:23:00 by dengstra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include "libft/libft.h"
# include <unistd.h>
# include <sys/wait.h>
# include <locale.h>
# include <dirent.h>

typedef struct	s_env
{
	char		*key;
	char		*value;
}				t_env;

int				start_program(char *cmd_path, char **cmd, char **environ);
void			do_all_cmds(char *line, t_list *env);
int				system_cmd(char **split, t_list *env, char **environ);
void			ft_error(char *message);
void			ft_usage(void);
void			lst_delete_one(void *content, size_t size);
void			lst_del_node(void *content, size_t size);
int				lst_cmp(void *env, void *find);
t_list			*find_node(t_list *node, char *key, char till);
t_list			*env_to_lst(char **environ);
void			new_env_node(char *new, t_list **start);
void			env_cmd(t_list *env);
void			setenv_cmd(char *line, t_list *env);
void			unsetenv_cmd(char *key, t_list **env);
void			do_cmds(char *line, t_list *env);
int				builtin_cmd(char *line, char **split,
								t_list *env, char *cwd);
char			*get_value(t_list *node, char *key, char till);
int				contains_alnum(char *str);
int				ft_cmp_till(char *a, char *b, char till);
char			*ft_strjoinfree_e(int free_a, char *a, int free_b, char *b);
char			**ft_strsplit_e(char *src, char c);
char			*ft_strdup_e(char *src);
char			*ft_strjoin_e(char *a, char *b);
int				ft_strcpytill_in(char *dst, char *src, char c);
char			*ft_strcat_end(char *dest, char *src);
int				ft_count_chars(char *str, char c);
size_t			ft_lst_len(t_list *lst);
void			*ft_malloc_e(size_t size);
#endif
