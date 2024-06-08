/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 12:47:57 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/08 12:13:00 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process(t_files *files, t_cmds *cmds, int *pipefd, char **env)
{
	close(pipefd[0]);
	dup2(files->infile, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	close(files->infile);
	close(files->outfile);
	execve(cmds->cmd1.path, cmds->cmd1.args, env);
	ft_putstr_fd("bash: command not found: ", 2);
	ft_putendl_fd(cmds->cmd1.args[0], 2);
	exit(1);
}

void	parent_process(t_files *files, t_cmds *cmds, int *pipefd, char **env)
{
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	dup2(files->outfile, STDOUT_FILENO);
	close(pipefd[1]);
	close(files->infile);
	close(files->outfile);
	execve(cmds->cmd2.path, cmds->cmd2.args, env);
	ft_putstr_fd("bash: command not found: ", 2);
	ft_putendl_fd(cmds->cmd2.args[0], 2);
	exit(1);
}

void 	exec_cmd2_and_exit(t_files *files, t_cmds *cmds, char **env)
{
	dup2(files->outfile, STDOUT_FILENO);
	execve(cmds->cmd2.path, cmds->cmd2.args, env);
	ft_putstr_fd("bash: command not found: ", 2);
	ft_putendl_fd(cmds->cmd2.args[0], 2);
	exit(1);
}
