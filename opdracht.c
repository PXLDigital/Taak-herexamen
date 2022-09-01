#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void filter(unsigned char *pixels, int totaalpixels);
void cleanup(unsigned char *pixels, unsigned char *header, int totaalAantalPixels, const char *argv);

int main(int argc, char const *argv[])
{
    //finding -input
    int Argvinput = 0;
    for (int i = 0; i < argc; i++)
    {
             if (strcmp(argv[i], "-in") == 0)
        {
            Argvinput = i + 1;
            break;
        }
    }
    if (Argvinput == 0)
    {
        printf("could not find -in");
        exit(EXIT_FAILURE);
    }

    // opening file
    FILE *inputBMP = fopen(argv[Argvinput], "rb");
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

    printf("INFO: File %s CLOSED\n", argv[Argvinput]);

    //filter process in diffrent function
    filter(pixels,totaalAantalPixels); 

    //finding -output
    Argvinput == 0 ;
    for (int i = 0; i < argc; i++)
    {
             if (strcmp(argv[i], "-out") == 0)
        {
            Argvinput = i + 1;
            break;
        }
    }
    if (Argvinput == 0)
    {
        printf("could not find -out");
        exit(EXIT_FAILURE);
    }
    
    //cleaning up diffrent function
    cleanup(pixels, header, totaalAantalPixels, argv[Argvinput]);

   
}

void filter(unsigned char *pixels, int totaalpixels)
{
    //initializing 
    int Rf = 0;
    int Gf = 0;
    int Bf = 0;

    //finding color values
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

    //filter algorythm 
    for (int pixel = 0; pixel < totaalpixels; ++pixel)
    {
            int startloc = pixel * 3;
            if (Rf < pixels[startloc + 2])
            {
                pixels[startloc + 2] = Rf;
            } // Red

            if (Gf < pixels[startloc + 1])
            {
                pixels[startloc + 1] = Gf;
            } //green

            if (Bf < pixels[startloc])
            {
                pixels[startloc] = Bf;
            } // blue
       
    }
}

void cleanup(unsigned char *pixels, unsigned char *header, int totaalAantalPixels, const char *output)
{   //file creation
    FILE *outputbmp = fopen(output, "wb");
    if (outputbmp == NULL)
    {
        printf("can't create file");
    }
    fwrite(header, 54, 1, outputbmp);
    fwrite(pixels, (totaalAantalPixels)*3, 1, outputbmp);

    //cleaning and realising data
    fclose(outputbmp);
    free(pixels);
    free(header);
    printf("INFO: Heap memory Freed = %d (bytes)\n", totaalAantalPixels * 3);
}
