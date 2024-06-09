/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 19:30:36 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/09 19:31:03 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	find_right_exit_status(int *exit_status)
{
	if (WIFEXITED(*exit_status))
	{
		*exit_status = WEXITSTATUS(*exit_status);
		if (*exit_status == 141)
			*exit_status = 0;
	}
	else if (WIFSIGNALED(*exit_status))
	{
		*exit_status = 128 + WTERMSIG(*exit_status);
		if (*exit_status == 141)
			*exit_status = 0;
		if (*exit_status == 139)
			*exit_status = 126;
	}
}

int	handle_exit(pid_t *pids)
{
	int		exit_status1;
	int		exit_status2;
	pid_t	current_pid;
	int		status;

	exit_status1 = 0;
	exit_status2 = 0;
	status = 0;
	current_pid = waitpid(-1, &status, 0);
	while (current_pid > 0)
	{
		if (current_pid == pids[0])
			exit_status1 = status;
		else if (current_pid == pids[1])
			exit_status2 = status;
		current_pid = waitpid(-1, &status, 0);
	}
	find_right_exit_status(&exit_status1);
	find_right_exit_status(&exit_status2);
	return (exit_status2);
}
