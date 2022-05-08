#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARBEITSZEIT_STUNDEN 7   // reguläre Arbeitszeit, Stundenanteil
#define ARBEITSZEIT_MINUTEN 48  // reguläre Arbeitszeit, Minutenanteil
#define PAUSE_STUNDEN 0         // reguläre Pausenzeit, Stundenanteil
#define PAUSE_MINUTEN 30        // reguläre Pausenzeit, Minutenanteil

int eingabeUhrzeit(unsigned int* stundenPointer, unsigned int* minutenPointer);

int main() {
  // notwendige Variablen, bitte nicht verändern
  unsigned int arbeitsbeginn_stunden = 0;  // Eingestempelt, Stundenanteil
  unsigned int arbeitsbeginn_minuten = 0;  // Eingestempelt, Minutenanteil
  time_t jetzt = 0;                // aktuelle Zeit (Sekunden seit 01.01.1970)
  struct tm* arbeitsende = NULL;   // Arbeitsende (Konstrukt mit Datum/Uhrzeit)
  float zeit_bis_arbeitsende = 0;  // von "jetzt" bis zum Arbeitsende in Stunden

  // Benutzerreingabe des Einstempelns anfordern test
  printf("Geben Sie die Anfangszeit ein ");
  eingabeUhrzeit(&arbeitsbeginn_stunden, &arbeitsbeginn_minuten);

  // Benutzer-Eingabe auf Sinnhaftigkeit überprüfen
  if (arbeitsbeginn_stunden > 23 || arbeitsbeginn_minuten > 59) {
    printf("\nSehr witzig. Versuchen Sie es noch einmal!");
  } else {
    // aktuelle Zeit ermitteln und in "jetzt" speichern
    time(&jetzt);

    // Zeit-Konstrukt aus der Zeit in "jetzt" erstellen
    arbeitsende = localtime(&jetzt);

    // Tageswechsel überprüfen und Tag des Arbeitsbeginns anpassen
    if (arbeitsende->tm_hour < arbeitsbeginn_stunden) {
      arbeitsende->tm_mday -= 1;
    }

    // Arbeitsende aus Arbeitsbeginn, Arbeitszeit und Pause ermitteln
    arbeitsende->tm_hour =
        arbeitsbeginn_stunden + ARBEITSZEIT_STUNDEN + PAUSE_STUNDEN;
    arbeitsende->tm_min =
        arbeitsbeginn_minuten + ARBEITSZEIT_MINUTEN + PAUSE_MINUTEN;

    // Differenz zwischen Jetzt und Arbeitsende ermitteln
    // Arbeitsende-Kontrukt aufräumen!!! Doppelte Nutzen aus mktime()
    zeit_bis_arbeitsende = difftime(mktime(arbeitsende), jetzt) / 3600;

    // Ausgabe
    printf(
        "\nBei einer regulaeren Arbeitszeit von %d:%02dh und %d:%02dh Pause "
        "waere gegen %02d:%02d Arbeitsende\n",
        ARBEITSZEIT_STUNDEN, ARBEITSZEIT_MINUTEN, PAUSE_STUNDEN, PAUSE_MINUTEN,
        arbeitsende->tm_hour, arbeitsende->tm_min);

    printf("\nNoch %d Stunden und %.0f Minuten ", (int)zeit_bis_arbeitsende,
           (zeit_bis_arbeitsende - (int)zeit_bis_arbeitsende) * 60);
  }

  // Fenster offen halten bis der Benutzer ENTER drückt
  getchar();

  return EXIT_SUCCESS;
}

int eingabeUhrzeit(unsigned int* stundenPointer, unsigned int* minutenPointer) {
  unsigned int stundenEingabe = 0;
  unsigned int minutenEingabe = 0;

  printf("[HH:MM] ");
  scanf("%2u:%2u", &stundenEingabe, &minutenEingabe);
  while (getchar() != '\n')
    ;

  *stundenPointer = stundenEingabe;
  *minutenPointer = minutenEingabe;
  return 0;
}