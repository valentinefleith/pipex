/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:07:11 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/08 16:39:39 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_right_path(char **cmd_and_args, char **paths)
{
	char	*command_attempt;
	char	*temp;
	int		i;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		if (temp == NULL)
			return (NULL);
		command_attempt = ft_strjoin(temp, cmd_and_args[0]);
		free(temp);
		if (command_attempt == NULL)
			return (NULL);
		if (access(command_attempt, F_OK) == 0)
		{
			if (access(command_attempt, X_OK) != 0)
				return (ft_permission_error(cmd_and_args[0]));
			return (command_attempt);
		}
		free(command_attempt);
		i++;
	}
	//ft_cmd_not_found(cmd_and_args[0]);
	return (NULL);
}

static char *handle_entire_path(char *cmd_path)
{
	if (access(cmd_path, F_OK) != 0)
	{
		if (ft_strchr(cmd_path, '/'))
			ft_file_not_found(cmd_path);
		return (NULL);
	}
	if (access(cmd_path, X_OK) != 0)
		return (ft_permission_error(cmd_path));
	return (cmd_path);
}

static t_cmd	parse_unique_command(char *arg, char **paths)
{
	t_cmd	cmd;
	char	**cmd_and_args;
	
	if (is_full_space(arg))
	{
		cmd.path = NULL;
		cmd.args = NULL;
		return cmd;
	}
	cmd_and_args = ft_split(arg, ' ');
	if (cmd_and_args == NULL)
	{
		if (paths)
			ft_free_split(paths);
		exit(MALLOC_ERROR);
	}
	if (ft_strchr(cmd_and_args[0], '/') || !paths)
		cmd.path = handle_entire_path(cmd_and_args[0]);
	else 
		cmd.path = get_right_path(cmd_and_args, paths);
	cmd.args = cmd_and_args;
	return (cmd);
}

void	parse_commands(t_cmds *cmds, char **argv, char **env)
{
	t_cmd	cmd1;
	t_cmd	cmd2;
	char	**paths;

	paths = get_paths(env);
	
	//if (!paths)
	//	exit(MALLOC_ERROR);
	cmd1 = parse_unique_command(argv[2], paths);
	if (!cmd1.path)
		ft_cmd_not_found(argv[2]);
	cmd2 = parse_unique_command(argv[3], paths);
	if (paths)
		ft_free_split(paths);
	if (!cmd2.path)
	{
		if (cmd1.path)
			free(cmd1.path);
		if (cmd1.args)
			ft_free_split(cmd1.args);
		ft_cmd_not_found(argv[3]);
		exit(127);
	}
	cmds->cmd1 = cmd1;
	cmds->cmd2 = cmd2;
}

void	parse_files(t_files *files, char **argv, t_cmds *cmds)
{
	files->infile = open(argv[1], O_RDONLY, 0777);
	if (files->infile < 0)
	{
		if (access(argv[1], F_OK) != 0)
			ft_file_not_found(argv[1]);
		if (access(argv[1], R_OK) != 0)
		{
			ft_putstr_fd("bash: permission denied: ", 2);
			ft_putendl_fd(argv[1], 2);
		}
	}
	files->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (files->outfile < 0)
	{
		ft_file_not_found(argv[4]);
		free_and_exit(FILE_ERROR, cmds);
	}
}
