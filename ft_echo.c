#include "builtins.h"

int starts_with(char *str, char *prefix)
{
    return ft_strncmp(str, prefix, ft_strlen(prefix)) == 0;
}

void ft_echo(t_lst *cmd)
{
    t_lst *current;
    int nl_flag;

    current = cmd;
    nl_flag = 0;
    // skip the nl
    if (current && starts_with(current->content, "-n") && ft_strlen(current->content) == 2)
    {
        nl_flag = 1;
        current = current->next;
    }
    while (current)
    {
        if (current->content)
        {
            ft_putstr_fd(current->content, STDOUT_FILENO);
            if (current->next)
                ft_putstr_fd(" ", STDOUT_FILENO);
        }
        current = current->next;
    }
    if (!nl_flag)
        ft_putstr_fd("\n", STDOUT_FILENO);
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
int main(void)
{
    // Create a list of test commands
    t_lst *cmd1 = new_lst_node("echo", WORD);
    t_lst *cmd2 = new_lst_node("Hello", WORD);
    t_lst *cmd3 = new_lst_node("world!", WORD);
    cmd1->next = cmd2;
    cmd2->prev = cmd1;
    cmd2->next = cmd3;
    cmd3->prev = cmd2;

    printf("Test 1: Normal echo\n");
    ft_echo(cmd1->next); // Should print "Hello world!\n"

    // Test with -n option
    t_lst *cmd4 = new_lst_node("echo", WORD);
    t_lst *cmd5 = new_lst_node("-n", WORD);
    t_lst *cmd6 = new_lst_node("Hello", WORD);
    t_lst *cmd7 = new_lst_node("world!", WORD);
    cmd4->next = cmd5;
    cmd5->prev = cmd4;
    cmd5->next = cmd6;
    cmd6->prev = cmd5;
    cmd6->next = cmd7;
    cmd7->prev = cmd6;

    printf("\nTest 2: Echo with -n\n");
    ft_echo(cmd4->next); // Should print "Hello world!"

    // Clean up
    t_lst *current = cmd1;
    t_lst *next;
    while (current)
    {
        next = current->next;
        free(current->content);
        free(current);
        current = next;
    }
}*/
