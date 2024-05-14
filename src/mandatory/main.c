/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:42:10 by vafleith          #+#    #+#             */
/*   Updated: 2024/05/14 17:42:54 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    pipex()
{
    pid_t child;
    int fd1 = open(av[1], O_RDONLY);
    int fd2 = open(av[4], O_WRONLY);
    char *cmd1 = av[2];
    char *cmd2 = av[3];   
    int pipefd[2];

    pipe(pipefd);

    pid_t child1 = create_child_process(fd1, cmd1, pipefd[1]);
    pid_t child2 = create_child_process(pipefd[0], cmd2, fd2);

}

void create_child_process()
{
  pid_t pid;

  pid = fork();

  if (pid == 0)
      child_execution_cmd;

  
   return pid;
   
}

     

int main(int argc, char **argv)
{
	if (argc < 2)
		exit(1);
	ft_printf("%s", argv[1]);	
}
