#ifndef CMORGAN_GATES_H
#define CMORGAN_GATES_H

#include "basegate.h"

void AND(CMWire *inputs, CMWire *outputs);
void OR(CMWire *inputs, CMWire *outputs);
void NOT(CMWire *inputs, CMWire *outputs);

#endif