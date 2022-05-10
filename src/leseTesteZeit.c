#include <stdio.h>

#include "leseDatei.h"
#include "testZeit.h"

int leseTesteZeit(FILE* datei, unsigned int array[]) {
  unsigned int zeit[2] = {0};

  if ((leseDatei(datei, zeit, 2)) < 0) return -1;
  if (testZeit(zeit[0], zeit[1]) < 0) return -1;

  for (int i = 0; i < 2; i++) {
    array[i] = zeit[i];
  }

  return 0;
}