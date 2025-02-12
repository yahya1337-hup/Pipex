#include "pipex.h"

// char **get_paths_cmds(char **env)
// {
//     int i;
//     char **path;
//     char	*temp;

//     i = 0;
//     path = NULL;
//     while (env[i])
//     {
//         if (ft_strncmp(env[i], "PATH=", 5) == 0)
//             break;
//         i++;
//     }
//     path = ft_split(env[i], ':');
//     if (path == NULL)
//         exit((perror("ft_split is falid "), 1));
//     temp = path[0];
//     path[0] = ft_strtrim(temp, "PATH=");
//     free(temp);
//     temp = NULL;
//     return path;
// }

char **get_paths_cmds(char **env)
{
    int i = 0;
    char **path = NULL;
    char *temp;

    while (env[i])
    {
        if (ft_strncmp(env[i], "PATH=", 5) == 0)
            break;
        i++;
    }
    if (!env[i]) // If "PATH=" is not found
        return NULL;

    temp = env[i] + 5; // Skip "PATH="
    path = ft_split(temp, ':'); 
    if (!path)
        exit((perror("ft_split failed"), 1));

    return path; // No need for ft_strtrim, as we already removed "PATH="
}


char **join_path_cmd(char **path, char *cmd)
{
    int i;
    char **new_path;
    char *join_cmd;

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

int check_path(char **path)
{
    int i;

    i = 0;
    while (path[i])
    {
        if (access(path[i], X_OK) == 0)
            return (i);
        i++;
    }
    return (0);
}

char    *get_path_cmd(char **env, char *cmd)
{
    char    **paths;
    char    **temp;
    int     i;
    char *temp1;

    if (ft_strchr(cmd, ' '))
    {
        temp = ft_split(cmd, ' ');
        paths = join_path_cmd( get_paths_cmds(env), temp[0]);
        free_mem(temp);
    } 
    else
        paths = join_path_cmd( get_paths_cmds(env), cmd);
    i = check_path(paths);
    temp1 = ft_strdup(paths[i]);
    free_mem(paths);
    return (temp1);
}
