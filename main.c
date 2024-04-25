#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void beginn();
void ende();
void berechnung();

int main() {
    printf(" _______________________________________________________________________\n");
    printf("|[] AmigaShell                                                     |X]|!|\n");
    printf("|---------------------------------------------------------------------| |\n");
    printf("|                                                                     | |\n");
    printf("| 1.Workbench:> cd Work                                               | |\n");
    printf("| 1.Work:> Arbeitszeiterfassung                                       | |\n");
    printf("|                                                                     | |\n");
    printf("| [1] Arbeitsbeginn                                                   | |\n");
    printf("| [2] Arbeitsende                                                     | |\n");
    printf("| [0] Andere Eingabe : Programmende                                   | |\n");
    printf("|_____________________________________________________________________|/|\n");

    printf("\n");
    char auswahl[10];
    fgets(auswahl, sizeof(auswahl), stdin);

    if (strcmp(auswahl, "1\n") == 0) {
        beginn();
    } else if (strcmp(auswahl, "2\n") == 0) {
        ende();
    } else {
        printf("Auf Wiedersehen\n");
    }

    return 0;
}

char *getDesktopPath() {
    return "/home/miri/Schreibtisch";
}

void beginn() {
    printf("Arbeitszeitbeginn notiert.\n");
    char *desktopPath = getDesktopPath();
    char *filePath = malloc(strlen(desktopPath) + strlen("/Arbeitszeit.txt") + 1);
    strcpy(filePath, desktopPath);
    strcat(filePath, "/Arbeitszeit.txt");

    FILE *file = fopen(filePath, "a");
    if (file == NULL) {
        printf("Fehler beim Öffnen der Datei.\n");
        free(filePath);
        return;
    }
    time_t now;
    time(&now);
    struct tm *local_time = localtime(&now);
    char zeit[20];
    strftime(zeit, sizeof(zeit), "%d.%m.%Y %H:%M:%S", local_time);
    fprintf(file, "-------------------------------------------\n");
    fprintf(file, "Arbeitsbeginn: %s\n", zeit);
    fclose(file);
    free(filePath);
}

void ende() {
    char *desktopPath = getDesktopPath();
    char *filePath = malloc(strlen(desktopPath) + strlen("/Arbeitszeit.txt") + 1);
    strcpy(filePath, desktopPath);
    strcat(filePath, "/Arbeitszeit.txt");

    FILE *file = fopen(filePath, "a");
    if (file == NULL) {
        printf("Fehler beim Öffnen der Datei.\n");
        free(filePath);
        return;
    }
    time_t now;
    time(&now);
    struct tm *local_time = localtime(&now);
    char zeit[20];
    strftime(zeit, sizeof(zeit), "%d.%m.%Y %H:%M:%S", local_time);
    fprintf(file, "Arbeitsende:   %s\n", zeit);
    fclose(file);
    berechnung();
    free(filePath);
}



void berechnung() {
    FILE *file = fopen("Arbeitszeit.txt", "r");
    if (file == NULL) {
        printf("Fehler beim Öffnen der Datei.\n");
        return;
    }
    
    char line[100];
    char *arbeitsbeginn_str = NULL;
    char *arbeitsende_str = NULL;
    
    // Durch die Datei gehen und Arbeitsbeginn und -ende finden
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, "Arbeitsbeginn")) {
            arbeitsbeginn_str = strdup(line);
        }
        if (strstr(line, "Arbeitsende")) {
            arbeitsende_str = strdup(line);
        }
    }
    fclose(file);
    
    // Prüfen, ob sowohl Arbeitsbeginn als auch -ende gefunden wurden
    if (arbeitsbeginn_str == NULL || arbeitsende_str == NULL) {
        printf("Fehler: Arbeitsbeginn oder -ende nicht gefunden.\n");
        return;
    }
    
    // Zeitdaten aus den Zeichenketten parsen
    struct tm arbeitsbeginn, arbeitsende;
    sscanf(arbeitsbeginn_str, "Arbeitsbeginn: %d.%d.%d %d:%d:%d\n",
           &arbeitsbeginn.tm_mday, &arbeitsbeginn.tm_mon, &arbeitsbeginn.tm_year,
           &arbeitsbeginn.tm_hour, &arbeitsbeginn.tm_min, &arbeitsbeginn.tm_sec);
    sscanf(arbeitsende_str, "Arbeitsende:   %d.%d.%d %d:%d:%d\n",
           &arbeitsende.tm_mday, &arbeitsende.tm_mon, &arbeitsende.tm_year,
           &arbeitsende.tm_hour, &arbeitsende.tm_min, &arbeitsende.tm_sec);
    
    // Zeitstrukturen in Zeitstempel umwandeln
    time_t beginn_time = mktime(&arbeitsbeginn);
    time_t ende_time = mktime(&arbeitsende);
    
    // Differenz berechnen und ausgeben
    double differenz = difftime(ende_time, beginn_time);
    int stunden = (int)differenz / 3600;
    int minuten = ((int)differenz % 3600) / 60;
    printf("Die Arbeitszeit beträgt %d Stunden und %d Minuten.\n", stunden, minuten);
    
    // Arbeitszeit in die Datei schreiben
    fprintf(file, "Die Arbeitszeit beträgt %d Stunden und %d Minuten.\n", stunden, minuten);
    
    // Allokierten Speicher freigeben
    free(arbeitsbeginn_str);
    free(arbeitsende_str);
}



// alte Methode
// void beginn() {
//     printf("Arbeitszeitbeginn notiert.\n");
//     FILE *file = fopen("Arbeitszeit.txt", "a");
//     if (file == NULL) {
//         printf("Fehler beim Öffnen der Datei.\n");
//         return;
//     }
//     time_t now;
//     time(&now);
//     struct tm *local_time = localtime(&now);
//     char zeit[20];
//     strftime(zeit, sizeof(zeit), "%d.%m.%Y %H:%M:%S", local_time);
//     fprintf(file, "-------------------------------------------\n");
//     fprintf(file, "Arbeitsbeginn: %s\n", zeit);
//     fclose(file);
// }


// alte Methode
// void ende() {
//     FILE *file = fopen("Arbeitszeit.txt", "a");
//     if (file == NULL) {
//         printf("Fehler beim Öffnen der Datei.\n");
//         return;
//     }
//     time_t now;
//     time(&now);
//     struct tm *local_time = localtime(&now);
//     char zeit[20];
//     strftime(zeit, sizeof(zeit), "%d.%m.%Y %H:%M:%S", local_time);
//     fprintf(file, "Arbeitsende:   %s\n", zeit);
//     fclose(file);
//     berechnung();
// }
