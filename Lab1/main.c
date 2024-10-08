#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

#define IME_DATOTEKE "studenti.txt"
#define BUFFER_MAX 1024
#define MAX_BODOVI 50
#define FILE_ERROR -1
#define ALLOC_ERROR -2

struct Student {
    char ime[16];
    char prezime[32];
    int bodovi;
};

int nadibrojStudenata(const char* imeDatoteke);
int ucitajStudente(struct Student* studenti, int brojStudenata, const char* imeDatoteke);
void ispisiStudente(struct Student* studenti, int brojStudenata);

int main()
{
    int brojStudenata = 0;
    struct Student* studenti = NULL;

    brojStudenata = nadibrojStudenata(IME_DATOTEKE);
    if (brojStudenata == FILE_ERROR)
    {
        printf("Datoteka %s nije se mogla otvoriti!", IME_DATOTEKE);
        return FILE_ERROR;
    }

    studenti = calloc(brojStudenata, sizeof(struct Student));
    if (!studenti)
    {
        printf("Nije bilo moguce alocirati studente!");
        return ALLOC_ERROR;
    }

    if (ucitajStudente(studenti, brojStudenata, IME_DATOTEKE) == FILE_ERROR)
    {
        printf("Datoteka %s nije se mogla otvoriti!", IME_DATOTEKE);
        return FILE_ERROR;
    }
    ispisiStudente(studenti, brojStudenata);

    return 0;
}


int nadibrojStudenata(const char* imeDatoteke)
{
    int brojStudenata = 0;
    FILE* datoteka = NULL;
    char buffer[BUFFER_MAX] = { '\0' };

    datoteka = fopen(imeDatoteke, "r");
    if (!datoteka)
    {
        return FILE_ERROR;
    }

    while (!feof(datoteka))
    {
        fgets(buffer, BUFFER_MAX, datoteka);
        ++brojStudenata;
    }
    fclose(datoteka);

    return brojStudenata;
}

int ucitajStudente(struct Student* studenti, int brojStudenata, const char* imeDatoteke)
{
    FILE* datoteka = NULL;

    datoteka = fopen(imeDatoteke, "r");
    if (!datoteka)
    {
        return FILE_ERROR;
    }

    for (int i = 0; i < brojStudenata; ++i)
    {
        fscanf(datoteka, "%s %s %d\n", studenti[i].ime, studenti[i].prezime, &studenti[i].bodovi);
    }
    fclose(datoteka);

    return 0;
}

void ispisiStudente(struct Student* studenti, int brojStudenata)
{
    for (int i = 0; i < brojStudenata; ++i)
    {
        printf("%s %s: %d/%d (%d%%)\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, MAX_BODOVI, studenti[i].bodovi * 100 / MAX_BODOVI);
    }
}