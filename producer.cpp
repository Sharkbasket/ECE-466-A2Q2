#include "producer.h"

// Constructor
SC_HAS_PROCESS(producer);
producer::producer(sc_module_name n) : sc_module(n)
{
    SC_CTHREAD(spit_numbers, clk.pos());
}

// Continuously try writing numbers to output port
void producer::spit_numbers()
{
    int num = 0;
    
    while (true)
    {
        if (out->write(num) == true)
        {
            std::cout << "@" << sc_time_stamp()
                      << ": W " << num << " (success)" << endl;
        }
        else
        {
            std::cout << "@" << sc_time_stamp()
                      << ": W " << num << " (failure)" << endl;
        }
        
        num = (num + 1) % 10;
        wait();
    }
}
