/**
 * @file loadbalancer.cpp
 * @brief This file contains the implementation of a simple load balancer.
 */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <chrono> 
#include <sstream>
#include <cstdint>
#include "webserver.h"

/**
 * @brief Writes log entries to a file.
 * 
 * This function writes the log entries stored in the provided vector to a specified file.
 * Each log entry is written to a new line in the file.
 *
 * @param logVector A vector containing the log entries to write.
 * @param filename The name of the file to write the log entries to.
 */
void writeLogToFile(const std::vector<std::string>& logVector, const std::string& filename) {
    std::ofstream outFile(filename, std::ios::app); // Open file in append mode

    if (!outFile.is_open()) {
        std::cerr << "Failed to open log file." << std::endl;
        return;
    }

    for (const auto& logEntry : logVector) {
        outFile << logEntry << std::endl;
    }

    outFile.close();
}

/**
 * @brief Simulates adding new requests to the request queue.
 * 
 * This function adds a new request to the queue at random intervals.
 *
 * @param rq The queue of requests.
 */
void more_requests(std::queue<request> &rq) {
    if(rq.size() % 5 == 0){
        request req;
        rq.push(req);
    }
}

/**
 * @brief Adjusts the number of web servers based on the request-to-server ratio.
 * 
 * This function adds or removes web servers based on the ratio of requests to servers.
 *
 * @param pq The queue of web servers.
 * @param rq The queue of requests.
 */
void more_servers(std::queue<webserver> &pq, std::queue<request> &rq) {
    int ratio = rq.size() / pq.size();
    if(ratio > 90){
        for(int i = 0; i < ratio / 10; i++){ // adds 10% more servers if overwhelmed
            webserver web;
            web.id = pq.size() + 1;
            pq.push(web);
        }
    } else if (ratio < 40) {
        for(int i = 0; i < ratio / 8; i++){ // removes 8% of servers if requests are going down.
            pq.pop();
        }
    }
}

/**
 * @brief Splits a string by a delimiter.
 * 
 * This function splits the given string into tokens separated by the specified delimiter.
 * Each token is converted to an integer and added to the resulting vector.
 *
 * @param str The string to split.
 * @param delimiter The character delimiter to split by.
 * @return A vector of integers obtained from the split string.
 */
std::vector<int> split(const std::string& str, char delimiter) {
    std::vector<int> tokens;
    std::string token;
    std::istringstream tokenStream(str);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(std::stoi(token));
    }
    return tokens;
}

/**
 * @brief Blocks requests from specific IP ranges.
 * 
 * This function checks if a request's IP falls within a specific range and logs it as blocked if it does.
 *
 * @param req The request to check.
 * @param log_vec The vector to store log entries.
 */
void IP_blocker(request req, std::vector<std::string> &log_vec) {
    std::vector<int> tokens = split(req.ip, '.');
    //blocking ip range 200.145.xx.xx
    if(tokens.at(0) == 200 && tokens.at(1) == 145){
        log_vec.push_back("BLOCKED IP: " + req.ip + " REQUEST DISMISSED");
    }
}

/**
 * @brief The main function of the load balancer program.
 * 
 * This function initializes the web servers and request queues, processes requests, 
 * and adjusts the number of web servers based on the load. The program runs until the specified time limit is reached.
 *
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 * @return 0 on successful execution, 1 on error.
 */
int main(int argc, char* argv[]) {
    // argv[0] myprogram
    // argv[1] webservers  
    // argv[2] time-limit
    if(argc < 3){
        std::cerr << "Usage: " << argv[0] << " <webserver count> <time_limit_in_seconds>" << std::endl;
        return 1;
    }
    int server_count = std::stoi(argv[1]);
    int time_limit = std::stoi(argv[2]);

    std::queue<request> requestQueue;
    std::queue<webserver> processQueue;
    std::vector<std::string> log_vector;
    
    // create some webservers, add them to queue
    for(int i = 0; i < server_count; i++){
        webserver web;
        web.id = i;
        processQueue.push(web);
    }

    // Create a full queue of requests, add them to queue
    for(int i = 0; i < server_count * 100; i++){
        request req;
        requestQueue.push(req);
    }

    // Process the requests
    auto start_time = std::chrono::steady_clock::now(); 
    while (true) { 
        if(!processQueue.empty() && !requestQueue.empty() && processQueue.front().available){ 
            // if the webserver queue isn't empty and the first server is ready...
            // will likely be waiting on the available flag
            request front = requestQueue.front();      // take the next request
            IP_blocker(front, log_vector);
            webserver process = processQueue.front(); // and the first available webserver
            log_vector.push_back(process.process_request(front)); // assign the request, and mark in log vector
            
            requestQueue.pop(); // remove request
            processQueue.pop(); // this webserver becomes unavailable           
            processQueue.push(process); // so push it to the back  
            
            more_requests(requestQueue); // check for more requests
            more_servers(processQueue, requestQueue); // check for more servers
        }
        auto current_time = std::chrono::steady_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count();
        if (elapsed_time >= time_limit) {
            std::cout << "Time limit reached, stopping program." << std::endl;
            break;
        }
    }
    writeLogToFile(log_vector, "log.txt");
    
    return 0;
}
