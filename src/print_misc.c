/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 09:49:54 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/01 12:58:18 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void print_cmds(t_cmds *cmds)
{
	ft_printf("COMMAND 1\n");
	ft_printf("%s\n", cmds->cmd1.path);
	ft_printf("%s\n", cmds->cmd1.args[0]);
	if (!cmds->cmd1.args[0])
		ft_printf("Cette commande n'a pas d'options.\n");
	for (int i = 0; cmds->cmd1.args[i]; i++)
	{
		ft_printf("%s\n", cmds->cmd1.args[i]);
	}
	ft_printf("COMMAND 2\n");
	ft_printf("%s\n", cmds->cmd2.path);
	ft_printf("%s\n", cmds->cmd2.args[0]);
	for (int i = 0; cmds->cmd2.args[i]; i++)
	{
		ft_printf("%s\n", cmds->cmd2.args[i]);
	}
}

void print_files(t_files *files)
{
	ft_printf("INFILE:\n %i\n", files->infile);
	ft_printf("OUTFILE:\n %i\n", files->outfile);
}

void ft_cmd_not_found(char *cmd)
{
	ft_putstr_fd("bash: command not found: ", 2);
	ft_putendl_fd(cmd, 2);
}

void ft_file_not_found(char *filename)
{
	ft_putstr_fd("bash: no such file or directory: ", 2);
	ft_putendl_fd(filename, 2);
}

char *ft_permission_error(char *cmd)
{
	ft_putstr_fd("bash: permission denied: ", 2);
	ft_putendl_fd(cmd, 2);
	return NULL;
}
