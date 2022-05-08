#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "eingabeZeit.h"
#include "jaNeinAbfrage.h"

int main() {
  unsigned int arbeitsbeginn_stunden = 0;  // Eingestempelt, Stundenanteil
  unsigned int arbeitsbeginn_minuten = 0;  // Eingestempelt, Minutenanteil
  unsigned int arbeitszeit_stunden = 0;    // Arbeitszeit, Stundenanteil
  unsigned int arbeitszeit_minuten = 0;    // Arbeitszeit, Minutenanteil
  unsigned int pause_stunden = 0;
  unsigned int pause_minuten = 0;
  char pause_gesetzlich = 0;
  time_t jetzt = 0;                // aktuelle Zeit (Sekunden seit 01.01.1970)
  struct tm* arbeitsende = NULL;   // Arbeitsende (Konstrukt mit Datum/Uhrzeit)
  float zeit_bis_arbeitsende = 0;  // von "jetzt" bis zum Arbeitsende in Stunden

  // Benutzerreingabe
  printf("Geben Sie die Anfangszeit ein ");
  while (eingabeZeit(&arbeitsbeginn_stunden, &arbeitsbeginn_minuten) != 0) {
    printf("Versuchen Sie es noch einmal ");
  }

  printf("Geben Sie die Laenge der Arbeitszeit ein ");
  while (eingabeZeit(&arbeitszeit_stunden, &arbeitszeit_minuten) != 0) {
    printf("Versuchen Sie es noch einmal ");
  }

  printf("Entspricht die Laenge ihrer Pause den gesetzlichen Vorgaben? ");
  while (jaNeinAbfrage(&pause_gesetzlich) != 0) {
    printf("Versuchen Sie es noch einmal ");
  }

  if (pause_gesetzlich == 'j') {
    if (arbeitszeit_stunden >= 9) {
      pause_minuten = 45;

    } else if (arbeitszeit_stunden >= 6) {
      pause_minuten = 30;

    } else {
      pause_minuten = 0;
    }
  } else if (pause_gesetzlich == 'n') {
    printf("Geben Sie die Laenge der Pause ein ");
    while (eingabeZeit(&pause_stunden, &pause_minuten) != 0) {
      printf("Versuchen Sie es noch einmal ");
    }
  }

  // aktuelle Zeit ermitteln und in "jetzt" speichern
  time(&jetzt);

  // Zeit-Konstrukt aus der Zeit in "jetzt" erstellen
  arbeitsende = localtime(&jetzt);

  // Tageswechsel überprüfen und Tag des Arbeitsbeginns anpassen
  if (arbeitsende->tm_hour < (int)arbeitsbeginn_stunden) {
    arbeitsende->tm_mday -= 1;
  }

  // Arbeitsende aus Arbeitsbeginn, Arbeitszeit und Pause ermitteln
  arbeitsende->tm_hour =
      arbeitsbeginn_stunden + arbeitszeit_stunden + pause_stunden;
  arbeitsende->tm_min =
      arbeitsbeginn_minuten + arbeitszeit_minuten + pause_minuten;

  // Differenz zwischen Jetzt und Arbeitsende ermitteln
  // Arbeitsende-Kontrukt aufräumen!!! Doppelte Nutzen aus mktime()
  zeit_bis_arbeitsende = difftime(mktime(arbeitsende), jetzt) / 3600;

  // Ausgabe
  printf(
      "\nBei einer Arbeitszeit von %d:%02dh und %d:%02dh Pause "
      "waere gegen %02d:%02d Arbeitsende\n",
      arbeitszeit_stunden, arbeitszeit_minuten, pause_stunden, pause_minuten,
      arbeitsende->tm_hour, arbeitsende->tm_min);

  printf("\nNoch %d Stunden und %.0f Minuten ", (int)zeit_bis_arbeitsende,
         (zeit_bis_arbeitsende - (int)zeit_bis_arbeitsende) * 60);

  // Fenster offen halten bis der Benutzer ENTER drückt
  getchar();

  return EXIT_SUCCESS;
}
