# ifndef BUILTINS_H
#define BUILTINS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../libft/libft.h"
#include "../minishell.h"

size_t      ft_strnlen(const char *s, size_t maxlen);
char        *ft_strncpy(char *dest, const char *src, size_t n);
char        *ft_strndup(const char *s, size_t n);
t_env_list  *find_var(t_env_list *env_list, const char *key);
char        *create_new_content(const char *key, const char *value);
void        update_env_var(t_env_list *env_var, char *new_content);
void        add_or_update_env_var(t_global *global, const char *key, const char *value);
t_env_list  *get_var_env(t_global *global, char *var);
void        ft_cd(t_global *global, t_lst *cmd);
void        ft_echo(t_lst *cmd);
void        ft_env(t_global *global);
void        ft_exit(t_global *global, t_lst *cmd);
void        ft_export(t_global *global, t_lst *cmd);
void        ft_unset(t_global *global, t_lst *cmd);

#endif
