#include "fifo.h"

// Constructor
template<class T>
fifo<T>::fifo(sc_module_name name, const unsigned int N)
: sc_module(name), size(N), free(N), read_flag(false), write_flag(false),
  read_success(false), write_success(false), r_index(0), w_index(0),
  read_storage(NULL), write_storage(0)
{
    buffer = new T[size];
    
    SC_THREAD(arbitrator);
    sensitive << read_req << write_req;
}

// Destructor
template<class T>
fifo<T>::~fifo()
{
    delete[] buffer;
}

template<class T>
bool fifo<T>::read(T& read_ref)
{
    read_flag = true;
    read_storage = &read_ref;
    read_req.notify();
    wait(done);
    return read_success;
}

template<class T>
bool fifo<T>::write(T write_value)
{
    write_flag = true;
    write_storage = write_value;
    write_req.notify();
    wait(done);
    return write_success;
}

template<class T>
void fifo<T>::arbitrator()
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
