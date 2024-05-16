#include "App.h"
#include "States/MainMenuState.h"

// Initialize the singleton instance to nullptr
App* App::instance = nullptr;

// Constructor
App::App() {
    // Set the current state to the main menu state
    currentState = new MainMenuState();
    // Create a new instance of Data
    data = new Data();
}

// Destructor
App::~App() {
    delete instance; // Delete the singleton instance
}

// Singleton instance getter
App *App::getInstance() {
    if (!instance) {
        instance = new App(); // Create new instance if it doesn't exist
    }
    return instance; // Return the singleton instance
}

// Get the current state
State *App::getState() {
    return currentState; // Return the current state
}

// Set the current state
void App::setState(State* state) {
    currentState = state; // Set the current state to the provided state
}

// Clear data
void App::clearData() {
    delete this->data; // Delete the current data instance
    this->data = new Data(); // Create a new instance of Data
}

// Set data by reading files
void App::setData() {
    try {
        this->data->readFiles(); // Read files to populate data
    } catch (const exception& e) {
        throw e; // Propagate any exceptions
    }
}

// Set file path for edges
void App::setEdgesFilePath(const filesystem::path &file_path) {
    this->data->setEdgesFilePath(file_path); // Set file path for edges in data
}

// Set file path for nodes
void App::setNodesFilePath(const filesystem::path &file_path) {
    this->data->setNodesFilePath(file_path); // Set file path for nodes in data
}

// Display information
void App::display() const {
    // Check if the current state is MainMenuState
    if(typeid(*currentState) == typeid(MainMenuState)) {
        cout << "\033[32m";
        cout << "------------------------------" << endl;
        cout << "\033[0m";
        // Display whether the graph is loaded or not
        cout << "> Loaded Graph?: " << (data->isGraphLoaded() ? "Yes" : ("\033[31mNo\033[30m")) << endl;
    }
    currentState->display(); // Display current state
}

// Handle user input
void App::handleInput() {
    currentState->handleInput(this); // Delegate handling input to current state
}

// Get data instance
Data *App::getData() {
    return data; // Return data instance
}
