/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboumei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:30:40 by yaboumei          #+#    #+#             */
/*   Updated: 2025/02/13 14:30:43 by yaboumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <sys/wait.h>

void	create_child_pr(t_pipex *info, int file_fd, int *pipe_fd, char *av)
{
	char	**cmd;
	int		pid;

	if (av[0] == 0)
		return ;
	cmd = get_path(av);
	pid = fork();
	if (pid == -1)
		exit((perror("function fork is filed"), 1));
	if (pid == 0)
	{
		if (dup2(pipe_fd[file_fd], file_fd) == -1)
			exit((perror("function dup2 is filed"), 1));
		if (file_fd == 1)
			close(pipe_fd[STDIN_FILENO]);
		if ((access(info->path, X_OK) == 0))
		{
			if (execve(info->path, cmd, info->env) == -1)
				exit((ft_putstr_fd("execve failed ", 2), 1));
		}
	}
	if (ft_strchr(av, ' '))
		free_mem(cmd);
	else
		free(cmd);
}

int	call_child_pr(t_pipex *info, int *pipe_fd)
{
	int	i;
	int	status = 0;

	if ((access(info->path, X_OK) == 0) && info->fd[0] != 0)
		create_child_pr(info, STDOUT_FILENO, pipe_fd, info->av[2]);
	else if (info->fd[0] != 0)
		err_exit(info->av[2], ": command not found\n");
	free(info->path);
	close(pipe_fd[STDOUT_FILENO]);
	info->path = get_path_cmd(info->env, info->av[3]);
	if (!info->path || (access(info->path, F_OK) != 0))
		err_exit(info->av[3], ": command not found\n");
	else if ((access(info->av[4], W_OK)) == -1)
	{
		wait(NULL);
		free(info->path);
		free(info->fd);
		free(info);
		exit(1);
	}
	create_child_pr(info, STDIN_FILENO, pipe_fd, info->av[3]);
	close(pipe_fd[STDIN_FILENO]);
	free(info->path);
	free(info->fd);
	i = 0;
	while (i++ < 2)
		wait(&status);
	return (WEXITSTATUS(status));
}

int	pipex(char **av, char **env)
{
	t_pipex	*info;
	int		pipe_fd[2];
	int		status;

	info = malloc(sizeof(t_pipex));
	info->av = av;
	info->env = env;
	info->path = get_path_cmd(info->env, info->av[2]);
	info->fd = creat_fd(av[1], av[4]);
	dup2(info->fd[0], STDIN_FILENO);
	dup2(info->fd[1], STDOUT_FILENO);
	close(info->fd[0]);
	close(info->fd[1]);
	if (pipe(pipe_fd) == -1)
		exit((perror("pipe funtion is filed"), 1));
	status = call_child_pr(info, pipe_fd);
	free(info);
	return (status);
}

int	main(int ac, char **av, char **env)
{
	if (ac == 5)
		return (pipex(av, env));
	return (0);
}
