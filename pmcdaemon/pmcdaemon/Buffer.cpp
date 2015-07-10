//
//  Buffer.cpp
//  pmcdaemon
//
//  Created by Jem Tucker on 23/05/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "Buffer.h"

#include <cstdlib>

#ifndef __pmcdaemon__Buffercpp__
#define __pmcdaemon__Buffercpp__

#define PMC_INIT_BUFFER_LEN 8
#define PMC_BUFFER_EXT 8

template <typename T>
Buffer<T>::Buffer() {
    bufferLength = PMC_INIT_BUFFER_LEN;
    buffer = (T*) malloc(sizeof(T) * bufferLength);
    filledLength = 0;
}

template <typename T>
Buffer<T>::~Buffer<T>() {
    free(buffer);
}

template <typename T>
void Buffer<T>::append(T item) {
    if (bufferLength == filledLength) {
        bufferLength += PMC_BUFFER_EXT;
        buffer = (T*) realloc(buffer, sizeof(T) * bufferLength);
    }
    buffer[filledLength] = item;
    filledLength++;
}

template <typename T>
int Buffer<T>::length() {
    return filledLength;
}

template <typename T>
T Buffer<T>::operator [](int i) {
    return buffer[i];
}

template <typename T>
T* Buffer<T>::getAll() {
    T* retval = (T*) malloc(sizeof(T) * filledLength);
    for (int i = 0; i < filledLength; i++) {
        retval[i] = buffer[i];
    }
    return retval;
}

template <typename T>
T* Buffer<T>::getAll(T last) {
    T* retval = (T*) malloc(sizeof(T) * (filledLength + 1));
    for (int i = 0; i < filledLength; i++) {
        retval[i] = buffer[i];
    }
    retval[filledLength] = last;
    return retval;
}


#endif
