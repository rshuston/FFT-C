#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "app.h"
#include "bithacks.h"
#include "complex.h"
#include "fft.h"


#define INPUT_LINE_LENGTH   128


int app_exec(int argc, char *argv[])
{
    int returnValue = 1;

    if (argc == 2)
    {
        FILE *fp;

        if ( (fp = fopen(argv[1], "r")) != NULL )
        {
            complex_f *data = NULL;
            int size = 0;
            char line[INPUT_LINE_LENGTH + 1];
            while ( fgets(line, INPUT_LINE_LENGTH, fp) != NULL )
            {
                line[INPUT_LINE_LENGTH] = '\0';

                float realValue;
                sscanf(line, "%f", &realValue);

                data = realloc(data, sizeof(complex_f) * (size + 1));
                data[size].re = realValue;
                data[size].im = 0.f;
                size++;
            }

            fclose(fp);

            unsigned r = log2_u(size);
            unsigned N = 1 << r;

            ffti_f(data, r, FFT_FORWARD);

            for (int i = 0; i < N; i++)
            {
                printf("[%d] = { %.6f , %.6f }\n", i, data[i].re, data[i].im);
            }

            free(data);

            returnValue = 0;
        }
    }

    return returnValue;
}

