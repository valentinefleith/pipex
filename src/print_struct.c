/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 09:49:54 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/01 10:25:20 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void print_cmds(t_cmds *cmds)
{
	ft_printf("COMMAND 1\n");
	ft_printf("%s\n", cmds->cmd1.path);
	ft_printf("%s\n", cmds->cmd1.cmd);
	if (!cmds->cmd1.args[0])
		ft_printf("Cette commande n'a pas d'options.\n");
	for (int i = 0; cmds->cmd1.args[i]; i++)
	{
		ft_printf("%s\n", cmds->cmd1.args[i]);
	}
	ft_printf("COMMAND 2\n");
	ft_printf("%s\n", cmds->cmd2.path);
	ft_printf("%s\n", cmds->cmd2.cmd);
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
