#ifndef CMORGAN_CIRCUIT_H
#define CMORGAN_CIRCUIT_H

#include <stdbool.h>
#include <stddef.h>
#include "basegate.h"

// Collegamento tra due porte logiche
typedef struct CMConnection {
    CMGate *sourceGate;
    CMWire *sourceWire;

    CMGate *destinationGate;
    CMWire *destinationWire;
} CMConnection;

// Struttura del circuito
typedef struct {
    CMGate **gates;
    size_t gate_count;
    size_t gate_capacity;

    CMConnection *connections;
    size_t connection_count;
    size_t connection_capacity;

} CMCircuit;

// Creazione e distruzione
CMCircuit *CMCircuit_create(void);
bool CMCircuit_destroy(CMCircuit *circuit);

// Gestione porte
bool CMCircuit_addGate(CMCircuit *circuit, CMGate *gate);
bool CMCircuit_removeGate(CMCircuit *circuit, CMGate *gate);
bool CMCircuit_containsGate(CMCircuit *circuit, CMGate *gate);

// Collegamento porte
bool CMCircuit_connect(
    CMCircuit *circuit,
    CMGate *sourceGate,
    CMWire *sourceWire,
    CMGate *destinationGate,
    CMWire *destinationWire
);

// Esecuzione circuito
bool CMCircuit_execute(CMCircuit *circuit);

#endif
