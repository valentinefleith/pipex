/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:09:10 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/09 13:17:48 by vafleith         ###   ########.fr       */
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
