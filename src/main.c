/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:49:50 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/09 19:40:51 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exec_cmd(char *cmd_path, char **cmd, char **env, char **paths)
{
	execve(cmd_path, cmd, env);
	ft_free_tab(cmd);
	free(cmd_path);
	if (paths)
		ft_free_tab(paths);
	exit(1);
}

static void	create_child2(char **argv, int *pipefd, char **env, char **paths)
{
	int		outfile;
	char	**cmd2;
	char	*cmd2_path;

	outfile = open_outfile(argv[4], paths, pipefd);
	cmd2 = ft_split(argv[3], ' ');
	if (!cmd2)
		free_close_and_exit(paths, pipefd, outfile, 1);
	cmd2_path = find_right_path(paths, cmd2, pipefd, outfile);
	dup2(pipefd[0], STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	close(outfile);
	exec_cmd(cmd2_path, cmd2, env, paths);
}

static void	create_child1(char **argv, int *pipefd, char **env, char **paths)
{
	int		infile;
	char	**cmd1;
	char	*cmd1_path;

	infile = open_infile(argv[1], paths, pipefd);
	cmd1 = ft_split(argv[2], ' ');
	if (!cmd1)
		free_close_and_exit(paths, pipefd, infile, 1);
	cmd1_path = find_right_path(paths, cmd1, pipefd, infile);
	dup2(infile, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	close(infile);
	exec_cmd(cmd1_path, cmd1, env, paths);
}

int	main(int argc, char **argv, char **env)
{
	int		pipefd[2];
	pid_t	pids[2];
	char	**paths;

	if (argc != 5)
		argument_error();
	if (pipe(pipefd) == -1)
		pipe_error();
	paths = get_paths(env);
	pids[0] = fork();
	if (pids[0] == -1)
		fork_error();
	if (pids[0] == 0)
		create_child1(argv, pipefd, env, paths);
	pids[1] = fork();
	if (pids[1] == -1)
		fork_error();
	if (pids[1] == 0)
		create_child2(argv, pipefd, env, paths);
	close(pipefd[0]);
	close(pipefd[1]);
	if (paths)
		ft_free_tab(paths);
	return (handle_exit(pids));
}
