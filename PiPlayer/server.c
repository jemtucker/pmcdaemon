//
//  server.c
//  PiPlayer
//
//  Created by Jem Tucker on 03/04/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "server.h"

static int event_handler(struct mg_connection *conn, enum mg_event ev) {
    switch (ev) {
        case MG_AUTH: return MG_TRUE;
        case MG_REQUEST:
            mg_printf_data(conn, "Hello! Requested URI is [%s]", conn->uri);
            return MG_TRUE;
            
        default:
            return MG_FALSE;
    }
}

int run_server(void) {
    struct mg_server *server = mg_create_server(NULL, event_handler);

    dbg("Creating server");
    
    mg_set_option(server, "document_root", ".");
    mg_set_option(server, "listening_port", "8087");
    
    const char *port = mg_get_option(server, "listening_port");
    const char *root = mg_get_option(server, "document_root");
    
    dbg("Initialising the server connection");
    dbgf("Serving %s on port %s", root, port);
    
    for (;;) {
        mg_poll_server(server, 1000);
    }
    
    mg_destroy_server(&server);
    return 0;
}