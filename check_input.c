/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboumei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:31:14 by yaboumei          #+#    #+#             */
/*   Updated: 2025/02/13 14:31:19 by yaboumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_bool	check_files_in_ou(char *file_name, t_which_file file, t_bool print)
{
	if (file == input)
	{
		if (access(file_name, R_OK) != 0)
		{
			if (print == TRUE)
			{
				ft_putstr_fd("pipex : ", 2);
				perror(file_name);
			}
			return (FALSE);
		}
	}
	else if (file == output)
	{
		if (access(file_name, W_OK) != 0)
		{
			if (print == TRUE)
			{
				ft_putstr_fd("pipex : ", 2);
				perror(file_name);
			}
			return (FALSE);
		}
	}
	return (TRUE);
}

int	open_fd(char *name, t_which_file file)
{
	int	fd;

	if (file == input)
		fd = open(name, O_RDONLY);
	else
		fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		perror("Error opening file");
	return (fd);
}

int	*creat_fd(char *input_file, char *output_file)
{
	int	*fd;

	fd = malloc(2 * sizeof(int));
	if (fd == NULL)
		exit((perror("Memory allocation failed"), 1));
	fd[0] = 0;
	fd[1] = 1;
	if (check_files_in_ou(input_file, input, TRUE))
		fd[0] = open_fd(input_file, input);
	if (check_files_in_ou(output_file, output, FALSE))
		fd[1] = open_fd(output_file, output);
	else
		fd[1] = open_fd(output_file, output);
	return (fd);
}
