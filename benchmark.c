/******************************************************\
*                                                      *
*   benchmark.c                                        *
*                                                      *
*   Created: Saturday, 09-Nov-2019 17:36:19 EET        *
*   By Serghei Amelian                                 *
*                                                      *
*                                                      *
\******************************************************/
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char *argv[])
{
    clock_t time_start = clock();

    FILE *fin = fopen("random_numbers.txt", "r");

    if(!fin)
    {
        perror("Nu s-a putut deschide fisierul random_numbers.txt");
        exit(1);
    }

    FILE *fout = fopen("result.txt", "w");

    if(!fout)
    {
        perror("Nu s-a putut crea fisierul result.txt");
        fclose(fin);
        exit(2);
    }

    int num = 0;
    for(; !feof(fin); num++)
    {
        char buf[256];
        memset(buf, 0, sizeof(buf));

        if(NULL == fgets(buf, sizeof(buf) - 1, fin))
            break;

        // elimina '\n'
        char *end = strchr(buf, '\n');
        if(end)
            *end = 0;

        char *token1 = strtok(buf, "\t");
        char *token2 = strtok(NULL, "\t");
        char *token3 = strtok(NULL, "\t");

        double v1 = atof(token1);
        double v2 = atof(token2);

        double result = v1 / v2;
        char buf_result[32];
        snprintf(buf_result, sizeof(buf_result), "%0.8f", result);

        // se compara rezultatul cu impartirii cu referinta din fisierul de input
        if(0 != strcmp(buf_result, token3))
        {
            fprintf(stderr, "Eroare: nu corespunde rezultatul!\n%s != %s", token3, buf_result);
            exit(3);
        }

        fprintf(fout, "%s\t%s\t%s\n", token1, token2, buf_result);
    }

    fclose(fin);
    fclose(fout);

    clock_t time_end = clock();
    fprintf(stdout, "Au procesate %d de perechi de numere aleatoare în %d secunde.\n", num, (time_end - time_start) / CLOCKS_PER_SEC);

    fprintf(stdout, "Se genereaza md5sum...\n");
    system("md5sum result.txt");

    return 0;
}
