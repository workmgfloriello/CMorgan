#ifndef CMORGAN_BASEGATE_H
#define CMORGAN_BASEGATE_H

#include <stdbool.h>


typedef struct {
    int power;
    char *name;
} CMWire;

typedef void (*GateFunction)(
    CMWire *inputs,
    CMWire *outputs
);

typedef struct CMGate {
    char *name;
    size_t input_count;

    CMWire *inputs;
    CMWire *outputs;

    GateFunction execute;

    int childCount;
    int fatherCount;
} CMGate;


CMGate *CMGate_create(char *name, size_t input_size, CMWire *inputs, CMWire *outputs, GateFunction execute);

bool CMGate_destroy(CMGate *gate);
bool CMGate_execute(CMGate *gate);

bool checkGateInput(CMGate *gate, CMWire *wire);
bool checkGateOutput(CMGate *gate, CMWire *wire);

#endif
