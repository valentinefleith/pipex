/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:07:11 by vafleith          #+#    #+#             */
/*   Updated: 2024/05/29 15:29:47 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **get_paths(char **env)
{
	while (ft_strncmp(*env, "PATH", 4))
		env++;
	return (ft_split(*env + 5, ':'));
}

static char *get_right_path(char **cmd_and_args, char **paths)
{
	char *command_attempt;

	while (paths)
	{
		command_attempt = ft_strjoin(*paths, cmd_and_args[0]);
		if (command_attempt == NULL)
			return NULL;
		if (can_access(command_attempt, cmd_and_args, paths))
			return (command_attempt);
		free(command_attempt);
		paths++;
	}
	return NULL;
}

t_cmd parse_command(char *arg, char **paths)
{
	t_cmd cmd;
	char **cmd_and_args;
	
	cmd_and_args = ft_split(arg, ' ');
	if (cmd_and_args == NULL)
	{
		cmd.path = NULL;
		cmd.args = NULL;
		return cmd;
	}
	cmd.path = get_right_path(cmd_and_args, paths);
	cmd.args = cmd_and_args++;
	//ft_free_split(cmd_and_args);
	//STILL TO BE FREED : PATH AND ARGS
	return cmd;
}
