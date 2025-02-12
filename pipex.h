#ifndef PIPEX_H
#define PIPEX_H

#include <fcntl.h>  // For open()
#include <unistd.h> // For access(), close()
#include <stdio.h>  // For perror()
#include <stdlib.h> // For exit()

typedef enum e_bool
{
    FALSE,
    TRUE
}           e_bool;

typedef enum e_which_file
{
    input,
    output
}              e_which_file;

int *creat_fd(char *input_file, char *output_file);
e_bool check_files_in_ou(char *file_name,  e_which_file file, e_bool print);
int open_fd(char *name, e_which_file file);

void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strdup(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strchr(const char *str, int c);
char	*ft_strjoin(char const *s1, char const *s2);
void	free_mem(char **arr);

char    *get_path_cmd(char **env, char *cmd);
int check_path(char **path);
char **join_path_cmd(char **path, char *cmd);


#endif
