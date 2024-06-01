/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:42:10 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/01 11:23:22 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char **env)
{
	int pipefd[2];
	pid_t pid;
	t_files files;
	t_cmds cmds;

	if (argc != 5)
		exit(1);
	parse_commands(&cmds, argv, env);
	parse_files(&files, argv, &cmds);
	if (pipe(pipefd) == -1)
		free_and_exit(1, &cmds);
	pid = fork();
	if (pid == -1)
		free_and_exit(2, &cmds);
	if (pid == 0)
		child_process(&files, &cmds, pipefd, env);
	parent_process(&files, &cmds, pipefd, env);
	free_cmds(&cmds);
}
