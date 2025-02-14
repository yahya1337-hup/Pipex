/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboumei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:31:03 by yaboumei          #+#    #+#             */
/*   Updated: 2025/02/13 14:31:05 by yaboumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_paths_cmds(char **env)
{
	int		i;
	char	**path;
	char	*temp;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (!env[i])
		return (NULL);
	temp = env[i] + 5;
	path = ft_split(temp, ':');
	if (!path)
		exit((perror("ft_split failed"), 1));
	return (path);
}

char	**join_path_cmd(char **path, char *cmd)
{
	int		i;
	char	**new_path;
	char	*join_cmd;

	join_cmd = ft_strjoin("/", cmd);
	i = 0;
	while (path[i])
		i++;
	new_path = (char **)malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (path[i])
	{
		new_path[i] = ft_strjoin(path[i], join_cmd);
		i++;
	}
	new_path[i] = NULL;
	free(join_cmd);
	free_mem(path);
	return (new_path);
}

int	check_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if (access(path[i], X_OK) == 0)
			return (i);
		i++;
	}
	return (0);
}

char	*get_path_cmd(char **env, char *cmd)
{
	char	**paths;
	char	**temp;
	int		i;
	char	*temp1;

	if (ft_strchr(cmd, ' '))
	{
		temp = ft_split(cmd, ' ');
		paths = join_path_cmd(get_paths_cmds(env), temp[0]);
		free_mem(temp);
	}
	else
		paths = join_path_cmd(get_paths_cmds(env), cmd);
	i = check_path(paths);
	temp1 = ft_strdup(paths[i]);
	free_mem(paths);
	return (temp1);
}
