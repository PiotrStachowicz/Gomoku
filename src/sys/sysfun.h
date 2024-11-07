#ifndef SYSFUN_HEADER
#define SYSFUN_HEADER

#include "stdio.h"

#define RESET "\033[0m"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"

void
sys_clear_terminal()
{
  printf("\033[2J\033[H");
  fflush(stdout);
}


#endif
