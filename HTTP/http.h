/*
 *  This is a library to aid with using HTTP requests and responses
 *
 */

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Structure for an incoming HTTP request
typedef struct IncomingRequest {
  char* Method;
  char* URI;
  char* Version;
} incoming_t;

typedef struct OutgoingResponse{
  // Response Headers
  char* ContentType;
  char* Version;
  char* Server;
  char* Status;

  // Response Body
  char* Body;
} outgoing_t;

// Frees all information in the Incoming Request
void 
FreeIncomingRequest(incoming_t* req) {
  free(req->Method);
  free(req->URI);
  free(req->Version);
}

incoming_t*
ParseRequest(const char* req) {
  incoming_t* request;

  request = (incoming_t*)malloc(sizeof(incoming_t));

  // Initialize the request strings
  request->Method  = (char*)calloc(1024, sizeof(char));
  request->URI     = (char*)calloc(1024, sizeof(char));
  request->Version = (char*)calloc(1024, sizeof(char));

  strcpy(request->Method, "NULL");
  strcpy(request->URI, "NULL");
  strcpy(request->Version, "NULL");

  // Read the request
  if (sscanf(req, "%s %s %s", request->Method, request->URI, request->Version) != 3) {
    
  }

  return request;
}

// Parse the request URI
// FOR NOW: assume all URI's are requesting a file
// FUTURE: add some sort of REST API, so check if URI is requesting '/api' or something
char*
ParseURI(const char* req_uri) {
  return strdup(req_uri+1); // '/app.css' -> 'app.css'
}


// Create an HTTP response from the information in the 
// Outgoing Request struct
char*
CreateResponse(outgoing_t* resp) {
  char* rv;
  
  rv = (char*)malloc(
      (strlen("HTTP \r\n)
       + strlen(resp->ContentType)+1+4
       + strlen(resp->Version)+1+4
       + strlen(resp->Server)
}

// Frees all information in the Outgoing Response
void 
FreeOutgoingResponse(outgoing_t* resp) {
  free(resp->ContentType);
  free(resp->Version);
  free(resp->Server);
  free(resp->Status);
  free(resp->Body);
}
