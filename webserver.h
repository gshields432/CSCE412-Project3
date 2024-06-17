/**
 * @file webserver.h
 * @brief Header file for the WebServer class.
 */

#include "request.h" // Include the request header file
#include <string>     // Include the standard string library

/**
 * @class webserver
 * @brief Represents a web server that can process requests.
 */
class webserver {
public:
    int id;             /**< ID of the web server */
    bool available = true; /**< Availability status of the web server */
    
    /**
     * @brief Process a request on the web server.
     * 
     * This function simulates processing a request by decrementing the request's
     * process time until it reaches zero. It updates the server's availability
     * status accordingly.
     * 
     * @param req Reference to the request object to be processed.
     * @return A string indicating the completion of the request, including the server ID, 
     *         the request's IP address, and the number of cycles taken.
     */
    std::string process_request(request &req);
};


