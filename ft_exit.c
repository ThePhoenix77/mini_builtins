#include "builtins.h"

int is_valid_number(char *str)
{
    if (*str == '\0') return 0;
    if (*str == '-' || *str == '+') str++;
    if (*str == '\0') return 0;
    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}

void ft_exit(t_global *global, t_lst *cmd)
{
    int exit_status;
    t_lst *current;

    exit_status = 0;
    current = cmd->next;
    if (!current)
        exit_status = global->exit_status;
    else
    {
        if (is_valid_number(current->content))
            exit_status = ft_atoi(current->content);
        else
        {
            ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
            exit_status = 1;
        }
    }
    exit(exit_status);
}

/*int exit(t_global *global, char **args)
{
    int status = 0;

    if (args[1] != NULL)
        status = ft_atoi(args[1]);
    ft_execve(ft_strjoin("exit ", ft_itoa(status)), global->env_list);
}*/
