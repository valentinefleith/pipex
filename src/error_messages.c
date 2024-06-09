/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:09:10 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/09 17:41:12 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	argument_error(void)
{
	ft_putstr_fd("5 arguments required.\n", 2);
	exit(1);
}

void	pipe_error(void)
{
	ft_putstr_fd("pipe error.\n", 2);
	exit(1);
}

void	fork_error(void)
{
	ft_putstr_fd("fork error.\n", 2);
	exit(1);
}

void no_such_file(char *filename)
{
	ft_putstr_fd("bash: no such file or directory: ", 2);
	ft_putendl_fd(filename, 2);
}

void cmd_not_found(char *cmd_name)
{
	ft_putstr_fd("bash: command not found: ", 2);
	ft_putendl_fd(cmd_name, 2);
}

void permission_denied(char *name)
{
	ft_putstr_fd("bash: permission denied: ", 2);
	ft_putendl_fd(name, 2);
}
