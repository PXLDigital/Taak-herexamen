#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void filter(unsigned char *pixels, signed int hoogte, signed int breedte);
void cleanup(unsigned char *pixels, unsigned char *header, int totaalAantalPixels, const char *argv);

int main(int argc, char const *argv[])
{
    int input = 0;
    int output = 0 ;
    for (int i = 0; i < argc; i++)
    {
             if (strcmp(argv[i], "-in") == 0)
        {
            input = i + 1;
            break;
        }
    }
    if (input == 0)
    {
        printf("could not find -in");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < argc; i++)
    {
             if (strcmp(argv[i], "-out") == 0)
        {
            output = i + 1;
            break;
        }
    }
   if (output == 0)
    {
        printf("could not find -out");
        exit(EXIT_FAILURE);
    }
    // opening file
    FILE *inputBMP = fopen(argv[input], "rb");
    unsigned char header[54] = {0};
    signed int hoogte = 0;
    signed int breedte = 0;
    unsigned char *pixels = NULL;
    int totaalAantalPixels = 0;

    if (inputBMP == NULL)
    {
        printf("%s\n", "ERROR: can't open the file");
        return -1;
    }

    // reading header info
    fread(header, 1, 54, inputBMP);
    breedte = header[21] << 24 | header[20] << 16 | header[19] << 8 | header[18];
    printf("De breedte van mijn afbeelding is = %d\n", breedte);
    hoogte = header[25] << 24 | header[24] << 16 | header[23] << 8 | header[22];
    printf("De hoogte van mijn afbeelding is = %d\n", hoogte);

    totaalAantalPixels = breedte * hoogte;
    pixels = (unsigned char *)malloc(totaalAantalPixels * 3);
    if (pixels == NULL)
    {
        printf("ERROR: memory allocation Failed\n");
        return -2;
    }

    fread(pixels, 1, totaalAantalPixels * 3, inputBMP);
    printf("INFO: Heap memory allocated = %d (bytes)\n", totaalAantalPixels * 3);

    fclose(inputBMP);
    printf("INFO: File %s CLOSED\n", argv[input]);

    //----------------------------------------
    filter(pixels, hoogte, breedte);
    cleanup(pixels, header, totaalAantalPixels, argv[output]);

    //-----------------------------------------
}

void filter(unsigned char *pixels, signed int hoogte, signed int breedte)
{
    int Rf = 0;
    int Gf = 0;
    int Bf = 0;
    while (1)
    {
        printf("Rood filter geef een getal (0 - 255) :");
        scanf("%i", &Rf);
        if (Rf >= 0 && Rf <= 255)
        {
            break;
        }
        else
        {
            printf("%i zit niet tussen 0 en 255\n", Rf);
        }
    }
    while (1)
    {
        printf("Groen filter geef een getal (0 - 255) :");
        scanf("%i", &Gf);
        if (Gf >= 0 && Gf <= 255)
        {
            break;
        }
        else
        {
            printf("%i zit niet tussen 0 en 255\n", Gf);
        }
    }
    while (1)
    {
        printf("Blauw filter geef een getal (0 - 255) :");
        scanf("%i", &Bf);
        if (Bf >= 0 && Bf <= 255)
        {
            break;
        }
        else
        {
            printf("%i zit niet tussen 0 en 255\n", Bf);
        }
    }

    for (int y = 0; y < hoogte; ++y)
    {
        for (int x = 0; x < breedte; ++x)
        {
            long startloc = (x + (y * breedte));
            startloc *= 3;
            if (Rf < pixels[startloc + 2])
            {
                pixels[startloc + 2] = Rf;
            } // Rood

            if (Gf < pixels[startloc + 1])
            {
                pixels[startloc + 1] = Gf;
            } //

            if (Bf < pixels[startloc])
            {
                pixels[startloc] = Bf;
            } // blauw
        }
    }
}

void cleanup(unsigned char *pixels, unsigned char *header, int totaalAantalPixels, const char *output)
{
    FILE *fpw = fopen(output, "wb");
    if (fpw == NULL)
    {
        printf("can't create file");
    }
    fwrite(header, 54, 1, fpw);
    fwrite(pixels, (totaalAantalPixels)*3, 1, fpw);
    fclose(fpw);
    free(pixels);
    free(header);
    printf("INFO: Heap memory Freed = %d (bytes)\n", totaalAantalPixels * 3);
}
