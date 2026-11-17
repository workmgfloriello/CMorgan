#ifndef CMORGAN_SIMULATOR_H
#define CMORGAN_SIMULATOR_H

#include "basegate.h"

bool addGate(CMGate *gate);
bool removeGate(CMGate *gate);
bool executeGate(CMGate *gate);
#endif