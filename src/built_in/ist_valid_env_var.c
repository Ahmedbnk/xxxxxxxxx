#include "minishell.h"

int is_it_key_value(char *str)
{
    if (!str || !*str)
        return 0;
        
    while(*str)
    {
        if(*str == '=')
            return 1;
        str++;
    }
    return 0;
}

int is_valid_var(char *str)
{
    int i;
    i = 0;
    
    if(!str || !*str)
    {
        print_error("export: `': not a valid identifier\n");
        return 0;
    }
    
    // First character must be a letter or underscore
    if(!ft_isalpha(str[0]) && str[0] != '_')
    {
        print_error("export: `%s': not a valid identifier\n", str);
        return 0;
    }
    
    while(str[i] && str[i] != '=')
    {
        if(!ft_isalnum(str[i]) && str[i] != '_')
        {
            print_error("export: `%s': not a valid identifier\n", str);
            return 0;
        }
        i++;
    }
    return 1;
}

int compare_env_var(char *var1, char *var2)
{
    int i ;
    i = 0;
    while((var1[i] ||  var2[i]) && var1[i] != '=' && var2[i] != '=')
    {
        if(var1[i] != var2[i])
            return 0;
        i++;
    }
    return 1;
}
