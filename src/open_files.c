/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:37:21 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/10 17:07:04 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_infile(char *filename, char **paths, int *pipefd)
{
	int	infile;

	infile = open(filename, O_RDONLY);
	if (infile != -1)
		return (infile);
	if (access(filename, F_OK) != 0)
		no_such_file(filename);
	else if (access(filename, R_OK) != 0)
		permission_denied(filename);
	if (paths)
		ft_free_tab(paths);
	close(pipefd[0]);
	close(pipefd[1]);
	exit(1);
}

int	open_outfile(char *filename, char **paths, int *pipefd)
{
	int	outfile;

	outfile = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (outfile != -1)
		return (outfile);
	if (access(filename, W_OK) != 0)
		permission_denied(filename);
	if (paths)
		ft_free_tab(paths);
	close(pipefd[0]);
	close(pipefd[1]);
	exit(1);
}
