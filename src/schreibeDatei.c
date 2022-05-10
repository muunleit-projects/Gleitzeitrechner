#include <stdio.h>

int schreibeDatei(FILE* datei, unsigned int array[], int arrayLaenge) {
  for (int i = 0; i < arrayLaenge; i++) {
    if (putc(array[i], datei) < 0) {
      return -1;
    }
  }
  return 0;
}