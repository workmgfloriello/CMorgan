#include <stdlib.h>
#include "circuit.h"

CMCircuit *CMCircuit_create(void)
{
    CMCircuit *circuit = malloc(sizeof(CMCircuit));
    if (circuit == NULL)
    {
        return NULL;
    }

    circuit->gates = malloc(sizeof(CMGate *) * 10);
    if (circuit->gates == NULL)
    {
        free(circuit);
        return NULL;
    }

    circuit->connections = malloc(sizeof(CMConnection) * 10);
    if (circuit->connections == NULL)
    {
        free(circuit->gates);
        free(circuit);
        return NULL;
    }

    circuit->gate_count = 0;
    circuit->gate_capacity = 10;
    circuit->connection_count = 0;
    circuit->connection_capacity = 10;
    return circuit;
}


bool CMCircuit_addGate(CMCircuit *circuit, CMGate *gate) {

    if (circuit == NULL || gate == NULL) {
        return false;
    }

    if (circuit->gate_count >= circuit->gate_capacity) {

        size_t newSize = circuit->gate_capacity * 2;

        CMGate **newGates = realloc(
            circuit->gates,
            newSize * sizeof(CMGate *)
        );

        if (newGates == NULL) {
            return false;
        }

        circuit->gates = newGates;
        circuit->gate_capacity = newSize;
    }

    circuit->gates[circuit->gate_count] = gate;
    circuit->gate_count++;

    return true;
}

bool CMCircuit_containsGate(CMCircuit *circuit, CMGate *gate){
    if(circuit == NULL || gate == NULL){
        return false;
    }

    for(size_t i=0; i <circuit->gate_count; i++){
        if(circuit->gates[i] == gate){
            return true;
        }
    }
    return false;
}

bool CMCircuit_connect(
    CMCircuit *circuit,
    CMGate *sourceGate,
    CMWire *sourceWire,
    CMGate *destinationGate,
    CMWire *destinationWire
) {
    if (circuit == NULL || sourceGate == NULL || sourceWire == NULL ||
        destinationGate == NULL || destinationWire == NULL) {
        return false;
    }
    // VALIDATE GATES AND WIRES
    if(!checkGateInput(sourceGate, sourceWire) || !checkGateOutput(destinationGate, destinationWire) || !CMCircuit_containsGate(circuit, sourceGate) || !CMCircuit_containsGate(circuit, destinationGate)){
        return false;
    }

    if (circuit->connection_count >= circuit->connection_capacity) {
        size_t newCapacity = circuit->connection_capacity * 2;

        CMConnection *newConnections = realloc(
            circuit->connections,
            newCapacity * sizeof(*circuit->connections)
        );

        if (newConnections == NULL) {
            return false;
        }

        circuit->connections = newConnections;
        circuit->connection_capacity = newCapacity;
    }

    circuit->connections[circuit->connection_count].sourceGate = sourceGate;
    circuit->connections[circuit->connection_count].sourceWire = sourceWire;
    circuit->connections[circuit->connection_count].destinationGate = destinationGate;
    circuit->connections[circuit->connection_count].destinationWire = destinationWire;

    circuit->connection_count++;

    //AGGIORNO SOURCE GATE CHILD COUNTER
    sourceGate->childCount++;
    //AGGIORNO DESTINATION GATE FATHER COUNTER
    destinationGate->fatherCount++;

    return true;
}


bool CMCircuit_destroy(CMCircuit *circuit){
    if(circuit == NULL){
        return false;
    }

    for(size_t i = 0; i < circuit->gate_count; i++) {
        CMGate_destroy(circuit->gates[i]);
    }
    free(circuit->gates);
    free(circuit->connections);
    free(circuit);

    return true;
}

bool CMCircuit_execute(CMCircuit *circuit){
   if (circuit == NULL || circuit->gate_count == 0) {
    return false;
    }

    //scansiono tutte le porte del circuito e salviamo quelle senza padri (fatherCount == 0) in un array temporaneo
    CMGate **tempGates = malloc(sizeof(CMGate *) * circuit->gate_count);
    if (tempGates == NULL) {
        return false;
    }

    for(size_t i = 0; i < circuit->gate_count; i++) {
        if(circuit->gates[i]->fatherCount == 0) {
            tempGates[i] = circuit->gates[i];
        } else {
            tempGates[i] = NULL;
        }
    }

    //ESEGUO LE PORTE SENZA PADRI
    for(size_t i = 0; i < circuit->gate_count; i++) {
        if(tempGates[i] != NULL) {
            CMGate_execute(tempGates[i]);
            //check se la porta ha figli (childCount > 0) e in tal caso eseguo le connessuoni
            if(tempGates[i]->childCount > 0){
                for(size_t j = 0; j < circuit->connection_count; j++){
                    if(circuit->connections[j].sourceGate == tempGates[i]){
                        //assegno il valore del sourceWire al destinationWire
                        circuit->connections[j].destinationWire->power = circuit->connections[j].sourceWire->power;
                        circuit->connections[j].destinationGate->fatherCount--;
                        
                        if(circuit->connections[j].destinationGate->fatherCount == 0){
                            CMGate_execute(circuit->connections[j].destinationGate);
                        }
                    }
                }
            }
        }
    }
    return true;
}