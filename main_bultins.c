#include "builtins.h"

void check_builtins(t_global *global, t_lst *cmd)
{
    int cmd_len;

    cmd_len = ft_strlen(cmd->content);
    if (ft_strncmp("export", cmd->content, cmd_len) == 0)
        ft_export(global, cmd);
    else if (ft_strncmp("echo", cmd->content, cmd_len) == 0)
        ft_echo(global);
    else if (ft_strncmp("cd", cmd->content, cmd_len) == 0)
        ft_cd(global, cmd);
    else if (ft_strncmp("exit", cmd->content, cmd_len) == 0)
        ft_exit(global, cmd);
    else if (ft_strncmp("unset", cmd->content, cmd_len) == 0)
        ft_unset(global, cmd);
    else if (ft_strncmp("env", cmd->content, cmd_len) == 0)
        ft_env(global);
    else if (ft_strncmp("pwd", cmd->content, cmd_len) == 0)
        ft_pwd(global, cmd);
    else
        printf("Unknown cmd: %s\n", cmd->content);
}
