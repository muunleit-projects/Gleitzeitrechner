#include<stdio.h>

int leseDatei(FILE* datei, unsigned int array[], int arrayLaenge) {
  for (int i = 0; i <= arrayLaenge; i++) {
    if ((array[i] = getc(datei)) < 0) {
      return -1;
    }
    // TODO: testZeit
  }
  return 0;
}