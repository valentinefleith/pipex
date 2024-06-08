/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 14:16:20 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/08 14:40:45 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int is_full_space(char *str)
{
	while (*str)
	{
		if (!ft_strchr(" \n\t\r\f\v", *str))
			return 0;
		str++;
	}
	return 1;
}

char	**get_paths(char **env)
{
	int	seeking;
	char **split_paths;

	seeking = -1;
	while (*env)
	{
		seeking = ft_strncmp(*env, "PATH", 4);
		if (!seeking)
			break ;
		env++;
	}
	if (seeking)
		//exit(127);
		return (NULL);
	split_paths = ft_split(*env + 5, ':');
	if (!split_paths)
		exit(MALLOC_ERROR);
	return (split_paths);
}
