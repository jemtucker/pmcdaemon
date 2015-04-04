//
//  audio.c
//  PiPlayer
//
//  Created by Jem Tucker on 04/04/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "pp_audio.h"

#define PP_PATH "/Users/Jem/workspace/song.mp3"
#define BITS 8

int pp_test(void) {
    // Declarations
    mpg123_handle *handle;
    unsigned char *buffer;
    size_t buffer_size;
    size_t done;
    int err;
    
    int driver;
    
    ao_device *device;
    ao_sample_format format;
    int channels, encoding;
    long rate;
    
    // Initialisations
    ao_initialize();
    driver = ao_default_driver_id();
    mpg123_init();
    handle = mpg123_new(NULL, &err);
    buffer_size = mpg123_outblock(handle);
    buffer = malloc(buffer_size * sizeof(unsigned char));
    
    // Open file and get decoding
    mpg123_open(handle, PP_PATH);
    mpg123_getformat(handle, &rate, &channels, &encoding);
    
    // Set output format
    format.bits     = mpg123_encsize(encoding) * BITS;
    format.rate     = rate;
    format.channels = channels;
    format.byte_format = AO_FMT_NATIVE;
    format.matrix = 0;
    device = ao_open_live(driver, &format, NULL);
    
    // Decode and play
    while (mpg123_read(handle, buffer, buffer_size, &done) == MPG123_OK) {
        ao_play(device, buffer, done);
    }
    
    // Cleanup
    free(buffer);
    ao_close(device);
    mpg123_close(handle);
    mpg123_delete(handle);
    mpg123_exit();
    ao_shutdown();
    
    return 0;
}