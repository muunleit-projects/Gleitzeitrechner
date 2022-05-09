#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "eingabeZeit.h"
#include "jaNeinAbfrage.h"

int main() {
  unsigned int arbeitsbeginn_stunden = 0;
  unsigned int arbeitsbeginn_minuten = 0;
  unsigned int arbeitszeit_stunden = 0;
  unsigned int arbeitszeit_minuten = 0;
  unsigned int pause_stunden = 0;
  unsigned int pause_minuten = 0;
  int pause_gesetzlich = 0;
  time_t jetzt = 0;
  struct tm* arbeitsende = NULL;
  float zeit_bis_arbeitsende = 0;

  /* Asking the user to input the starting time. */
  printf("Geben Sie die Anfangszeit ein ");
  while (eingabeZeit(&arbeitsbeginn_stunden, &arbeitsbeginn_minuten) != 0) {
    printf("Versuchen Sie es noch einmal ");
  }

  /* Asking the user to input the working time. */
  printf("Geben Sie die Laenge der Arbeitszeit ein ");
  while (eingabeZeit(&arbeitszeit_stunden, &arbeitszeit_minuten) != 0) {
    printf("Versuchen Sie es noch einmal ");
  }

  /* Asking the user if the length of the pause is according to the legal
   * requirements. */
  printf("Entspricht die Laenge ihrer Pause den gesetzlichen Vorgaben? ");
  while ((pause_gesetzlich = jaNeinAbfrage()) < 0) {
    printf("Versuchen Sie es noch einmal ");
  }

  /* Setting the Asking the length of the pause to the legal requirements or
   * asking the user to input the pause time. */
  if (pause_gesetzlich) {
    if (arbeitszeit_stunden >= 9) {
      pause_minuten = 45;

    } else if (arbeitszeit_stunden >= 6) {
      pause_minuten = 30;

    } else {
      pause_minuten = 0;
    }
  } else {
    printf("Geben Sie die Laenge der Pause ein ");
    while (eingabeZeit(&pause_stunden, &pause_minuten) != 0) {
      printf("Versuchen Sie es noch einmal ");
    }
  }

  /* Getting the current time and storing it in the variable `jetzt`. */
  time(&jetzt);

  /* Converting the time_t value `jetzt` to a struct tm value in local format.
   */
  arbeitsende = localtime(&jetzt);

  /* It checks if the current hour is smaller than the starting hour.
   * If it is, it subtracts one from the day. */
  if (arbeitsende->tm_hour < (int)arbeitsbeginn_stunden) {
    arbeitsende->tm_mday -= 1;
  }

  /* Adding the starting time, the working time and the pause time to the
   * current time. */
  arbeitsende->tm_hour =
      arbeitsbeginn_stunden + arbeitszeit_stunden + pause_stunden;
  arbeitsende->tm_min =
      arbeitsbeginn_minuten + arbeitszeit_minuten + pause_minuten;

  /* It calculates the time difference between the current time and the time
   * when the work ends and clean Up Arbeitsende-Kontrukt in one functioncall */
  zeit_bis_arbeitsende = difftime(mktime(arbeitsende), jetzt) / 3600;

  /* Printing the time when the work ends and the time left until the work ends.
   */
  printf(
      "\nBei einer Arbeitszeit von %d:%02dh und %d:%02dh Pause "
      "waere gegen %02d:%02d Arbeitsende\n",
      arbeitszeit_stunden, arbeitszeit_minuten, pause_stunden, pause_minuten,
      arbeitsende->tm_hour, arbeitsende->tm_min);

  printf("\nNoch %d Stunden und %.0f Minuten ", (int)zeit_bis_arbeitsende,
         (zeit_bis_arbeitsende - (int)zeit_bis_arbeitsende) * 60);

  /* Waiting for the user to press a key. */
  getchar();

  return EXIT_SUCCESS;
}
