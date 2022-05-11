#include <stdio.h>

int leseDatei(FILE* datei, unsigned int array[], int arrayLaenge) {
  for (int i = 0; i < arrayLaenge; i++) {
    if ((int)(array[i] = getc(datei)) < 0) {
      return -1;
    }
  }

  return 0;
}