//
//  server.c
//  pimediacenter
//
//  Created by Jem Tucker on 03/04/2015.
//  Copyright (c) 2015 Jem Tucker. All rights reserved.
//

#include "server.h"

#define PMC_DEFAULT_PORT "8087"
#define PMC_API_NEWSTATION "/api/newstation"

const char *PMC_LISTENING_PORT = PMC_DEFAULT_PORT;
bool server_running = false;

static int event_handler(struct mg_connection *conn, enum mg_event ev);
void process_post_request(struct mg_connection *conn);
int parse_radio_station_JSON(char *jsontext);
int get_json_from_string(const char *string, char *buffer);

int set_listening_port(char* port) {
    if (server_running) {
        err("Cannot set port, server already initialized.");
        return -1;
    } else {
        dbgf("Setting PMC_LISTENING_PORT to %s.", port);
        PMC_LISTENING_PORT = port;
        return 0;
    }
}

static int event_handler(struct mg_connection *conn, enum mg_event ev) {
    switch (ev) {
        case MG_AUTH: return MG_TRUE;
        case MG_REQUEST:
            // TODO handle POST vs GET
            if (!strcmp(conn->request_method, "POST")) {
                process_post_request(conn);
            }
            
            return MG_TRUE;
        default:
            return MG_FALSE;
    }
}

void process_post_request(struct mg_connection *conn) {
    mg_printf_data(conn, "Processing requested URI [%s] \n", conn->uri);
    dbgf("Recived request to [%s]", conn->uri);
    
    if (!strcmp(conn->uri, PMC_API_NEWSTATION)) {
        printf(conn->content);
        printf("\n");
        char buffer[100];
        parse_radio_station_JSON(conn->content);
    }
    
    
    char url_array[100] = "http:/";
    strcat(url_array, conn->uri);
    
    const char *url = &url_array[0];
    
//    thread_stream_url(url);
    dbg("Success!");
}

int run_server(void) {
    // TODO In another thread?
    struct mg_server *server = mg_create_server(NULL, event_handler);

    dbg("Creating server");
    
    mg_set_option(server, "document_root", ".");
    mg_set_option(server, "listening_port", PMC_LISTENING_PORT);
    
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

int parse_radio_station_JSON(char *jsontext) {
    char *out;
    cJSON *json, *station_url;
    json = cJSON_Parse(jsontext);
    if (!json) {
        dbgf("Error before: [%s]\n", cJSON_GetErrorPtr());
        return -1;
    } else {
        station_url = cJSON_GetObjectItem(json, "uri");
        out = cJSON_Print(station_url);
        cJSON_Delete(json);
        remove_char(out, '"');
        dbgf("Extracted %s\n", out);
        thread_stream_url(out);
        free(out);
        return 0;
    }
}