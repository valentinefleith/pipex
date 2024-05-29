/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:42:10 by vafleith          #+#    #+#             */
/*   Updated: 2024/05/29 10:58:38 by vafleith         ###   ########.fr       */
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

     

int main(int argc, char **argv, char **env)
{
	int pipefd[2];
	pid_t id;

	//if (argc != 5 || !check_args(argv))
	//	exit(1);
	if (pipe(pipefd) == -1)
		return (1);
	id = fork();
	if (id < 0)
		return (2);
	if (id == 0)
	{
		// child process (cmd1)
		//create_child_process(argv, pipefd, env);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execlp("ping", "ping", "-c", "5", "google.com", NULL);
	}
	int id2;
	id2 = fork();
	if (id2 < 0)
		return 3;
	if (id2 == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execlp("grep", "grep", "rtt", NULL);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(id, NULL, 0);
	waitpid(id2, NULL, 0);
	//Check the existence of infile and outfile
	//be sure to understand what > does when the file does not exist
	//Create the necessary pipe (or pipes)
	//Create a child process for each command
	//Wait for all the processes to end before writing to the outfile
}
