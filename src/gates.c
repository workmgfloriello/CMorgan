#include "gates.h"

void AND(CMWire *inputs, CMWire *outputs) {
    outputs[0].power = inputs[0].power && inputs[1].power;
}

void OR(CMWire *inputs, CMWire *outputs) {
    outputs[0].power = inputs[0].power || inputs[1].power;
}

void NOT(CMWire *inputs, CMWire *outputs) {
    outputs[0].power = !inputs[0].power;
}