#!/bin/bash
set -e
g++ main_parse.cpp objs/component.cpp objs/diode.cpp objs/capacitor.cpp objs/inductor.cpp objs/resistor.cpp objs/i_source.cpp objs/v_source.cpp objs/nodes.cpp circuit.cpp objs/utils.cpp -o circuitSim -fno-math-errno
