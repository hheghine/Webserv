#ifndef REQUEST_H
#define REQUEST_H

#include "Client.h"

#define REQUEST_DEFAULT_STATE_CODE 200
#define REQUEST_DEFAULT_HEADER_TIMEOUT 10
#define REQUEST_DEFAULT_BODY_TIMEOUT 3600
#define REQUEST_DEFAULT_UPLOAD_STATE "./www/upload"

class Request
{
public:
    Request(Client* client);
    Request(const Request& other);
};

#endif // REQUEST_H