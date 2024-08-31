#include "builtins.h"

size_t ft_strnlen(const char *s, size_t maxlen)
{
    size_t len;
    
    len = 0;
    while (len < maxlen && s[len] != '\0')
        ++len;
    return len;
}

char *ft_strncpy(char *dest, const char *src, size_t n)
{
    int i;

    i = 0;
    while (i < n && src[i] != '\0')
    {
        dest[i] = src[i];
        ++i;
    }
    while (i < n)
    {
        dest[i] = '\0';
        ++i;
    }
    return (dest);
}

char *ft_strndup(const char *s, size_t n)
{
    size_t len;
    char *dup;

    len = ft_strnlen(s, n);

    dup = (char *)malloc(len + 1);
    if (dup == NULL)
        return NULL;

    ft_strncpy(dup, s, len);
    dup[len] = '\0';
    return (dup);
}

t_env_list *get_var_env(t_global *global, char *var)
{
    t_env_list *tmp;
    int len;

    tmp = global->env_list;
    len = ft_strlen_un_char(var, '=') + 1;
    while (tmp)
    {
        if (ft_strncmp(var, tmp->content, len) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return (NULL);
}
