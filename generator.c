/******************************************************\
*                                                      *
*   generator.c                                        *
*                                                      *
*   Created: Saturday, 09-Nov-2019 16:20:01 EET        *
*   By Serghei Amelian                                 *
*                                                      *
*                                                      *
\******************************************************/
#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static void get_random_number(FILE *fin, char *buf, int size, int is_divider)
{
    int32_t int_part;

    do
    {
        fread(&int_part, sizeof(int_part), 1, fin);
    }
    while(int_part == 0); // nu vrem sa avem zero la partea intreaga

    if(is_divider)
        int_part &= 0x00000fff;
    else
        int_part &= 0x0fffffff;

    int32_t frac_part;

    fread(&frac_part, sizeof(frac_part), 1, fin);
    frac_part &= 0x0fffffff;

    char buf_frac_part[5];
    buf_frac_part[4] = 0; // c-string terminator

    int n = snprintf(buf_frac_part, 5, "%d", frac_part);

    // completeaza cu caractere '0'
    for(; n < sizeof(buf_frac_part) - 1; n++)
        buf_frac_part[n] = '0';

    snprintf(buf, size, "%d.%s", int_part, buf_frac_part);
}


int main(int argc, char *argv[])
{
    clock_t time_start = clock();

    FILE *fin = fopen("/dev/urandom", "r");

    if(!fin)
    {
        perror("Nu s-a putut deschide fisierul /dev/urandom");
        exit(1);
    }

    FILE *fout = fopen("random_numbers.txt", "w");

    if(!fout)
    {
        perror("Nu s-a putut crea fisierul random_numbers.txt");
        fclose(fin);
        exit(2);
    }

    int num;
    for(num = 0; num < 10000000; num++)
    {
        char buf1[64];
        get_random_number(fin, buf1, sizeof(buf1), 0);

        char buf2[64];
        get_random_number(fin, buf2, sizeof(buf2), 1);

        double v1 = atof(buf1);
        double v2 = atof(buf2);
        double result = v1 / v2;

        fprintf(fout, "%s\t%s\t%0.8f\n", buf1, buf2, result);
    }

    fclose(fout);
    fclose(fin);

    clock_t time_end = clock();

    fprintf(stdout, "Au fost generate %d de perechi de numere aleatoare în %d secunde.\n", num, (time_end - time_start) / CLOCKS_PER_SEC);

    fprintf(stdout, "Se genereaza md5sum...\n");
    system("md5sum random_numbers.txt");

    return 0;
}
