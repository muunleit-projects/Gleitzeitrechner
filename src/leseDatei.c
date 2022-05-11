/**
 * It reads a file and stores the contents in an array
 *
 * @param datei The file to read from.
 * @param array The array to write to.
 * @param arrayLaenge The length of the array.
 *
 * @return The return value is 0 for okay and -1 for unexpected EOF
 */

#include <stdio.h>

int leseDatei(FILE* datei, unsigned int array[], int arrayLaenge) {
  for (int i = 0; i < arrayLaenge; i++) {
    if ((int)(array[i] = getc(datei)) < 0) {
      return -1;
    }
  }

  return 0;
}