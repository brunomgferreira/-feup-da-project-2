#ifndef FEUP_DA_PROJECT_2_GET_STARTING_VERTEX_STATE_H
#define FEUP_DA_PROJECT_2_GET_STARTING_VERTEX_STATE_H


#include <utility>
#include "States/State.h"

/**
* @brief Class that represents a state for obtaining the network files path.
*/

class GetStartingVertexState : public State {
private:
    State* backState;
    function<void(App*, int)> nextStateCallback;
public:

    /**
    * @brief Constructs an instance of GetStartingVertexState with specified back state and callback function.
    *
    * @details This constructor initializes an instance of the GetStartingVertexState class with the given back state and
    * a callback function for transitioning to the next state. The back state represents the state to which the
    * application should return when the user chooses to go back from the current state. The callback function
    * specifies the action to be performed in the next state, usually involving capturing a top number from user
    * input and proceeding to the next state with the captured information.
    *
    * @param backState A pointer to the state to which the application should return when the user chooses to go back.
    * @param nextStateCallback A function defining the action to be performed in the next state, usually involving a top number.
    */
    GetStartingVertexState(State* backState, function<void(App*, int)> nextStateCallback);

    /**
    * @brief Displays a prompt for inserting the id of the starting vertex.
    *
    * @details This method prints a prompt to the console, asking the user to insert the id of the starting vertex.
    * The displayed prompt guides the user on the expected format for entering the id of the starting vertex. The user is
    * expected to input a valid vertex id.
    */
    void display() const override;

    /**
    * @brief Handles user input for obtaining the id of the starting vertex.
    *
    * @details This method reads a line of input from the console, representing the id of the starting vertex.
    * The method validates the entered input, ensuring it is a vertex id.
    * If the input is valid, the callback function is invoked with the captured number of top elements, and the application transitions to the next
    * state accordingly. If the input is invalid, the user is prompted with an error message, and the state transitions to a "Try Again" state,
    * allowing the user to make another attempt.
    *
    * @param app A pointer to the application instance.
    */
    void handleInput(App* app) override;
};


#endif //FEUP_DA_PROJECT_2_GET_STARTING_VERTEX_STATE_H
