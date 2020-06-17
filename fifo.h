#ifndef FIFO_H
#define FIFO_H

#include "systemc.h"
#include "fifo_if.h"

// Definition of a FIFO hierarchical channel
template<class T>
class fifo : public sc_module, public fifo_in_if<T>, public fifo_out_if<T>
{
    public:
        // Constructor
        SC_HAS_PROCESS(fifo);
        fifo(sc_module_name name, const unsigned int N)
        : sc_module(name), size(N), free(N), read_flag(false),
          write_flag(false), read_success(false), write_success(false),
          r_index(0), w_index(0), read_storage(NULL), write_storage(0)
        {
            buffer = new T[size];
            
            SC_THREAD(arbitrator);
            sensitive << read_req << write_req;
        }
        
        // Destructor
        ~fifo()
        {
            delete[] buffer;
        }
        
        bool read(T& read_ref)
        {
            read_flag = true;
            read_storage = &read_ref;
            read_req.notify();
            wait(done);
            return read_success;
        }
        
        bool write(T write_value)
        {
            write_flag = true;
            write_storage = write_value;
            write_req.notify();
            wait(done);
            return write_success;
        }
        
    private:
        // Arbitrator thread to deal with concurrent read/write requests
        void arbitrator()
        {
            while (true)
            {
                // Read has higher priority, so it gets checked first
                if (read_flag == true)
                {
                    read_flag = false;
                    if (free == size)
                    {
                        // Nothing to read
                        read_success = false;
                    }
                    else
                    {
                        *read_storage = buffer[r_index];
                        r_index = (r_index + 1) % size;
                        free++;
                        read_success = true;
                    }
                }
                
                // Write has lower priority, so it gets checked second
                if (write_flag == true)
                {
                    write_flag = false;
                    if (free == 0)
                    {
                        // No space to write
                        write_success = false;
                    }
                    else
                    {
                        buffer[w_index] = write_storage;
                        w_index = (w_index + 1) % size;
                        free--;
                        write_success = true;
                    }
                }
                
                done.notify();
                wait();
            }
        }
        
        // Private data members
        bool read_flag, write_flag, read_success, write_success;
        const unsigned int size;
        sc_event read_req, write_req, done;
        T write_storage;
        T* read_storage;
        T* buffer;
        unsigned int free, r_index, w_index;
};

#endif
