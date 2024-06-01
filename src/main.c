/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:42:10 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/01 10:39:12 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//void    pipex()
//{
//    pid_t child;
//    int fd1 = open(av[1], O_RDONLY);
//    int fd2 = open(av[4], O_WRONLY);
//    char *cmd1 = av[2];
//    char *cmd2 = av[3];   
//    int pipefd[2];
//
//    pipe(pipefd);
//
//    pid_t child1 = create_child_process(fd1, cmd1, pipefd[1]);
//    pid_t child2 = create_child_process(pipefd[0], cmd2, fd2);
//
//}

void create_child_process(t_files *files, t_cmds *cmds, int *pipefd)
{
	dup2(files->infile, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	execlp("ping", "ping", "-c", "5", "google.com", NULL);
}

void create_parent_process(t_files *files, t_cmds *cmds, int *pipefd)
{
	return;
}
     

int main(int argc, char **argv, char **env)
{
	int pipefd[2];
	pid_t pid;
	t_files files;
	t_cmds cmds;

	if (argc != 5)
		exit(1);
	parse_commands(&cmds, argv, env);
	print_cmds(&cmds);
	parse_files(&files, argv, &cmds);
	print_files(&files);
	free_cmds(&cmds);
	//if (pipe(pipefd) == -1)
	//	return (1);
	//pid = fork();
	//if (pid < 0)
	//	return (2);
	//if (pid == 0)
	//{
	//	// child process (cmd1)
	//	create_child_process(argv, pipefd, env);
	//}
	//create_parent_process(argv, pipefd, env);





	//int pid2;
	//pid2 = fork();
	//if (pid2 < 0)
	//	return 3;
	//if (pid2 == 0)
	//{
	//	dup2(pipefd[0], STDIN_FILENO);
	//	close(pipefd[0]);
	//	close(pipefd[1]);
	//	execlp("grep", "grep", "rtt", NULL);
	//}
	//close(pipefd[0]);
	//close(pipefd[1]);
	//waitpid(pid1, NULL, 0);
	//waitpid(pid2, NULL, 0);
	//Check the existence of infile and outfile
	//be sure to understand what > does when the file does not exist
	//Create the necessary pipe (or pipes)
	//Create a child process for each command
	//Wait for all the processes to end before writing to the outfile
}
