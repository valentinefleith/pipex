/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:43:31 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/09 17:41:11 by vafleith         ###   ########.fr       */
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

void	argument_error(void);
void	pipe_error(void);
void	fork_error(void);
void no_such_file(char *filename);
void cmd_not_found(char *cmd_name);
void permission_denied(char *name);

void	ft_free_tab(char **strs);

int		open_infile(char *filename, char **paths, int *pipefd);
int		open_outfile(char *filename, char **paths, int *pipefd);
char	*find_right_path(char **paths, char **cmd, int *pipefd, int file);
char	**get_paths(char **env);

#endif
