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

#include "testUhrzeit.h"

#ifndef EINGABE_UHRZEIT
#define EINGABE_UHRZEIT

int eingabeUhrzeit(unsigned int*, unsigned int*);

#endif /* !EINGABE_UHRZEIT */
