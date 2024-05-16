#include "TryAgainState.h"
#include "States/MainMenuState.h"

// Constructor for TryAgainState
TryAgainState::TryAgainState(State *backState, State* currentState)
        : backState(backState), currentState(currentState) {}

// Display function to print the try again options
void TryAgainState::display() const {
    cout << "\033[31m";
    cout << "----------------" << endl;
    cout << "\033[0m";
    cout << "  1. Try Again" << endl;
    cout << "  b. Go back" << endl;
    cout << "  q. Main Menu" << endl;
    cout << "\033[31m";
    cout << "----------------" << endl;
    cout << "\033[0m";
    cout << "Enter your choice: ";
}

// Function to handle user input and navigate through different states
void TryAgainState::handleInput(App* app) {
    string choice;
    cin >> choice;

    if (choice.size() == 1) { // Check if input is a single character
        switch (choice[0]) {
            case '1':
                // Transition to the current state
                app->setState(currentState);
                break;
            case 'b':
                // Transition to the previous state
                app->setState(backState);
                break;
            case 'q':
                // Transition to the main menu
                app->setState(new MainMenuState());
                break;
            default:
                // Display error message for invalid choice
                cout << "\033[31m";
                cout << "Invalid choice." << endl;
                cout << "\033[0m";
        }
    } else {
        // Display error message for invalid input
        cout << "\033[31m";
        cout << "Invalid input. Please enter a single character." << endl;
        cout << "\033[0m";
    }
    cin.ignore();
}