#include "minishell.h"

static void first_range(int exit_status)
{
  if (exit_status == 1)
    printf("Hangup\n");
  else if (exit_status == 2)
    printf("\n");
  else if (exit_status == 3)
    printf("Quit (core dumped)\n");
  else if (exit_status == 4)
    printf("Illegal instruction (core dumped)\n");
  else if (exit_status == 5)
    printf("Trace/breakpoint trap (core dumped)\n");
  else if (exit_status == 6)
    printf("Aborted (core dumped)\n");
  else if (exit_status == 7)
    printf("Bus error (core dumped)\n");
  else if (exit_status == 8)
    printf("Floating point exception (core dumped)\n");
  else if (exit_status == 9)
    printf("Killed\n");
  else if (exit_status == 10)
    printf("User defined signal 1\n");
  else if (exit_status == 11)
    printf("Segmentation fault (core dumped)\n");
  else if (exit_status == 12)
    printf("User defined signal 2\n");
}

static void second_range(int exit_status)
{
  if (exit_status == 13)
    printf("Broken pipe\n");
  else if (exit_status == 15)
    printf("Alarm clock\n");
  else if (exit_status == 16)
    printf("Stack fault\n");
  else if (exit_status == 17)
    printf("Child exited\n");
  else if (exit_status == 18)
    printf("Continued\n");
  else if (exit_status == 19)
    printf("Stopped\n");
  else if (exit_status == 20 || exit_status == 21 || exit_status == 22)
    printf("Stopped\n");
  else if (exit_status == 24)
    printf("CPU time limit exceeded (core dumped)\n");
  else if (exit_status == 25)
    printf("File size limit exceeded (core dumped)\n");
  else if (exit_status == 26)
    printf("Virtual timer expired\n");
}

static void third_range(int exit_status)
{
  if (exit_status == 27)
    printf("Profiling timer expired\n");
  else if (exit_status == 29)
    printf("I/O possible\n");
  else if (exit_status == 30)
    printf("Power failure\n");
  else if (exit_status == 31)
    printf("Bad system call (core dumped)\n");
  else if(exit_status == 32 || exit_status == 33)
    printf("Unknown signal %d\n", exit_status);
  else if(exit_status >= 34 && exit_status <= 64)
      printf("Real-time signal %d\n", exit_status - 34);
}

void print_exit_signal_message(int exit_status)
{
  exit_status = exit_status - 128;
  first_range(exit_status);
  second_range(exit_status);
  third_range(exit_status);
}
