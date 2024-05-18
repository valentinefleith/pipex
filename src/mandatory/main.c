/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:42:10 by vafleith          #+#    #+#             */
/*   Updated: 2024/05/18 23:55:48 by vafleith         ###   ########.fr       */
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

#include <stdio.h>

void create_child_process(char **argv, int *pipefd, char **env)
{
	(void)argv;
	(void)env;
	close(pipefd[1]);
	int y;
	read(pipefd[0], &y, sizeof(int));
	close(pipefd[0]);
	printf("Got from child process %d\n", y);
}

void create_parent_process(char **argv, int *pipefd, char **env)
{
	(void)argv;
	(void)env;
	close(pipefd[0]);
	int x;
	printf("Input a number: ");
	scanf("%d", &x);
	write(pipefd[1], &x, sizeof(int));
	close(pipefd[1]);
}
     

int main(int argc, char **argv, char **env)
{
	int pipefd[2];
	pid_t id;

	//if (argc != 5)
	//	exit(1);
	if (pipe(pipefd) == -1)
		exit(-1);
	id = fork();
	if (id == 0)
		create_child_process(argv, pipefd, env);
	else
		create_parent_process(argv, pipefd, env);
}
