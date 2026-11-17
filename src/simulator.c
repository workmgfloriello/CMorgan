#include <stdlib.h>
#include <stdio.h>
#include "basegate.h"

int n = 0;             
int capacita = 1;      
CMGate **gates = NULL; 

// Funzione per inizializzare l'array (da chiamare all'inizio del main)
void initGates() {
   gates = malloc(capacita * sizeof(CMGate *));
    if (gates == NULL) {
        printf("Errore di allocazione!\n");
        exit(1);
    }
}

bool addGate(CMGate *gate) {
    // Se l'array non è ancora stato allocato
    if (gates == NULL) {
        initGates();
    }

    if(n>=capacita){
        capacita *= 2;
        CMGate **temp = realloc(gates,capacita * sizeof(CMGate *));

         if (temp == NULL) {
            printf("Errore nel ridimensionamento!\n");
            return false;
        }

        gates = temp;
    }


    gates[n] = gate;
    n++;
    return true;
}

bool removeGate(CMGate *gate){
    int removeIndex = -1;

    for(int i=0; i<n; i++){
        if(gates[i] == gate){
            free(gate);
            removeIndex = i;
            break;
        }
    }
    
    //SHIFTING
    if(removeIndex != -1){
        for(int i=removeIndex; i<n-1; i++){
            gates[i] = gates[i+1];
        }
    }else{
    return false;
    }

    removeIndex = -1;
    n--;
    gates[n] = NULL;
    return true;
}

bool executeGate(CMGate *gate){
    if (gate == NULL || gate->execute == NULL) {
    return false;
    }

    //FUNZIONE PASSATA AL GATE NELL MAIN
    
    //Controlo trammite il count se ci sono figli
    if(gate->childCount > 0){
        //Se ci sono eseguo in ordine gate->nextGate
        CMGate *current = gate;
        CMGate *next = NULL;

        for (int i = 0; i < current->childCount; i++)
        {
            current->execute(current->inputs,current->outputs);

            next = current->nextGate;

            next->execute(next->inputs, next->outputs);

            if(next->childCount > 0){
                executeGate(next);
            };
        }
        return true;
    }else{
      //Se non ci sono eseguo solo il gate principale
        gate->execute(gate->inputs,gate->outputs);
        return true;
    }
    
}