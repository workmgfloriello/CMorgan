#include <stdio.h>
#include "../include/cmorgan.h"

int main(){
    CMWire input[2] = {{.power = false, name : "A"}, {.power = true, name : "B"}};
    CMWire output[1] = {{.power=false, .name="X"}};

    CMWire orInput[2] = {{.power = 0, .name="C"},{.power = false, .name="X1"}};
    CMWire orOutput[1] = {{.power=false, .name="X"}};

    CMWire notInput[1] = {{.power = 0, .name="D"}};
    CMWire notOutput[1] = {{.power = 0, .name="X2"}};

    CMGate *and = CMGate_create("AND",2,input,output, AND);
    CMGate *or = CMGate_create("OR", 2, orInput, orOutput, OR);
    CMGate *not = CMGate_create("NOT" ,1, notInput,notOutput,NOT);

    //Assegno var
    CMGate_connect(and, &output[0], or, &orInput[1]);
    CMGate_connect(or,&orOutput[0],not,&notInput[0]);

    CMGate_execute(and);

    printf("RES: %d\n",or->outputs[0].power);
}
