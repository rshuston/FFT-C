#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "app.h"
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
            char line[INPUT_LINE_LENGTH + 1];

            if ( fgets(line, INPUT_LINE_LENGTH, fp) != NULL )
            {
                line[INPUT_LINE_LENGTH] = '\0';
            }

            fclose(fp);
            returnValue = 0;
        }
    }

    return returnValue;
}
