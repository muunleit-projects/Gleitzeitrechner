/**
 * It reads the starting time, the working time and the pause time from the user
 * and calculates the time when the work ends and the difference between the
 * current time and the time when the work ends.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "eingabeZeit.h"
#include "jaNeinAbfrage.h"
#include "leseTesteZeit.h"
#include "schreibeDatei.h"

int main(void) {
  /* Array of hours and minutes when work started today */
  unsigned int arbeitsbeginn[2] = {0};
  /* Array of hours and minutes of the daily work */
  unsigned int arbeitszeit[2] = {0};
  /* Array of hours and minutes of the daily pause */
  unsigned int pause[2] = {0};
  /* Variable to hold info if the pause is based on the legal requirements */
  int pause_gesetzlich = 0;
  /* Handle for the savefile */
  FILE* speicher_datei = NULL;
  /* Name of the savefile */
  char name_speicher_datei[] = "GleitzeitSpeicher";
  /* Variable that is used to check if an error occured */
  int fehler = 0;
  /* The current time */
  time_t jetzt = 0;
  /* The workingdays end */
  struct tm* arbeitsende = NULL;
  /* The time until workingdays end */
  float zeit_bis_arbeitsende = 0;

  /*
   * Asking the user to input the starting time.
   */
  printf("Geben Sie die Anfangszeit ein ");

  while (eingabeZeit(&arbeitsbeginn[0], &arbeitsbeginn[1]) != 0) {
    printf("Versuchen Sie es noch einmal ");
  }

  /*
   * Opening the save-file and reading the values of the arrays arbeitszeit and
   * pause from it.
   */
  speicher_datei = fopen(name_speicher_datei, "rb");

  if (speicher_datei) {
    fehler = 0;

    /* get the working time */
    if ((leseTesteZeit(speicher_datei, arbeitszeit)) != 0) {
      fehler = 1;
    }

    /* get the pause time */
    if ((leseTesteZeit(speicher_datei, pause)) != 0) {
      fehler = 1;
    }

    fclose(speicher_datei);
    printf(">> Arbeitszeit %d:%02dh und %d:%02dh Pause aus Datei %s gelesen\n",
           arbeitszeit[0], arbeitszeit[1], pause[0], pause[1],
           name_speicher_datei);
  } else {
    fehler = 1;
  }

  /*
   * if reading the values of working time and the pause time from the savefile
   * didn't work, asking the user to input the working time and the pause time.
   */
  if (fehler) {
    printf(">> Datei %s konnte nicht korrekt gelesen werden\n",
           name_speicher_datei);

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

    /*
     * Setting the length of the pause to the legal requirements or asking the
     * user to input the pause time.
     */
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

    /*
     * Opening the savefile and writing the values of the arrays arbeitszeit and
     * pause into it.
     */
    speicher_datei = fopen(name_speicher_datei, "w+b");

    if (speicher_datei) {
      fehler = 0;

      /* write the working time */
      if (schreibeDatei(speicher_datei, arbeitszeit, 2) != 0) {
        fehler = 1;
      }

      /* write the pause time */
      if (schreibeDatei(speicher_datei, pause, 2) != 0) {
        fehler = 1;
      }

      fclose(speicher_datei);

      printf(
          ">> Arbeitszeit %d:%02dh und %d:%02dh Pause in Datei %s "
          "geschrieben\n",
          arbeitszeit[0], arbeitszeit[1], pause[0], pause[1],
          name_speicher_datei);

    } else {
      fehler = 1;
    }

    /* It checks if the file could be written. */
    if (fehler) {
      printf(">> Datei %s konnte nicht geschrieben werden\n",
             name_speicher_datei);
    }
  }

  /*
   * It gets the current time and stores it in the variable `jetzt`.
   */
  time(&jetzt);

  /*
   * It converts the time_t value `jetzt` to a struct tm value in local format.
   */
  arbeitsende = localtime(&jetzt);

  /*
   * It checks if the current hour is smaller than the starting hour.
   * If it is, it subtracts one from the day.
   */
  if (arbeitsende->tm_hour < (int)arbeitsbeginn[0]) {
    arbeitsende->tm_mday -= 1;
  }

  /*
   * Adding the starting time, the working time and the pause time to the
   * current time.
   */
  arbeitsende->tm_hour = arbeitsbeginn[0] + arbeitszeit[0] + pause[0];
  arbeitsende->tm_min = arbeitsbeginn[1] + arbeitszeit[1] + pause[1];

  /*
   * It calculates the time difference between the current time and the time
   * when  work ends and clean Up Arbeitsende-Kontrukt in one functioncall
   */
  zeit_bis_arbeitsende = difftime(mktime(arbeitsende), jetzt) / 3600;

  /*
   * Printing the time when the work ends and the time left until the work ends.
   */
  printf("\nDas Ende des Arbeitstages waere gegen %02d:%02d \n",
         arbeitsende->tm_hour, arbeitsende->tm_min);

  printf("\nNoch %d Stunden und %.0f Minuten ", (int)zeit_bis_arbeitsende,
         (zeit_bis_arbeitsende - (int)zeit_bis_arbeitsende) * 60);

  /*
   * Waiting for the user to press a key.
   */
  getchar();

  return EXIT_SUCCESS;
}
