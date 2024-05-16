#include "GetEdgesFilePathState.h"
#include "TryAgainState.h"

// Constructor for GetEdgesFilePathState
GetEdgesFilePathState::GetEdgesFilePathState(State* backState, function<void(App*)> nextStateCallback)
        : backState(backState), nextStateCallback(std::move(nextStateCallback)) {}

// Display function to prompt the user to insert the path to the edges file
void GetEdgesFilePathState::display() const {
    cout << "Insert path to the edges file (Ex: \"./dataset/edges.csv\"): ";
}

// Function to handle user input and verify if the file path is valid
void GetEdgesFilePathState::handleInput(App* app) {
    string path;
    getline(cin, path);
    filesystem::path file_path;

    try {

        if (path.front() == '.') {
            // Append the current directory if the input path starts with '.'
            file_path = filesystem::path(filesystem::current_path() / ("." + path));
        }
        else {
            // Otherwise, use the input path as it is
            file_path = filesystem::path(path);
        }

        // Check if the file exists and is not a directory
        if (filesystem::exists(file_path) && !filesystem::is_directory(file_path)) {
            app->setEdgesFilePath(file_path); // Set the nodes file path in the app
            nextStateCallback(app); // Call the callback function to proceed to the next state
        } else {
            // Throw an exception for invalid path
            throw invalid_argument("Invalid path. Please enter a valid file path.");
        }
    } catch (const invalid_argument& e) { // Catch any exceptions thrown

        cout << "\033[31m";
        cout << e.what() << endl; // Display the error message
        cout << "\033[0m";
        app->setState(new TryAgainState(backState, this)); // Transition to TryAgainState

    }
}