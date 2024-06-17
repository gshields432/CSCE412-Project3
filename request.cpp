/**
 * @file request.cpp
 * @brief request file for the load balancer simulation.
 */

#include <iostream> 
#include <string>
#include <random>
#include <cstdlib>
#include <ctime>
#include "request.h"

using namespace std;

/**
 * @brief Generates a random IP address string.
 * 
 * This function generates a random IP address by generating four octets,
 * each ranging from 0 to 255, and constructs the IP address string.
 * 
 * @return A string representing a random IP address (e.g., "192.168.1.10").
 */
std::string generate_random_ip() {
    // Ensure the random number generator is initialized
    std::random_device rd;
    std::srand(rd());

    // Generate four octets and construct the IP address string
    std::string ip_address = "" + std::to_string(std::rand() % 256) + "." +
                             std::to_string(std::rand() % 256) + "." +
                             std::to_string(std::rand() % 256) + "." +
                             std::to_string(std::rand() % 256);
    return ip_address;
}

/**
 * @brief Default constructor for the request class.
 * 
 * Initializes a request object with a random IP address and a random processing time.
 * The IP address is generated using generate_random_ip() function, and the processing
 * time is a random integer between 1 and 50.
 */
request::request() {
    this->ip = generate_random_ip(); // Initialize IP address with a random value
    this->process_time = std::rand() % 49 + 1; // Initialize process time with a random value between 1 and 50
}
