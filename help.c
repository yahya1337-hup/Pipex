/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboumei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:30:52 by yaboumei          #+#    #+#             */
/*   Updated: 2025/02/13 14:30:55 by yaboumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_mem(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}



void	err_exit(char *file, char *messag)
{
	ft_putstr_fd(file, 2);
	ft_putstr_fd(messag, 2);
}

char	**get_path(char *av)
{
	char	**cmd;

	if (ft_strchr(av, ' '))
		cmd = ft_split(av, ' ');
	else
	{
		cmd = malloc((2 * sizeof(char *)));
		(1) && (cmd[0] = av, cmd[1] = NULL);
	}
	return (cmd);
}
