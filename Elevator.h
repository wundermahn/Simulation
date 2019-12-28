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
// Include the Passenger class
#include "Passenger.h"
// Using namespace std to avoid writing things like std::cout << " Hello World " << endl;
using namespace std;

// Elevator Class
class Elevator{

    // Public member data
    public:
    // Constructor
    explicit Elevator(string name){
        status = "STOPPED";
        passengerCount = 0;
        this->name = name;
        currentLocation = 0;
    }//end constructor

    // Return the name of the elevator
    string getName(){
        return name;
    } //end getName

    // UTILITY

    // Simulates the drop off of a passenger
    void dropoffPassenger(){
        // Changes the passenger count
        changePassengerCount(-1);
        // Pops the 
        this->stops.pop();
        // Removes the passenger
        this->passengers.pop();
    } //end drop of

    // Utility function to print the stops queue
    void printQueue(){
        //NOTE - Influenced by: https://www.includehelp.com/stl/print-all-elements-of-a-queue.aspx

        // Create a copy of the queue
        queue<int> copy = this->stops;

        // Check to see if queue is empty
        if(copy.size() == 0){
            // Print out if it was
            cout << " Queue is empty. " << endl;
        } //end if

        // While its not empty
        while(!copy.empty()){
            // Print out the top element
            cout << copy.front() << " ";
            // Pop off the top element
            copy.pop();
        } //end while

        // New line
        cout << endl;
    }//end printQueue

    // This function adds a passenger to the elevator
    void addPassenger(int time, Passenger curr){
        // Add a stop for wherever this passenger is trying to go
        addStop(curr.getEndFloor());
        // Change how many people are on the elevator
        changePassengerCount(1);
        // Add the person
        addNewPassenger(curr);
    } //end addPassenger
    
    // Utility function to check to see if someone else can get on the elevator
    bool checkCount(){
        // If there are more than 8 people
        if (this->passengerCount > 8){
            // Return false
            return false;
        // Otherwise, they can get on
        }else{
            // Return true
            return true;
        } //endif else
    } //end checkCount

    // Utility function to see who the next passenger is
    Passenger checkNextPassenger(){
        // Return the top passenger in the queue
        return this->passengers.front();
    }//end checkNextPassenger
    // UTILITY

    // PASSENGER COUNT
    // Function to change the count of passengers
    void changePassengerCount(int change){
        // Change this elevator's passenger count
        this->passengerCount += change;
    }//end changePassengerCount

    // Function to return the passenger count
    int getPassengerCount(){
        // Return it
        return this->passengerCount;
    }//end getPassengerCount
    // PASSENGER COUNT    

    // STATUS
    // This function returns the status of the elevator
    string getStatus(){
        // Return it
        return this->status;
    } // end getStatus

    // This function sets the status of the elevator
    void setStatus(string status){
        // Set it
        this->status = status;
    } //end setStatus
    // STATUS

    // STOPS
    // This function adds a stop to the queue
    void addStop(int location){
        // Add a new location to the list of stops to make
        this->stops.push(location);
    } //end addStop

    // This function gets the size of the stops to make queue
    int getStops(){
        // Return the size
        return this->stops.size();
    } //end getStops

    // This function determines the next stop (by floor number) the elevator will be making
    int getRoute(){
        // If there are no stops to make, return 0
        if(this->stops.size() == 0){
            return 0;
        // Otherwise...
        }else{
            // Return the next step
            return this->stops.front();   
        } //end else
    } //end getRoute
    // STOPS

    // PASSENGERS
    // Function to add a new passenger
    void addNewPassenger(Passenger newPass){
        // Push a new passenger into the queue
        this->passengers.push(newPass);
    }//end addNewPassenger
    // PASSENGERS

    // LOCATION
    // Function to set a new location for the elevator to go
    void setLocation(int location){
        // Set the current elevator's location
        this->currentLocation = location;
    } // end setLocation

    // Function to return the location of the elevator
    int getLocation(){
        // Return it
        return this->currentLocation;
    } //end getLocation
    // LOCATION

    // Declare private member data
    private:
    string status;
    int passengerCount;
    queue<int> stops;
    queue<Passenger> passengers;
    string name;
    int currentLocation;

}; //end passenger
