/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:07:11 by vafleith          #+#    #+#             */
/*   Updated: 2024/05/30 00:22:32 by vafleith         ###   ########.fr       */
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
		if (access(command_attempt, F_OK | X_OK) == 0)
			return (command_attempt);
		free(command_attempt);
		paths++;
	}
	return NULL;
}

static t_cmd parse_unique_command(char *arg, char **paths)
{
	t_cmd cmd;
	char **cmd_and_args;
	
	cmd_and_args = ft_split(arg, ' ');
	if (cmd_and_args == NULL)
	{
		cmd.cmd = NULL;
		cmd.path = NULL;
		cmd.args = NULL;
		return cmd;
	} // essayer bzero ici ?
	cmd.path = get_right_path(cmd_and_args, paths);
	cmd.cmd = *cmd_and_args;
	cmd.args = cmd_and_args++;
	//ft_free_split(cmd_and_args);
	//STILL TO BE FREED : PATH AND ARGS
	return cmd;
}

void parse_commands(t_cmds *cmds, char **argv, char **env)
{
	t_cmd cmd1;
	t_cmd cmd2;
	t_cmds cmds;
	char **paths;

	paths = get_paths(env);
	if (!paths)
		exit(MALLOC_ERROR);
	cmd1 = parse_unique_command(argv[2], paths);
	cmd2 = parse_unique_command(argv[3], paths);
	ft_free_split(paths);
	if (!cmd1.path || !cmd2.path)
		exit(MALLOC_ERROR); // ICI IL FAUDRA FREE MIEUX JE PENSE
	cmds->cmd1 = cmd1;
	cmds->cmd2 = cmd2;
}

void parse_files(t_files *files, char **argv)
{
	files->infile = open(argv[1], O_RDONLY);
	files->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC); // un arg en plus ?
	if (files->infile < 0 || files->outfile < 0)
		free_and_exit(FILE_ERROR);
}