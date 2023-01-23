#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "spotfes.h"

int main(int argc, char **argv)
{

    Spotfes s;

    s = Spotfes_constroi();
    s = Spotfes_le(s, argc, argv);
    Spotfes_funcionalidades(s);
    Spotfes_destroi(s);
    printf("\n\033[1m----Ate a proxima!----\033[0m\n\n");

    return 0;
}
