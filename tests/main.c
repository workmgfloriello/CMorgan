#include <stdio.h>
#include "../include/cmorgan.h"

int main(){
    CMWire input[2] = {{.power = false, .name = "A"}, {.power = true, .name = "B"}};
    CMWire output[1] = {{.power=false, .name="X"}};

    CMWire orInput[2] = {{.power = 0, .name="C"},{.power = true, .name="X1"}};
    CMWire orOutput[1] = {{.power=false, .name="X"}};

    CMGate *and = CMGate_create("AND",2,input,output, AND);
    CMGate *or = CMGate_create("OR", 2, orInput, orOutput, OR);


    //Assegno var
    orInput[0].power = and->outputs[0].power;


    CMGate_execute(and);
    CMGate_execute(or);

    printf("RES: %d\n",or->outputs[0].power);
}
