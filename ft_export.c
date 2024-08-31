#include "builtins.h"

void export_without_args(t_global *global)
{
    t_env_list *tmp = global->env_list;
    while (tmp)
    {
        ft_putstr_fd("declare -x ", 2);
        ft_putstr_fd(tmp->content, 2);
        ft_putstr_fd("\n", 2);
        tmp = tmp->next;
    }
}

int is_valid_name_char(char c)
{
    return (ft_isalnum(c) || c == '_');
}

int name_checker(const char *s)
{
    int i;

    i = 0;
    if (!ft_isalpha(s[0]) && s[0] != '_')
        return (-1);
    while(s[i])
    {
        if (!is_valid_name_char(s[i]))
            return (-1);
        i++;
    }
    return (0);
}

t_env_list *find_var(t_env_list *env_list, char *key)
{
    size_t key_len;
    
    key_len = ft_strlen(key);
    while (env_list)
    {
        if (ft_strncmp(env_list->content, key, key_len) == 0 &&
            env_list->content[key_len] == '=')
            return (env_list);
        env_list = env_list->next;
    }
    return (NULL);
}

char *create_new_content(const char *key, const char *value)
{
    size_t total_len;
    char *new_content;
    
    total_len = ft_strlen(key) + ft_strlen(value) + 2;
    new_content = malloc(total_len);
    if (!new_content)
    {
        perror("malloc");
        return (NULL);
    }
    ft_strcpy(new_content, key);
    new_content[ft_strlen(key)] = '=';
    ft_strcpy(new_content + ft_strlen(key) + 1, value);
    return (new_content);
}

void update_env_var(t_env_list *env_var, char *new_content)
{
    free(env_var->content);
    env_var->content = new_content;
}

t_env_list *create_new_node(char *new_content, t_env_list *env_list)
{
    t_env_list *new_node;
    
    new_node = malloc(sizeof(t_env_list));
    if (!new_node)
    {
        perror("malloc");
        free(new_content);
        return (NULL);
    }
    new_node->content = new_content;
    new_node->next = env_list;
    new_node->prev = NULL;
    if (env_list)
        env_list->prev = new_node;
    return (new_node);
}

void add_or_update_env_var(t_global *global, const char *key, const char *value)
{
    t_env_list *env_var;
    
    env_var = find_var(global->env_list, key);
    char *new_content = create_new_content(key, value);
    if (!new_content)
        return;
    if (env_var)
        update_env_var(env_var, new_content);
    else
    {
        t_env_list *new_node = create_new_node(new_content, global->env_list);
        if (new_node)
            global->env_list = new_node;
    }
}
void handle_key_value(t_global *global, char *content)
{
    char *equal_sign;
    char *key;
    char *value;
    size_t key_length;

    equal_sign = ft_strchr(content, '=');
    if (equal_sign)
    {
        key_length = equal_sign - content;
        key = ft_strndup(content, key_length);
        value = ft_strdup(equal_sign + 1);
        if (key && value)
        {
            add_or_update_env_var(global, key, value);
            free(key);
            free(value);
        }
    }
    else
        ft_putstr_fd("export: Invalid format. Use VAR=value.\n", 2);
}

void process_export_cmd(t_global *global, t_lst *cmd)
{
    while (cmd)
    {
        if (cmd->type == WORD)
            handle_key_value(global, cmd->content);
        cmd = cmd->next;
    }
}

void ft_export(t_global *global, t_lst *cmd)
{
    if (!cmd->next)
        export_without_args(global);
    else if (name_checker(cmd->content) == -1)
        ft_putstr_fd("export: Invalid variable name.\n", 2);
    else
        process_export_cmd(global, cmd);
}


/*void ft_export(t_global *global, t_lst *cmd)
{
    size_t key_length;
    char *value;
    char *key;

    if (!cmd->next)
        export_without_args(global);
    else if (name_checker(cmd->content) == -1)
        printf("export: Invalid variable name !!!!\n");
    else
    {
        char *equal_sign;
        while (cmd)
        {
            if (cmd->type == WORD)
            {
                equal_sign = ft_strchr(cmd->content, '=');
                if (equal_sign)
                {
                    key_length = equal_sign - cmd->content;
                    key = ft_strndup(cmd->content, key_length);
                    value = ft_strdup(equal_sign + 1);
                    if (key && value)
                    {
                        add_or_update_env_var(global, key, value);
                        free(key);
                        free(value);
                    }
                }
                else
                    printf("export: Invalid format. Use VAR=value.\n");
            }
            cmd = cmd->next;
        }
    }
}*/
