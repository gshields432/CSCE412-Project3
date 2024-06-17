/**
 * @file request.h
 * @brief Header file for the request class.
 */

#include <iostream> 
#include <string>

using namespace std;

/**
 * @brief The request class represents a request with an IP address and a processing time.
 */
class request {
public:
    string ip; /**< The IP address associated with the request. */
    int process_time; /**< The processing time required for the request. */

    /**
     * @brief Default constructor for the request class.
     * 
     * Initializes a request object with default values.
     */
    request();
};
