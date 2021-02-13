#include <iostream>
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* system, NULL, EXIT_FAILURE */

int main ()
{
  int i;
  printf ("Checking if processor is available...");
  if (system(NULL)) puts ("Ok");
    else exit (EXIT_FAILURE);
  printf ("Executing command DIR...\n");
  i=system ("./createPlotCmd.sh /var/SaunaPiData/2020/Dec/2020-Dec-30.dat /var/SaunaPiData/2020/Dec/2020-Dec-30.png");
  printf ("The value returned was: %d.\n",i);

  i=system ("ln -s -f plot.png symPLot.png");
  printf("The symlink returned value: %d.\n", i);
  return 0;
}
