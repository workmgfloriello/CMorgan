#include "basegate.h"
#include "simulator.h"

#include <stdlib.h>

CMGate *CMGate_create(char *name, size_t input_count, CMWire *inputs, CMWire *outputs,GateFunction execute){

    CMGate *gate = malloc(sizeof(CMGate));

    if (gate == NULL) {
    return NULL;
    }

    gate->name = name;
    gate->input_count = input_count;
    gate->inputs = inputs;
    gate->outputs = outputs;
    gate->execute = execute;
    gate->childCount = 0;
    gate->fatherCount = 0;

    bool result = addGate(gate);

    if (result) {
        return gate;
    } else {
        free(gate);
        return NULL;
    }
}

bool CMGate_destroy(CMGate *gate) {
    if (gate == NULL) {
        return false;
    }

    return removeGate(gate);
}


bool CMGate_execute(CMGate *gate) {
    return executeGate(gate);
}


bool checkGateInput(CMGate *gate, CMWire *wire) {
    if (gate == NULL || wire == NULL) {
        return false;
    }

    for (size_t i = 0; i < gate->input_count; i++) {
        if (&gate->inputs[i] == wire) {
            return true;
        }
    }

    return false;
}

bool checkGateOutput(CMGate *gate, CMWire *wire) {
    if (gate == NULL || wire == NULL) {
        return false;
    }

    return &gate->outputs[0] == wire;
}