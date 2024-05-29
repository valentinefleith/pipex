/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:07:11 by vafleith          #+#    #+#             */
/*   Updated: 2024/05/29 15:47:54 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **get_paths(char **env)
{
	while (ft_strncmp(*env, "PATH", 4))
		env++;
	return (ft_split(*env + 5, ':'));
}

static int can_access(char *cmd_attempt, char **cmd_and_args, char **paths)
{
	if (access(cmd_attempt, F_OK) == -1)
		return 0;
	if (access(cmd_attempt, X_OK) == -1)
		free_and_exit(cmd_attempt, cmd_and_args, paths);
	return 1;
}

static char *get_right_path(char **cmd_and_args, char **paths)
{
	char *command_attempt;
	char *temp;

	while (paths)
	{
		temp = ft_strjoin(*paths, "/");
		if (temp == NULL)
			return NULL;
		command_attempt = ft_strjoin(temp, cmd_and_args[0]);
		free(temp);
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
