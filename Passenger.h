// Only compile this once
#pragma once
// Include iostream for cin and cout
#include <iostream>
// Include STL queue structure
#include <queue>
// Include STL vector structure
#include <vector>
// Include cmath for absolute value
#include <cmath>
// Using namespace std to avoid writing things like std::cout << " Hello World " << endl;
using namespace std;


// Create Passenger class
class Passenger{
    // Declare public member functions
    public:

    // Constructor
    explicit Passenger(int startTime, int startFloor, int endFloor, int travelTime, int waitTime){
        this->startTime = startTime;
        this->startFloor = startFloor;    
        this->endFloor = endFloor;
        this->travelTime = travelTime;
        this->waitTime = waitTime;
    }//end constructor

    // Increase the travel time for the passenger
    void increaseTravel(int increase){
        this->travelTime += increase;
    } //end increaseTravel

    // Return the travel time for the passenger
    int getTravel(){
        return this->travelTime;
    } //end getTravel

    // Return the end floor for the passenger
    int getEndFloor(){
        return this->endFloor;
    } //end getEndFloor

    // Return the start time
    int getStartTime(){
        // Return the start time
        return this->startTime;
    } //end getStartTime

    // Return the start floor
    int getStartFloor(){
        // Return it
        return this->startFloor;
    }//end getStartFloor

    // Return the wait time
    int getWaitTime(){
        // Return it
        return this->waitTime;
    } //end getWaitTime

    // Determine the travel time that the passenger traveled
    int determineTravelTime(int time){
        // Update the passenger's travelTime data
        this->travelTime = (abs(time - this->startTime));
        // Return it
        getTravel();
    } //end determineTravelTime

    // Determine the wait time
    int determineWaitTime(int time){
        // Set the wait time equal to the current time - the time the passenger started waiting
        return (time - this->startTime);
    } //end determineWaitTime

    // Member data
    private:
    int startTime, startFloor, endFloor, travelTime, waitTime;

}; //end passenger
