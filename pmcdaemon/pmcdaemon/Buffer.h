//
//  Buffer.h
//  pmcdaemon
//
//  Created by Jem Tucker on 23/05/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#ifndef __pmcdaemon__Buffer__
#define __pmcdaemon__Buffer__

#include <stdio.h>

template <typename T>

class Buffer {
    T* buffer;
    int bufferLength;
    int filledLength;
    
public:
    Buffer();
    ~Buffer();
    T* getAll();
    T* getAll(T);
    void append(T);
    int length();
    T operator [](int);
};

#include "Buffer.cpp"
#endif /* defined(__pmcdaemon__Buffer__) */
