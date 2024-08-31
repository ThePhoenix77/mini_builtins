#include "builtins.h"

int ft_pwd()
{
    /*if (argc > 1 && args[1][1] != 'L' && args[1][1] != 'P')
    {
        printf("bash: pwd: -%c: invalid option\n", args[1][1]);
        return (-1);
    }*/
    char *cwd;

    cwd = getcwd(NULL, 0);
    if (cwd == NULL)
    {
        perror("getcwd");
        return (-1);
    }
    printf("%s\n", cwd);
    free(cwd);
    return 0;
}
