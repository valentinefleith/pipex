/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:26:49 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/09 19:36:12 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_tab(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	free_close_and_exit(char **paths, int *pipefd, int file,
		int exit_status)
{
	if (paths)
		ft_free_tab(paths);
	close(pipefd[0]);
	close(pipefd[1]);
	close(file);
	exit(exit_status);
}
