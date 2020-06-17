#include "producer.h"

// Constructor
SC_HAS_PROCESS(producer);
producer::producer(sc_module_name n) : sc_module(n)
{
    SC_THREAD(spit_numbers);
    sensitive << clk.pos();
    dont_initialize();
}

// Continuously try writing numbers to output port
void producer::spit_numbers()
{
    int num = 0;
    
    while (true)
    {
        wait();
        if (out->write(num) == true)
        {
            std::cout << "@" << sc_time_stamp()
                      << ": Write value " << num << " (success)" << endl;
        }
        else
        {
            std::cout << "@" << sc_time_stamp()
                      << ": Write value " << num << " (failure)" << endl;
        }
        
        num = (num + 1) % 10;
    }
}
