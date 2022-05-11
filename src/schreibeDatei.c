#include <stdio.h>

int schreibeDatei(FILE* datei, unsigned int array[], int arrayLaenge) {
  for (int i = 0; i < arrayLaenge; i++) {
    if ((int)putc(array[i], datei) < 0) {
      return -1;
    }
  }

  return 0;
}