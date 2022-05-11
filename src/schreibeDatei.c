/**
 * It writes an array of unsigned ints to a file
 *
 * @param datei The file to write to.
 * @param array The array to write to the file.
 * @param arrayLaenge The length of the array.
 *
 * @return The return value is 0 for okay and -1 for write-error
 */

#include <stdio.h>

int schreibeDatei(FILE* datei, unsigned int array[], int arrayLaenge) {
  for (int i = 0; i < arrayLaenge; i++) {
    if ((int)putc(array[i], datei) < 0) {
      return -1;
    }
  }

  return 0;
}