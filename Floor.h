// Only compile once
#pragma once
// Floor Class
class Floor{

    // Public member data
    public:
    // Constructor
    explicit Floor(int value){
        this->value = value;
    }//end constructor

    // Function to get the floors value
    int getFloorVal(){
        // Return it
        return this->value;
    } //end getFloorVal

    // Function to set the floor's value
    void setFloorVal(int value){
        // Set it
        this->value = value;
    } //end setFloorVal

    // Private member data
    private:
    int value;

}; // end floor