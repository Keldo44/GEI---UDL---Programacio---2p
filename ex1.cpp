#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_LONGITUD_PARAULA 21
#define MAX_PARAULES_SPAM 100

// Funció per saltar caràcters invàlids i retornar el següent caràcter vàlid (lletra o punt)
char saltar_no_alfabetic()
{
    char c;
    while ((c = getchar()) != EOF)
    {
        if (isalpha(c) || c == '.')
        {
            return c; // Retorna el caràcter vàlid (lletra o punt)
        }
    }
    return EOF; // Fi de l'entrada
}

// Funció per llegir la següent paraula o seqüència de punts
void llegir_següent_paraula(char paraula[], bool final)
{
    paraula[0] = '\0';
    char c = saltar_no_alfabetic(); // Obté el primer caràcter vàlid
    int i = 0;
    int finalitzada_paraula = 0;
    if (final)
    {
        finalitzada_paraula = 1;
        paraula[1] = '\0';
    }

    while (c != EOF && i < MAX_LONGITUD_PARAULA - 1 && finalitzada_paraula != 1)
    {
        if (c == '.')
        {
            if (i == 0 || paraula[0] == '.')
            {
                paraula[i] = c;
                i++;
                if (paraula[1] == '.')
                {
                    finalitzada_paraula = 1;
                }
            }
            else
            {
                // Atura si un punt segueix una lletra alfabètica
                ungetc(c, stdin); // Torna a posar el caràcter a l'entrada
                finalitzada_paraula = 1;
            }
        }
        else if (isalpha(c))
        {
            // Si és una lletra alfabètica, emmagatzema-la en minúscula
            if (paraula[0] == '.')
            {
                ungetc(c, stdin); // Torna a posar el caràcter a l'entrada
                finalitzada_paraula = 1;
            }
            else
            {
                paraula[i++] = tolower(c);
            }
        }
        else
        {
            // Si és un separador, atura el processament
            if (paraula[0] == '.')
            {
                c = saltar_no_alfabetic();
                if (c != '.')
                {
                    ungetc(c, stdin); // Torna a posar el caràcter a l'entrada
                    finalitzada_paraula = 1;
                }else{
                    paraula[i] = c;
                    i++;
                    finalitzada_paraula = 1;
                }
            }
            else
            {
                finalitzada_paraula = 1;
            }
        }
        c = getchar(); // Llegeix el següent caràcter
    }
    if (!final)
    {
        ungetc(c, stdin); // Torna a posar el caràcter a l'entrada
        paraula[i] = '\0';   // Finalitza la cadena
        if (paraula[2] == '.')
        {
            paraula[2] = '\0';
        }
    }
}

void inicialitzar_llista_paraules(char llista[MAX_PARAULES_SPAM][MAX_LONGITUD_PARAULA + 1])
{
    for (int i = 0; i < MAX_PARAULES_SPAM; i++)
    {
        llista[i][0] = '\0';
    }
}

int omplir_llista_spam(char llista[MAX_PARAULES_SPAM][MAX_LONGITUD_PARAULA + 1], char paraula[MAX_LONGITUD_PARAULA], int &num_paraules)
{
    bool punt_trobat = false;
    while (!punt_trobat)
    {
        llegir_següent_paraula(paraula, false);
        if (strcmp(".", paraula) == 0)
        {
            punt_trobat = true;
        }
        else
        {
            // Comprova si la paraula ja està a la llista
            int es_duplicat = 0;
            for (int j = 0; j < num_paraules; j++)
            {
                if (strcmp(llista[j], paraula) == 0)
                {
                    es_duplicat = 1;
                }
            }

            // Si la paraula no és un duplicat, afegeix-la a la llista
            if (!es_duplicat)
            {
                strcpy(llista[num_paraules++], paraula);
                if (num_paraules == MAX_PARAULES_SPAM)
                {
                    printf("La llista de paraules spam és plena. Abortant...\n");
                    return 2;
                }
            }
        }
    }
    return 0;
}

void comptar_paraules_spam_missatge(char llista[MAX_PARAULES_SPAM][MAX_LONGITUD_PARAULA + 1], char paraula[MAX_LONGITUD_PARAULA], int comptadors[MAX_PARAULES_SPAM], int num_paraules)
{
    bool doble_punt_trobat = false;
    while (!doble_punt_trobat)
    {
        llegir_següent_paraula(paraula, false);
        if (strcmp("..", paraula) == 0)
        {
            doble_punt_trobat = true;
        }
        else
        {
            // Compara la paraula amb cada paraula de la llista i compta-la als comptadors
            for (int i = 0; i < num_paraules; i++)
            {
                if (strcmp(paraula, llista[i]) == 0)
                {
                    comptadors[i]++;
                }
            }
        }
    }
}

void imprimir_resultats(char llista[MAX_PARAULES_SPAM][MAX_LONGITUD_PARAULA + 1], int comptadors[MAX_PARAULES_SPAM], int num_paraules)
{
    printf("Introdueix les paraules a identificar:\n");
    printf("Introdueix el text acabat en doble punt (..):\n");
    printf("Relació de paraules buscades:\n");
    int paraules_spamejades = 0;
    // Per a cada paraula de la llista, comprova si ha aparegut dues vegades o més
    for (int i = 0; i < num_paraules; i++)
    {
        // Sortida desitjada
        // La paraula "qwert" apareix 0 vegada/es
        printf("La paraula \"%s\" apareix %d vegada/es\n", llista[i], comptadors[i]);
        if (comptadors[i] >= 2)
        {
            paraules_spamejades++;
        }
    }

    printf("Resultat:\n");
    printf("Rati: paraules amb 2 o més aparicions / total de paraules = %d / %d = %.3f\n", paraules_spamejades, num_paraules, (float)paraules_spamejades / num_paraules);
    if (paraules_spamejades >= (num_paraules / 2))
    {
        printf("El missatge és SPAM!\n");
    }
    else
    {
        printf("El missatge no és SPAM.\n");
    }
}

int main()
{
    char paraula[MAX_LONGITUD_PARAULA];
    char paraules[MAX_PARAULES_SPAM][MAX_LONGITUD_PARAULA + 1];
    int comptadors[MAX_PARAULES_SPAM] = {0};
    int num_paraules = 0;
    bool final = false;

    inicialitzar_llista_paraules(paraules);
    if (omplir_llista_spam(paraules, paraula, num_paraules) == 2)
    {
        return 0;
    }
    comptar_paraules_spam_missatge(paraules, paraula, comptadors, num_paraules);
    imprimir_resultats(paraules, comptadors, num_paraules);
    return 0;
}
