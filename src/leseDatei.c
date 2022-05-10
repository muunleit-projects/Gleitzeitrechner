#include <stdio.h>

int leseDatei(FILE* datei, unsigned int array[], int arrayLaenge) {
  /* int versuch;
  for (int i = 0; i < arrayLaenge; i++) {
    versuch = array[i] = getc(datei);
    if (versuch < 0) {
      return -1;
    }
  } */
  for (int i = 0; i < arrayLaenge; i++) {
    if ((array[i] = getc(datei)) < 0) {
      return -1;
    }
  }
  return 0;
}