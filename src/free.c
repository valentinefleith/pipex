/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:18:19 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/01 11:40:23 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void ft_free_split(char **strs)
{
	int i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void free_cmds(t_cmds *cmds)
{
	free(cmds->cmd1.path);
	ft_free_split(cmds->cmd1.args);
	free(cmds->cmd2.path);
	ft_free_split(cmds->cmd2.args);
}

void free_and_exit(int error, t_cmds *cmds)
{
	free_cmds(cmds);
	exit(error);
}
