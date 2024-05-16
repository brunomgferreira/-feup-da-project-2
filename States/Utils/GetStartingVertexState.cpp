#include "GetStartingVertexState.h"
#include "TryAgainState.h"

// Constructor for GetStartingVertexState
GetStartingVertexState::GetStartingVertexState(State* backState, function<void(App*, int)> nextStateCallback)
        : backState(backState), nextStateCallback(std::move(nextStateCallback)) {}

// Display function to prompt the user to insert starting vertex id
void GetStartingVertexState::display() const {
    cout << "Insert starting vertex id (Ex: 0): ";
}

// Function to handle user input and verify if the vertex exists
void GetStartingVertexState::handleInput(App* app) {
    int id;
    std::cin.ignore();
    std::cin >> id;

    bool vertexExists = app->getData()->vertexExists(id); // Check if the vertex exists

    if (vertexExists) {
        nextStateCallback(app, id); // Call the callback function with the app and id
    } else {
        cout << "\033[31m";
        cout << "Vertex does not exist." << endl; // Display error messages
        cout << "\033[0m";
        app->setState(new TryAgainState(backState, this)); // Transition to TryAgainState
    }
}
