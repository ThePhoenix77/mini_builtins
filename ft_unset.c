#include "builtins.h"

void remove_env_node(t_global *global, t_env_list *node)
{
    if (node->prev)
        node->prev->next = node->next;
    else
        global->env_list = node->next;
    if (node->next)
        node->next->prev = node->prev;
    free(node->content);
    free(node);
}

void ft_unset(t_global *global, t_lst *cmd)
{
    t_env_list *env_var;
    char *key;
    char *equal_sign;
    
    while (cmd)
    {
        if (cmd->type == WORD)
        {
            equal_sign = ft_strchr(cmd->content, '=');
            if (equal_sign)
            {
                size_t key_length = equal_sign - cmd->content;
                key = ft_strndup(cmd->content, key_length);
                if (key)
                {
                    env_var = find_var(global->env_list, key);
                    if (env_var)
                        remove_env_node(global, env_var);
                    free(key);
                }
            }
            else
                printf("unset: Invalid format. Use VAR.\n");
        }
        cmd = cmd->next;
    }

}

