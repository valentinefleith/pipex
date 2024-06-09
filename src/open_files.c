/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:37:21 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/09 14:42:51 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_infile(char *filename, char **paths)
{
	int	infile;

	infile = open(filename, O_RDONLY);
	if (infile != -1)
		return (infile);
	if (access(filename, F_OK) != 0)
	{
		ft_putstr_fd("bash: no such file or directory: ", 2);
		ft_putendl_fd(filename, 2);
	}
	else if (access(filename, R_OK) != 0)
	{
		ft_putstr_fd("bash: permission denied: ", 2);
		ft_putendl_fd(filename, 2);
	}
	if (paths)
		ft_free_tab(paths);
	exit(1);
}

int	open_outfile(char *filename, char **paths)
{
	int	outfile;

	outfile = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (outfile != -1)
		return (outfile);
	if (access(filename, W_OK) != 0)
	{
		ft_putstr_fd("bash: permission denined: ", 2);
		ft_putendl_fd(filename, 2);
	}
	if (paths)
		ft_free_tab(paths);
	exit(1);
}
