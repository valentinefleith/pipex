/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:40:24 by vafleith          #+#    #+#             */
/*   Updated: 2024/06/09 19:36:12 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_path_no_env(char *cmd_name)
{
	if (access(cmd_name, F_OK) != 0)
	{
		if (ft_strchr(cmd_name, '/'))
			no_such_file(cmd_name);
		else
			cmd_not_found(cmd_name);
		return (NULL);
	}
	if (access(cmd_name, X_OK) != 0)
	{
		permission_denied(cmd_name);
		return (NULL);
	}
	return (ft_strdup(cmd_name));
}

static char	*get_path_env(char *cmd_name, char **paths)
{
	char	*cmd_attempt;
	char	*tmp;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		cmd_attempt = ft_strjoin(tmp, cmd_name);
		free(tmp);
		if (!cmd_attempt)
			return (NULL);
		if (access(cmd_attempt, F_OK) == 0)
		{
			if (access(cmd_attempt, X_OK) == 0)
				return (cmd_attempt);
			permission_denied(cmd_name);
		}
		free(cmd_attempt);
		i++;
	}
	return (get_path_no_env(cmd_name));
}

char	*find_right_path(char **paths, char **cmd, int *pipefd, int file)
{
	char	*right_path;

	if (!cmd[0])
	{
		ft_putendl_fd("bash: command not found", 2);
		right_path = NULL;
		ft_free_tab(cmd);
		free_close_and_exit(paths, pipefd, file, 127);
	}
	else if (ft_strchr(cmd[0], '/') || !paths)
		right_path = get_path_no_env(cmd[0]);
	else
		right_path = get_path_env(cmd[0], paths);
	if (!right_path)
	{
		if (cmd[0] && ft_strnstr(cmd[0], "./", 2) != 0)
		{
			ft_free_tab(cmd);
			free_close_and_exit(paths, pipefd, file, 126);
		}
		ft_free_tab(cmd);
		free_close_and_exit(paths, pipefd, file, 127);
	}
	return (right_path);
}

char	**get_paths(char **env)
{
	int		seeking;
	char	**split_paths;

	seeking = -1;
	while (*env)
	{
		seeking = ft_strncmp(*env, "PATH", 4);
		if (!seeking)
			break ;
		env++;
	}
	if (seeking)
		return (NULL);
	split_paths = ft_split(*env + 5, ':');
	if (!split_paths)
		exit(1);
	return (split_paths);
}
