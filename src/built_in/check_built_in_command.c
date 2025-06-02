#include "minishell.h"

void check_built_in_command(char **env, char **cmd_and_args)
{ 
    if(are_they_equal(*cmd_and_args, "pwd"))
      pwd();
    else if(are_they_equal(*cmd_and_args, "env"))
      print_env(env);
    else if(are_they_equal(*cmd_and_args, "echo"))
      echo(cmd_and_args+1);
    // else if(are_they_equal(*cmd_and_args, "cd"))
    //   cd(env, cmd_and_args+1);
    // else if(are_they_equal(*cmd_and_args, "export"))
    //   export(env, cmd_and_args +1);
    // else if(are_they_equal(*cmd_and_args, "unset"))
    //   unset(env, cmd_and_args +1);

    printf("%s\n", "its a bult in");
}
