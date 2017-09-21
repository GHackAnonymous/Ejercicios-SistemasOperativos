//#include "functions01.h"
//#include <stdio.h>
//#include <string.h>

int main (int argc, char* argv [])
{
  char str01[32], str02[32];
  unsigned int  n1, n2;

  printf ("give me a natural number: ");
  gets (str01);
  sscanf(str01,"%u",&n1);
  printf ("give me a natural number: ");
  gets(str02);
  sscanf(str02,"%u",&n2);
  printf("lcm(%u,%u)=%u\n", n1, n2, lcm(n1,n2));
  printf("gcd(%u,%u)=%u\n", n1, n2, gcd(n1,n2));
  return 0;
}
