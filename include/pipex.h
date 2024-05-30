/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:43:31 by vafleith          #+#    #+#             */
/*   Updated: 2024/05/30 19:49:26 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>

# define MALLOC_ERROR 1
# define ARGUMENT_ERROR 2
# define FILE_ERROR 3

typedef struct s_files
{
	int		infile;
	int		outfile;
}			t_files;

typedef struct s_cmd
{
	char	*path;
	char *cmd;
	char	**args;
}			t_cmd;

typedef struct s_cmds
{
	t_cmd cmd1;
	t_cmd cmd2;
} t_cmds;

void create_child_process(t_files *files, t_cmds *cmds, int *pipefd);
void create_parent_process(t_files *files, t_cmds *cmds, int *pipefd);
//int			check_args(char **argv);
char **get_paths(char **env);
void ft_free_split(char **strs);
void parse_commands(t_cmds *cmds, char **argv, char **env);
void parse_files(t_files *files, char **argv);
void free_cmds(t_cmds *cmds);

#endif
