#include "consumer.h"

// Constructor
SC_HAS_PROCESS(consumer);
consumer::consumer(sc_module_name n) : sc_module(n)
{
    SC_CTHREAD(eat_numbers, clk.pos());
}

// Continuously try reading numbers from input port
void consumer::eat_numbers()
{
    int num = 0;
    
    while (true)
    {
        if (in->read(num) == true)
        {
            std::cout << "@" << sc_time_stamp()
                      << ":                " // Whitespace for readability
                      << "R " << num << " (success)" << endl;
        }
        else
        {
            std::cout << "@" << sc_time_stamp()
                      << ":                " // Whitespace for readability
                      << "R " << num << " (failure)" << endl;
        }
        
        wait();
    }
}
