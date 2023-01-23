#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct criterios *Criterios;

// estrutura:
Criterios Criterios_constroi();

// leitura:
Criterios Criterios_le(Criterios c, FILE *f);

// funcionalidades:
void Lista_criterios(Criterios c);
