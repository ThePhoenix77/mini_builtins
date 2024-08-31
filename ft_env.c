#include "builtins.h"

void ft_env(t_global *global)
{
    t_env_list *current;
    
    current = global->env_list;
    while (current)
    {
        ft_putstr_fd(current->content, STDOUT_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
        current = current->next;
    }
}

/*t_lst *new_lst_node(const char *content, t_type type)
{
    t_lst *node = malloc(sizeof(t_lst));
    if (!node)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    node->content = ft_strdup(content);
    node->next = NULL;
    node->prev = NULL;
    node->state = GENERAL;
    node->type = type;
    node->len = ft_strlen(content);
    return node;
}
int main()
{

}*/
