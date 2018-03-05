#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "app.h"
#include "complex.h"
#include "fft.h"


#define INPUT_LINE_LENGTH   128


static uint32_t _log2_u(uint32_t v);


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

            unsigned r = _log2_u(size);
            unsigned N = 1 << r;

            fft_f(data, N);

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



static uint32_t _log2_u(uint32_t v)
{
    int r;      // result goes here

    static const int MultiplyDeBruijnBitPosition[32] =
    {
        0, 9, 1, 10, 13, 21, 2, 29, 11, 14, 16, 18, 22, 25, 3, 30,
        8, 12, 20, 28, 15, 17, 24, 7, 19, 27, 23, 6, 26, 5, 4, 31
    };

    v |= v >> 1; // first round down to one less than a power of 2
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;

    r = MultiplyDeBruijnBitPosition[(uint32_t)(v * 0x07C4ACDDU) >> 27];

    return r;
}
