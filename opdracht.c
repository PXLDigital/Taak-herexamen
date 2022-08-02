#include <stdio.h>
#include <stdlib.h>

void cleanup(unsigned char *pixels, unsigned char *header, int totaalAantalPixels, const char *argv);

int main(int argc, char const *argv[])
{
    // opening file
    FILE *inputBMP = fopen(argv[1], "rb");
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
    printf("INFO: File %s CLOSED\n", argv[1]);

    //----------------------------------------

    cleanup(pixels, header, totaalAantalPixels, argv[2]);

    //-----------------------------------------
}

void zwartwit(unsigned char * pixels, signed int hoogte, signed int breedte){
    int doorgaan = 0;
    int Rf = 0;
    int Gf = 0;
    int Bf = 0;
    while (doorgaan == 0)
    {
        printf("Rood filter geef een getal (0 - 255) :");
        scanf("%i",&Rf);
        if (Rf >= 0 && Rf <= 255)
        {
            doorgaan = 1;
        }
        else
        {
            printf("%i zit niet tussen 0 en 255\n",Rf);
        }
    }
    doorgaan = 0;
   while (doorgaan == 0)
    {
        printf("Groen filter geef een getal (0 - 255) :");
        scanf("%i",&Gf);
        if (Gf >= 0 && Gf <= 255)
        {
            doorgaan = 1;
        }
        else
        {
            printf("%i zit niet tussen 0 en 255\n",Gf);
        }
    }
    doorgaan = 0;
    while (doorgaan == 0)
    {
        printf("Blauw filter geef een getal (0 - 255) :");
        scanf("%i",&Bf);
        if (Bf >= 0 && Bf <= 255)
        {
            doorgaan = 1;
        }
        else
        {
            printf("%i zit niet tussen 0 en 255\n",Bf);
        }
    }
    doorgaan = 0;
    
    for (int y = 0; y < hoogte; ++y)
    {
        for (int x = 0; x < breedte; ++x)
        {
            long startloc = (x + (y * breedte));
            startloc *= 3;
            if (Rf < pixels[startloc + 2]) {pixels[startloc + 2] = Rf;} //Rood

            if (Gf < pixels[startloc + 1]) {pixels[startloc + 1] = Gf;} //
            
            if (Bf < pixels[startloc]) {pixels[startloc] = Bf;}// blauw
        }
    }
}

void cleanup(unsigned char *pixels, unsigned char *header, int totaalAantalPixels, const char * output)
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
