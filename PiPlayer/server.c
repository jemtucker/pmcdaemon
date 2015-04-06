//
//  server.c
//  PiPlayer
//
//  Created by Jem Tucker on 03/04/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "server.h"
#define PI_DEFAULT_PORT "8087"

char *PI_LISTENING_PORT = PI_DEFAULT_PORT;
bool server_running = false;

static int event_handler(struct mg_connection *conn, enum mg_event ev);
void process_request(struct mg_connection *conn);

int set_listening_port(char* port) {
    if (server_running) {
        err("Cannot set port, server already initialized.");
        return -1;
    } else {
        dbgf("Setting PI_LISTENING_PORT to %s.", port);
        PI_LISTENING_PORT = port;
        return 0;
    }
}

static int event_handler(struct mg_connection *conn, enum mg_event ev) {
    switch (ev) {
        case MG_AUTH: return MG_TRUE;
        case MG_REQUEST:
            process_request(conn);
            return MG_TRUE;
        default:
            return MG_FALSE;
    }
}

void process_request(struct mg_connection *conn) {
    mg_printf_data(conn, "Processing requested URI [%s] \n", conn->uri);
    dbgf("Recived request to [%s]", conn->uri);
    
    char url_array[100] = "http:/";
    strcat(url_array, conn->uri);
    
    const char *url = &url_array[0];
    
    thread_stream_url(url);
    dbg("Success!");
}

int run_server(void) {
    // TODO In another thread?
    struct mg_server *server = mg_create_server(NULL, event_handler);

    dbg("Creating server");
    
    mg_set_option(server, "document_root", ".");
    mg_set_option(server, "listening_port", PI_LISTENING_PORT);
    
    const char *port = mg_get_option(server, "listening_port");
    const char *root = mg_get_option(server, "document_root");
    
    dbg("Initialising the server connection");
    dbgf("Serving %s on port %s", root, port);
    
    server_running = true;
    
    for (;;) {
        mg_poll_server(server, 1000);
    }
    
    mg_destroy_server(&server);
    return 0;
}