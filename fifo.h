#ifndef FIFO_H
#define FIFO_H

#include "systemc.h"
#include "fifo_if.h"    

// Declaration of a FIFO hierarchical channel
template <class T> class fifo
: public sc_module, public fifo_in_if <T>, public fifo_out_if <T>
{
    public:
        // Constructor
        fifo(sc_module_name, const unsigned int);
        
        // Destructor
        ~fifo();
        
    private:
        // Arbitrator thread to deal with concurrent read/write requests
        void arbitrator();
        
        // Private data members
        bool read_flag, write_flag, read_success, write_success;
        const unsigned int size;
        sc_event read_req, write_req, done;
        T write_storage;
        T* read_storage;
        T* buffer;
        unsigned int free, r_index, w_index;
}

#endif
