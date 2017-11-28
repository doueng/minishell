/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: douglas <douglas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 15:46:08 by douglas           #+#    #+#             */
/*   Updated: 2017/11/19 20:40:34 by douglas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void		*resize(void *memory, int *mem_size, int used_mem)
{
	void	*new_mem;

	new_mem = memory;
	if (used_mem >= *mem_size)
	{
		new_mem = ft_memalloc(*mem_size * 2);
		ft_memcpy(new_mem, memory, *mem_size);
		*mem_size *= 2;
		free(memory);
	}
	return (new_mem);
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

static char	**get_values(t_list *env, char *line)
{
	char	**values;
	int		size;
	int		i;

	size = 20; // increase
	values = (char**)ft_memalloc(sizeof(char*) * (size + 10)); // null
	i = 0;
	while (*line)
	{
		if (*line == '$')
			values[i++] = get_value(env, ++line, ' ');
		// values = resize(values, &size, i);
		line++;
	}
	// values[size] = NULL;
	return (values);
}

static char	*replace_variables(t_list *env, char *line)
{
	char	**values;
	int		len_vals;
	int		i;
	char	*new_line;
	char	*res;
	char	**tmp;

	values = get_values(env, line);
	tmp = values;
	i = 0;
	len_vals = 0;
	while (values[i])
		len_vals += ft_strlen(values[i++]);
	new_line = ft_strnew_e(len_vals + ft_strlen(line));
	res = new_line;
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && *values)
		{
			new_line = ft_strcat_end(new_line, *values);
			while (line[i] != ' ' && line[i])
				i++;
		}
		else
			*new_line++ = line[i++];
	}
	free(tmp);
	free(line);
	return (res);
}

static void	quote_remover(char *line)
{
	while (*line)
	{
		if (*line == '"')
			ft_memmove(line, line + 1, ft_strlen(line));
		if (*(line + 1) == '\0' && *line == '"')
			*line = '\0';
		else
			line++;
	}
}

void		replacer(t_list *env, char **split)
{
	while (*split)
	{
		if (*split[0] != '\'')
		{
			quote_remover(*split);
			*split = replace_all('~', *split, get_value(env, "HOME", '\0'));
			*split = replace_variables(env, *split);
		}
		split++;
	}
}