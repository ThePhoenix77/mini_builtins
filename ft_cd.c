#include "builtins.h"

void checker(void *ptr, char *msg)
{
    if (!ptr)
    {
        printf("%s", msg);
        return ;
    }
}

void update_pwd(t_global *global)
{
    char *cwd;
    char *old_pwd;
    
    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        perror("getcwd");
        return;
    }
    old_pwd = get_var_env(global, "PWD");
    if (old_pwd)
        add_or_update_env_var(global, "OLDPWD", old_pwd);
    add_or_update_env_var(global, "PWD", cwd);
    free(cwd);
}

void ft_cd(t_global *global, t_lst *cmd)
{
    char *old_p;
    char *new_p;
    char *home_p;
    t_env_list *home;

    old_p = NULL;
    new_p = NULL;
    if (cmd->next)
        new_p = cmd->next->content;
    else
    {
        home = get_var_env(global, "HOME");
        checker(&home, "cd: HOME not set\n");
        home_p = home->content + 5;
        new_p = home_p;
    }
    old_p = getcwd(NULL, 0);
    checker(&old_p, "getcwd has failed !\n");
    if (chdir(new_p) != 0)
    {
        printf("cd has failed !\n");
        free(old_p);
        return ;
    }
    else
    {
        free(old_p);
        return ;
    }
    update_pwd(global);
    free(old_p);
}

int main()
{
    t_global global = { NULL };
    t_lst cd_cmd;
    t_env_list *home_env;

    // Create a minimal environment list with HOME set
    home_env = malloc(sizeof(t_env_list));
    if (!home_env)
    {
        perror("malloc");
        return 1;
    }
    home_env->content = ft_strdup("HOME=/home/user");
    home_env->next = NULL;
    home_env->prev = NULL;
    global.env_list = home_env;

    // Test with no arguments (should use HOME)
    cd_cmd.content = NULL;
    cd_cmd.next = NULL;
    cd_cmd.prev = NULL;

    // Test changing directory to HOME
    printf("Testing cd without arguments...\n");
    ft_cd(&global, &cd_cmd);

    // Add or update PWD environment variable
    add_or_update_env_var(&global, "PWD", "/home/user");
    add_or_update_env_var(&global, "OLDPWD", "/home");

    // Test with explicit directory (assuming this directory exists)
    cd_cmd.content = "/tmp";
    printf("\nTesting cd with /tmp...\n");
    ft_cd(&global, &cd_cmd);

    // Clean up
    t_env_list *tmp;
    while (global.env_list)
    {
        tmp = global.env_list;
        global.env_list = global.env_list->next;
        free(tmp->content);
        free(tmp);
    }

    return 0;
}
/*void set_dir(char **env, const char *cwd, const char *owd)
{
    setenv("PWD", cwd, 1);
    setenv("OLDPWD", owd, 1);
}

int ft_cd(char **args, char **env) {
    char cwd[1024];
    char owd[1024];

    getcwd(owd, sizeof(owd));

    if (!args[1])
    {
        if (chdir(getenv("HOME")) != 0) {
            perror("cd");
            return 1;
        }
    }
    else
    {
        if (chdir(args[1]) != 0)
        {
            perror("cd");
            return 1;
        }
    }
    getcwd(cwd, sizeof(cwd));
    set_dir(env, cwd, owd);
    return 0;
}*/
