/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:09:10 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/09 19:41:56 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	no_such_file(char *filename)
{
	ft_putstr_fd("bash: no such file or directory: ", 2);
	ft_putendl_fd(filename, 2);
}

void	cmd_not_found(char *cmd_name)
{
	ft_putstr_fd("bash: command not found: ", 2);
	ft_putendl_fd(cmd_name, 2);
}

void	permission_denied(char *name)
{
	ft_putstr_fd("bash: permission denied: ", 2);
	ft_putendl_fd(name, 2);
}
