/**
 * It reads two unsigned integers from stdin, separated by a colon, and stores
 * them in the variables pointed to by the two parameters
 *
 * @param stundenPointer Pointer to the where the hours variable
 * @param minutenPointer Pointer to the minutes variable
 *
 * @return 0 for test on input was okay and 1 for test gone wrong
 */

#include <stdio.h>

#include "testZeit.h"

int eingabeZeit(unsigned int* stundenPointer, unsigned int* minutenPointer) {
  unsigned int stundenEingabe = 0;
  unsigned int minutenEingabe = 0;

  printf("[HH:MM] ");
  scanf("%2u:%2u", &stundenEingabe, &minutenEingabe);
  /* Reading the newline character from the input buffer. */
  while (getchar() != '\n')
    ;

  /* Checking if the input is valid. */
  if (testZeit(stundenEingabe, minutenEingabe) != 0) return 1;

  *stundenPointer = stundenEingabe;
  *minutenPointer = minutenEingabe;

  return 0;
}