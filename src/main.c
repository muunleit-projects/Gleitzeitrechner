#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "eingabeZeit.h"
#include "jaNeinAbfrage.h"
#include "schreibeDatei.h"

int main(void) {
  /* Declaring arrays with hours in field [0] and minutes in feld [1] */
  unsigned int arbeitsbeginn[2] = {0};
  unsigned int arbeitszeit[2] = {0};
  unsigned int pause[2] = {0};
  int pause_gesetzlich = 0;
  FILE* speicher_datei;
  char name_speicher_datei[] = "GleitzeitSpeicher";
  time_t jetzt = 0;
  struct tm* arbeitsende = NULL;
  float zeit_bis_arbeitsende = 0;

  /* Asking the user to input the starting time. */
  printf("Geben Sie die Anfangszeit ein ");
  while (eingabeZeit(&arbeitsbeginn[0], &arbeitsbeginn[1]) != 0) {
    printf("Versuchen Sie es noch einmal ");
  }

  /* Opening the save-file and reading the values of the arrays arbeitszeit and
   * pause from it. */
  speicher_datei = fopen(name_speicher_datei, "rb");

  if (speicher_datei) {
    for (int i = 0; i <= 1; i++) {
      /* Reading the values and checking the if all expected values are there */
      if (((int)(arbeitszeit[i] = (int)getc(speicher_datei)) == EOF) |
          ((int)(pause[i] = (int)getc(speicher_datei)) == EOF)) {
        printf(">> Datei %s beschaedigt. Loeschen Sie die Datei",
               name_speicher_datei);

        return EXIT_FAILURE;
      }
    }

    fclose(speicher_datei);

  } else {
    printf(">> Datei %s konnte nicht gelesen werden\n", name_speicher_datei);

    /* Asking the user to input the working time. */
    printf("Geben Sie die Laenge der Arbeitszeit ein ");
    while (eingabeZeit(&arbeitszeit[0], &arbeitszeit[1]) != 0) {
      printf("Versuchen Sie es noch einmal ");
    }

    /* Asking the user if the length of the pause is according to the legal
     * requirements. */
    printf("Entspricht die Laenge ihrer Pause den gesetzlichen Vorgaben? ");
    while ((pause_gesetzlich = jaNeinAbfrage()) < 0) {
      printf("Versuchen Sie es noch einmal ");
    }

    /* Setting the length of the pause to the legal requirements or asking the
     * user to input the pause time. */
    if (pause_gesetzlich) {
      if (arbeitszeit[0] >= 9) {
        pause[1] = 45;

      } else if (arbeitszeit[0] >= 6) {
        pause[1] = 30;

      } else {
        pause[1] = 0;
      }
    } else {
      printf("Geben Sie die Laenge der Pause ein ");
      while (eingabeZeit(&pause[0], &pause[1]) != 0) {
        printf("Versuchen Sie es noch einmal ");
      }
    }

    /* Opening the save-file and writing the values of the arrays arbeitszeit
     * and pause into it. */
    speicher_datei = fopen(name_speicher_datei, "w+b");

    if (speicher_datei) {
      if (schreibeDatei(speicher_datei, arbeitszeit, 2) < 0) {
        printf(">> Arbeitszeit konnte nicht in Datei %s geschrieben werden\n",
               name_speicher_datei);
      }
      if (schreibeDatei(speicher_datei, pause, 2) < 0) {
        printf(">> Pause konnte nicht in Datei %s geschrieben werden\n",
               name_speicher_datei);
      }

      fclose(speicher_datei);

    } else {
      printf(">> Datei %s konnte nicht geschrieben werden\n",
             name_speicher_datei);
    }
  }

  /* Getting the current time and storing it in the variable `jetzt`. */
  time(&jetzt);

  /* Converting the time_t value `jetzt` to a struct tm value in local format */
  arbeitsende = localtime(&jetzt);

  /* It checks if the current hour is smaller than the starting hour.
   * If it is, it subtracts one from the day. */
  if (arbeitsende->tm_hour < (int)arbeitsbeginn[0]) {
    arbeitsende->tm_mday -= 1;
  }

  /* Adding the starting time, the working time and the pause time to the
   * current time. */
  arbeitsende->tm_hour = arbeitsbeginn[0] + arbeitszeit[0] + pause[0];
  arbeitsende->tm_min = arbeitsbeginn[1] + arbeitszeit[1] + pause[1];

  /* It calculates the time difference between the current time and the time
   * when the work ends and clean Up Arbeitsende-Kontrukt in one functioncall */
  zeit_bis_arbeitsende = difftime(mktime(arbeitsende), jetzt) / 3600;

  /* Printing the time when the work ends and the time left until the work ends.
   */
  printf(
      "\nBei einer Arbeitszeit von %d:%02dh und %d:%02dh Pause "
      "waere gegen %02d:%02d Arbeitsende\n",
      arbeitszeit[0], arbeitszeit[1], pause[0], pause[1], arbeitsende->tm_hour,
      arbeitsende->tm_min);

  printf("\nNoch %d Stunden und %.0f Minuten ", (int)zeit_bis_arbeitsende,
         (zeit_bis_arbeitsende - (int)zeit_bis_arbeitsende) * 60);

  /* Waiting for the user to press a key. */
  getchar();

  return EXIT_SUCCESS;
}
