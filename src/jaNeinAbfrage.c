/**
 * It asks the user for a yes or no answer and returns the answer as an integer
 *
 * @param jnPointer Pointer to the variable that will be 1 is yes and 0 if no
 *
 * @return 0 for test okay and 1 for test gone wrong
 */

#include <stdio.h>

int jaNeinAbfrage(char* jnPointer) {
  char jnVar = 0;

  printf("[J/N] ");

  scanf("%c", &jnVar);
  while (getchar() != '\n')
    ;

  switch (jnVar) {
    case 74:
    case 106:
      *jnPointer = 'j';
      break;
    case 78:
    case 110:
      *jnPointer = 'n';
      break;
    default:
      return 1;
      break;
  }

  return 0;
}
