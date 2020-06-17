#ifndef PRODUCER_H
#define PRODUCER_H

#include "systemc.h"
#include "fifo_if.h"
#include <iostream>

SC_MODULE(producer)
{
    // Ports
    sc_in_clk clk;
    sc_port < fifo_out_if<int> > out;
    
    // Constructor
    producer(sc_module_name);
    
    // Clocked process
    void spit_numbers();
};

#endif
