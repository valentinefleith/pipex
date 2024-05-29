/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:43:31 by vafleith          #+#    #+#             */
/*   Updated: 2024/05/29 14:58:27 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define MALLOC_ERROR 1
# define ARGUMENT_ERROR 2

typedef struct s_files
{
	int		infile;
	int		outfile;
}			t_files;

typedef struct s_cmd
{
	char	*cmd_path;
	char	**cmd_args;
}			t_cmd;

void		create_child_process(char **argv, int *pipefd, char **env);
void		create_parent_process(char **argv, int *pipefd, char **env);
//int			check_args(char **argv);
char **get_paths(char **env);

#endif
