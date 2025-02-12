#include <stdio.h>
#include "pipex.h"
#include <sys/wait.h>
// #include "find_cmd.c"
// #include "check_input.c"
// #include "ft_split.c"
// #include "ft_strtrim.c"
// #include "help.c"
// #include "utils.c"
// #include "utils_2.c"


void create_child_pr(int file_fd, int *pipe_fd, char **env, char *av, char *path)
{
    char **cmd;
    int pid;

    if (ft_strchr(av, ' '))
        cmd = ft_split(av, ' ');
    else
    {
        cmd = malloc((2 * sizeof(char *)));
        (1) && (cmd[0] = av, cmd[1] = NULL);
    }
    pid = fork();
    if (pid == -1)
        exit((perror("function fork is filed"), 1));
    if (pid == 0)
    {
        if (dup2(pipe_fd[file_fd], file_fd) == -1)
            exit((perror("function dup2 is filed"), 1));
        if ((access(path, X_OK) == 0))
        {
            if (execve(path, cmd, env) == -1)
                exit((ft_putstr_fd("execve failed ", 2), 1));
        }
    }
    if (ft_strchr(av, ' '))
        free_mem(cmd);
    else
        free(cmd);
}

void call_child_pr(char **av, char **env, int *fd, int *pipe_fd)
{
    char *path;
    int i;

    path = get_path_cmd(env, av[2]);
    if ((access(path, X_OK) == 0) && fd[0] != 0)
        create_child_pr(STDOUT_FILENO, pipe_fd, env, av[2], path);
    else if (fd[0] != 0)
    {
        ft_putstr_fd(av[2], 2);
        ft_putstr_fd(": command not found\n", 2);
    }
    free(path);
    close(pipe_fd[STDOUT_FILENO]);
    path = get_path_cmd(env, av[3]);
    if (!path || (access(path, F_OK) != 0))
    {
        ft_putstr_fd(av[3], 2);
        ft_putstr_fd(": command not found\n", 2);
    }
    else
        create_child_pr(STDIN_FILENO, pipe_fd, env, av[3], path);
    free(path);
    i = 0;
    while (i++ < 2)
        wait(NULL);
}

void pipex(char **av, char **env)
{
    int pipe_fd[2];
    int *fd;

    fd = creat_fd(av[1], av[4]);
    dup2(fd[0], STDIN_FILENO);
    dup2(fd[1], STDOUT_FILENO);
    close(fd[0]);
    close(fd[1]);
    if (pipe(pipe_fd) == -1)
        exit((perror("pipe funtion is filed"), 1));
    call_child_pr(av, env, fd, pipe_fd);
    free(fd);
}

int main(int ac, char **av, char **env)
{
    if (ac == 5)
    {
        pipex(av, env);
    }
    return (0);
}
