// Include iostream for things like cout and cin
#include <iostream>
// Include fstream for reading in a file
#include <fstream>
// Include string for things like .compare
#include <string>
// Include the STL vector structure
#include <vector>
// Include sstream for reading in a file
#include <sstream>
// Include cmath for absolute value
#include <cmath>
// Elevator Class
#include "Elevator.h"
// Floor Class
#include "Floor.h"
// Use namespace std to avoid writing things like std::cout << " Hello World " << std::endl;
using namespace std;

// Global variable for thetime
int time = 0;

// Function to change the time
void changeTime(int curr, int future){
    // Take the time variable plus how long it will take to navigate to the floor from the
    // current location
    time += abs((curr - future) * 10);
} //end changeTime

// Function to calculate the average travel time
int calculateAverage(vector<int> times){
    // NOTE -- Influenced by: https://stackoverflow.com/questions/36016484/calculating-average-of-a-vector-with-a-for-loop-c    
    // Variable to hold the total count
    int total;

    // Loop through the times
    for(unsigned int i = 0; i < times.size(); i++){
        // Add to the total
        total += times[i];
    } //end for

    // Return the average
    return total / times.size();
} //end calculateAverage

// main function
int main(){
    // Declare a vector of Passengers
    vector<Passenger> passengers;
    // Create four elevator objects
    Elevator elevatorOne = Elevator("elevatorOne");
    Elevator elevatorTwo = Elevator("elevatorTwo");
    Elevator elevatorThree = Elevator("elevatorThree");
    Elevator elevatorFour = Elevator("elevatorFour");
    // Declare a vector to hold the elevators
    vector<Elevator> elevators;
    // Fill the vector
    elevators.push_back(elevatorOne);
    elevators.push_back(elevatorTwo);
    elevators.push_back(elevatorThree);
    elevators.push_back(elevatorFour);

    // Declare a vector of travel times
    vector<int> travelTimes;

    // Declare a vector of wait times
    vector<int> waitTimes;

    // Read in the file
    ifstream ifile("D:\\Grad School\\Fall 2019\\EN.605.604.81.FA19 - OO Programming with C++\\Project 7\\hello.csv"); 
    // Read the file in as a string

    //NOTE - Edited from this code: https://stackoverflow.com/questions/1120140/how-can-i-read-and-parse-csv-files-in-c

    string line; // we read the full line here
    while (getline(ifile, line)){ // read the current line
        istringstream iss{line}; // construct a string stream from line
        // read the tokens from current line separated by comma
        vector<string> tokens; // here we store the tokens
        string token; // current token
        while (getline(iss, token, ',')){
            tokens.push_back(token); // add the token to the vector
        }
        // map the tokens into our variables, this applies to your scenario
        int startTime = stoi(tokens[0]); // convert to int
        int startFloor = stoi(tokens[1]); // second is an int, convert it
        int endFloor = stoi(tokens[2]); // same for third

        // Create a new floor
        Floor newFloor = Floor(endFloor);

        // Create a passenger object, and add it to the pasengers vector
        Passenger curr = Passenger(startTime, startFloor, endFloor, 0, 0);
        // Add the new passenger created from the csv file
        passengers.push_back(curr);

    } //end while reading the file

    // Pickup passengers
    for(unsigned int i = 0; i < passengers.size(); i++){
        // Loop through elevators
        for (int j = 0; j < elevators.size(); j++){
            // Increment time by 1 second
            time += 1;

            // If the elevator hasn't moved for the first time
            if(elevators[j].getStatus().compare("STOPPED") == 0 && elevators[j].getStops() == 0 && elevators[j].checkCount() == true){                
                // Add the passenger to the elevator
                elevators[j].addPassenger(time, passengers[i]);

                // Determine the passenger's wait time
                waitTimes.push_back(passengers[i].determineWaitTime(time));

                // If the elevator's current destination is higher than its current location
                if(elevators[j].getRoute() > elevators[j].getLocation()){
                    // Move up
                    elevators[j].setStatus("MOVING UP");
                // If the elevator's current destination is lowerr than its current location
                }else if (elevators[j].getRoute() < elevators[j].getLocation()){
                    // Move down
                    elevators[j].setStatus("MOVING DOWN");
                }else{
                    // Otherwise, its there, so set it to stopping
                    elevators[j].setStatus("STOPPING");
                } //end else

                break;                     
            } //end if
            
            // If the elevator is stopped
            else if (elevators[j].getStatus() == "STOPPED"  && elevators[j].checkCount() == true && passengers[i].getStartTime() <= time){
                // Add the passenger to the elevator
                elevators[j].addPassenger(time, passengers[i]);

                // Determine the passenger's wait time
                waitTimes.push_back(passengers[i].getWaitTime());

                // If the elevator's current destination is higher than its current location
                if(elevators[j].getRoute() > elevators[j].getLocation()){
                    // Move up
                    elevators[j].setStatus("MOVING UP");
                // If the elevator's current destination is lowerr than its current location
                }else if (elevators[j].getRoute() < elevators[j].getLocation()){
                    // Move down
                    elevators[j].setStatus("MOVING DOWN");
                }else{
                    // Otherwise, its there, so set it to stopping
                    elevators[j].setStatus("STOPPING");
                } //end else
                
                break;                     
            } //end if
            
            else{
                // If none of these conditions match, move on to the next elevator
                continue;
            } //end else
        } //end looping through elevators for pickup


        // Now, decide when to drop off passengers
        for(int k = 0; k < elevators.size(); k++){
            // Update the time
            time += 1;

            // If the elevator is about to stop
            if(elevators[k].getStatus().compare("STOPPING") == 0){
                // Increase the time
                time += 2;
                // Stop it 
                elevators[k].setStatus("STOPPED");
                // Add the passenger to be dropped off's travel time
                Passenger current = elevators[k].checkNextPassenger();
                // Add that passenger's travel time to the vector
                travelTimes.push_back(current.determineTravelTime(time));
                // Drop off the passenger
                elevators[k].dropoffPassenger();
                break;
                
                // Otherwise, if its still moving
            } else if(elevators[k].getStatus().compare("MOVING UP") == 0 || elevators[k].getStatus().compare("MOVING DOWN") == 0){
                // Calculate the time to move floors
                changeTime(elevators[k].getLocation(), elevators[k].getRoute());
                // Set location to where you are going
                elevators[k].setLocation(elevators[k].getRoute());
                // Update status
                elevators[k].setStatus("STOPPING");                              
                break;
            }else{
                // This is an error, and shouldn't happen
                // A WEAK form of exception catching
                cout << " Somehow in else " << endl;
                break;
            } //end else
        } //end dropoff sequence
    } //end looping through passengers

    // For testing purposes, loop through each elevator and ensure that they are empty
    // i.e., every passenger has been dropped off
    for(int x = 0; x < elevators.size(); x++){
        // Evaluate the elevator
        cout << " Evaluating Elevator: " << elevators[x].getName() << endl;
        // Print its queue
        elevators[x].printQueue();
    } //end for

    cout << " The Average Travel Time is: " << calculateAverage(travelTimes) << endl;
    cout << " The Average Wait Time is: " << calculateAverage(waitTimes) << endl;
} //end main