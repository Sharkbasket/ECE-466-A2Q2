#ifndef CONSUMER_H
#define CONSUMER_H

#include "systemc.h"
#include "fifo_if.h"
#include <iostream>

SC_MODULE(consumer)
{
    // Ports
    sc_in_clk clk;
    sc_port < fifo_in_if<int> > in;
    
    // Constructor
    consumer(sc_module_name);
    
    // Clocked process
    void eat_numbers();
};

#endif
