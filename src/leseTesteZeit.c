/**
 * It reads two unsigned integers from a file, tests them for validity, and if
 * they are valid, stores them in an array
 *
 * @param datei The file to read from
 * @param array The array to store the time in.
 *
 * @return The return value is 0 for okay and -1 any error
 */

#include <stdio.h>

#include "leseDatei.h"
#include "testZeit.h"

int leseTesteZeit(FILE* datei, unsigned int array[]) {
  unsigned int zeit[2] = {0};

  if ((leseDatei(datei, zeit, 2)) < 0) {
    return -1;  // return
  }

  if (testZeit(zeit[0], zeit[1]) < 0) {
    return -1;  // return
  }

  for (int i = 0; i < 2; i++) {
    array[i] = zeit[i];
  }

  return 0;
}