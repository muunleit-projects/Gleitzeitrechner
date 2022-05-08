
int eingabeUhrzeit(unsigned int* stundenPointer, unsigned int* minutenPointer) {
  unsigned int stundenEingabe = 0;
  unsigned int minutenEingabe = 0;

  printf("[HH:MM] ");
  scanf("%2u:%2u", &stundenEingabe, &minutenEingabe);
  /* Reading the newline character from the input buffer. */
  while (getchar() != '\n')
    ;

  /* Checking if the input is valid. */
  if (testUhrzeit(stundenEingabe, minutenEingabe) != 0) return 1;

  *stundenPointer = stundenEingabe;
  *minutenPointer = minutenEingabe;

  return 0;
}