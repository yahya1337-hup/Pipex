/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaboumei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:32:30 by yaboumei          #+#    #+#             */
/*   Updated: 2025/02/13 14:32:33 by yaboumei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_bool
{
	FALSE,
	TRUE
}			t_bool;

typedef enum e_which_file
{
	input,
	output
}			t_which_file;

typedef struct t_pipex
{
	int		*fd;
	char	**env;
	char	**av;
	char	*path;
}			t_pipex;

int			*creat_fd(char *input_file, char *output_file);
t_bool		check_files_in_ou(char *file_name, t_which_file file, t_bool print);
int			open_fd(char *name, t_which_file file);

void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
size_t		ft_strlen(const char *str);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
char		*ft_strdup(const char *str);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		**ft_split(char const *s, char c);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strchr(const char *str, int c);
char		*ft_strjoin(char const *s1, char const *s2);
void		free_mem(char **arr);

void	free_after_exc(t_pipex *strc, char *av, char *cmd, int fd);
void		free_struct(t_pipex *strc);
void		err_exit(char *file, char *messag);
char		**get_path(char *av);
char		*get_path_cmd(char **env, char *cmd);
int			check_path(char **path);
char		**join_path_cmd(char **path, char *cmd);

#endif
