/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:43:31 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/08 12:13:31 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

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
	char	**args;
}			t_cmd;

typedef struct s_cmds
{
	t_cmd	cmd1;
	t_cmd	cmd2;
}			t_cmds;

void		child_process(t_files *files, t_cmds *cmds, int *pipefd,
				char **env);
void		parent_process(t_files *files, t_cmds *cmds, int *pipefd,
				char **env);
void 	exec_cmd2_and_exit(t_files *files, t_cmds *cmds, char **env);
// int			check_args(char **argv);
char		**get_paths(char **env);
void		ft_free_split(char **strs);
void		parse_commands(t_cmds *cmds, char **argv, char **env);
void		parse_files(t_files *files, char **argv, t_cmds *cmds);
void		free_cmds(t_cmds *cmds);
void		print_cmds(t_cmds *cmds);
void		print_files(t_files *files);
void		free_and_exit(int error, t_cmds *cmds);
void		ft_cmd_not_found(char *cmd);
void		ft_file_not_found(char *filename);
char		*ft_permission_error(char *cmd);

#endif
