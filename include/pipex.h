/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:43:31 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/09 19:36:43 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

void	argument_error(void);
void	pipe_error(void);
void	fork_error(void);
void	no_such_file(char *filename);
void	cmd_not_found(char *cmd_name);
void	permission_denied(char *name);

void	ft_free_tab(char **strs);
void	free_close_and_exit(char **paths, int *pipefd, int file,
			int exit_status);

int		open_infile(char *filename, char **paths, int *pipefd);
int		open_outfile(char *filename, char **paths, int *pipefd);
char	*find_right_path(char **paths, char **cmd, int *pipefd, int file);
char	**get_paths(char **env);
int		handle_exit(pid_t *pids);

#endif
