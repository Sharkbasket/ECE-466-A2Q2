#include "systemc.h"
#include "producer.h"
#include "consumer.h"
#include "fifo.h"

int sc_main(int argc, char* argv[])
{
    // Channel instantiation
    sc_clock fast_clock("fast_clock", 10.0, SC_NS);
    sc_clock slow_clock("slow_clock", 20.0, SC_NS);
    fifo<int> my_fifo("my_fifo", 4);
    
    // Module instantiation & interconnection
    producer my_producer("my_producer");
    my_producer.clk(fast_clock);
    my_producer.out(my_fifo);
    
    consumer my_consumer("my_consumer");
    my_consumer.clk(slow_clock);
    my_consumer.in(my_fifo);
    
    sc_start(1000, SC_NS);
    
    return 0;
}
