/**
 * @file webserver.cpp
 * @brief Implementation file for the WebServer class.
 */

#include "webserver.h"

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
std::string webserver::process_request(request &req) {
    this->available = false; // Mark the server as unavailable during processing
    int copy = req.process_time; // Store the initial process time for logging

    // Simulate processing the request by decrementing its process time
    while (req.process_time > 0) {
        req.process_time--; // Decrement the process time (simulated processing)
    }

    this->available = true; // Mark the server as available again after processing

    // Construct and return a completion message including server ID, request IP, and process cycles
    return "completed request (ID: " + std::to_string(this->id) + "): " +
           req.ip + " in " + std::to_string(copy) + " cycles";
}
