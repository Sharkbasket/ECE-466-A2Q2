#include "consumer.h"

// Constructor
SC_HAS_PROCESS(consumer);
consumer::consumer(sc_module_name n) : sc_module(n)
{
    SC_THREAD(eat_numbers);
    sensitive << clk.pos();
    dont_initialize();
}

// Continuously try reading numbers from input port
void consumer::eat_numbers()
{
    int num = 0;
    
    while (true)
    {
        wait();
        if (in->read(num) == true)
        {
            std::cout << "@" << sc_time_stamp()
                      << ":                          " // For readability
                      << "Read value " << num << " (success)" << endl;
        }
        else
        {
            std::cout << "@" << sc_time_stamp()
                      << ":                          " // For readability
                      << "Read failed" << endl;
        }
    }
}
