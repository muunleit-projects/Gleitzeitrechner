/**
 * It asks the user for a yes or no answer and returns the answer as an integer
 *
 * @param jnPointer Pointer to the variable that will be 1 is yes and 0 if no
 *
 * @return 0 for test okay and 1 for test gone wrong
 */

#include <stdio.h>

int jaNeinAbfrage() {
  char jaNein = 0;
  int returnVal = -1;

  printf("[J/N] ");

  scanf("%c", &jaNein);
  while (getchar() != '\n')
    ;

  switch (jaNein) {
    case 74:
    case 106:
      returnVal = 1;
      break;
    case 78:
    case 110:
      returnVal = 0;
      break;
    default:
      returnVal = -1;
      break;
  }

  return returnVal;
}
