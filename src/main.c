/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:49:50 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/09 16:51:41 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"



static void	handle_exit_status1(int *exit_status1)
{
	if (WIFEXITED(*exit_status1))
	{
		*exit_status1 = WEXITSTATUS(*exit_status1);
		if (*exit_status1 == 141)
			*exit_status1 = 0;
		// if (shell->input == -1 && shell->output != -1)
		// 	*exit_status1 = 0;
	}
	else if (WIFSIGNALED(*exit_status1))
	{
		*exit_status1 = 128 + WTERMSIG(*exit_status1);
		if (*exit_status1 == 141)
			*exit_status1 = 0;
		// if (shell->input== -1 && shell->output != -1)
		// 	*exit_status1 = 0;
	}
}

static void	handle_exit_status2(int *exit_status2)
{
	if (WIFEXITED(*exit_status2))
	{
		*exit_status2 = WEXITSTATUS(*exit_status2);
		if (*exit_status2 == 141)
			*exit_status2 = 0;
		// if (shell->input == -1 && shell->output != -1)
		// 	*exit_status2 = 0;
	}
	else if (WIFSIGNALED(*exit_status2))
	{
		// printf("before exit_status2: %d", *exit_status2);
		*exit_status2 = 128 + WTERMSIG(*exit_status2);
		if (*exit_status2 == 141)
			*exit_status2 = 0;
		if (*exit_status2 == 139)
			*exit_status2 = 126;
		// if (shell->input == -1 && shell->output != -1)
		// 	*exit_status2 = 0;
		// printf("after exit_status2: %d", *exit_status2);
	}
}

void handle_exit(int *exit_status1, int *exit_status2, pid_t pid1,  pid_t pid2) 
{
	pid_t current_pid = 0;
	int	status = 0;
	
	current_pid = waitpid(-1, &status, 0);
    while (current_pid > 0) 
	{
        if (current_pid == pid1) 
		{
            *exit_status1 = status;
        } 
		else if (current_pid == pid2) 
		{
            *exit_status2 = status;
        }
        current_pid = waitpid(-1, &status, 0);
    }

    handle_exit_status1(exit_status1);
    handle_exit_status2(exit_status2);
    // restore_terminal(shell);
}

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
	{
		ft_free_tab(paths);
		close(pipefd[1]);
		close(pipefd[0]);
		close(outfile);
		exit(1);
	}
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
	{
		ft_free_tab(paths);
		close(pipefd[0]);
		close(pipefd[1]);
		close(infile);
		exit(1);
	}
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
	int exit_status1 = 0;
	int exit_status2 = 0;
	// int status= 0;

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
	// waitpid(pid[0], &status,)
	pids[1] = fork();
	if (pids[1] == -1)
		fork_error();
	if (pids[1] == 0)
		create_child2(argv, pipefd, env, paths);
	close(pipefd[0]);
	close(pipefd[1]);
	// waitpid(pids[0], NULL, 0);
	// waitpid(pids[1], NULL, 0);
	handle_exit(&exit_status1, &exit_status2, pids[0], pids[1]);
	//fprintf(stderr, "exit_status1: %d", exit_status1);
	//fprintf(stderr, "exit_status2: %d", exit_status2);
	if (paths)
		ft_free_tab(paths);
	return exit_status2;
}
