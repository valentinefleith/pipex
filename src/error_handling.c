/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 21:09:22 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/07 21:09:49 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_cmd_not_found(char *cmd)
{
	ft_putstr_fd("bash: command not found: ", 2);
	ft_putendl_fd(cmd, 2);
}

void	ft_file_not_found(char *filename)
{
	ft_putstr_fd("bash: no such file or directory: ", 2);
	ft_putendl_fd(filename, 2);
}

char	*ft_permission_error(char *cmd)
{
	ft_putstr_fd("bash: permission denied: ", 2);
	ft_putendl_fd(cmd, 2);
	return (NULL);
}
