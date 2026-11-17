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
    gate->nextGate = NULL;

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

void CMGate_connect(CMGate *gateInp, CMWire *wireIn, CMGate *gateOut,CMWire *wireOut){

    gateInp->nextGate = gateOut;
    gateInp->childCount++;
    //Controllo cavi DA FARE
    wireOut->power = wireIn->power;

}