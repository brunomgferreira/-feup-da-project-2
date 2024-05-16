#ifndef FEUP_DA_PROJECT_2_APP_H
#define FEUP_DA_PROJECT_2_APP_H

#include "Data.h"

class State;

/**
* @brief Singleton class representing the main application controller for the water supply analysis system.
*/

class App {
private:
    static App* instance;
    State* currentState;
    Data* data;

    /**
    * @brief Constructor for the App class.
    *
    * @details Initializes an App object with the main menu state and a new Data object.
    */
    App();
public:
    /**
    * @brief Destructor for the App class.
    *
    * @details Deallocates the memory occupied by the App instance.
    */
    ~App();

    /**
    * @brief Gets the singleton instance of the App class.
    *
    * @details If the instance is not yet created, it creates a new App instance.
    *
    * @return A pointer to the singleton instance of the App class.
    */
    static App* getInstance();

    /**
    * @brief Gets the current state of the application.
    *
    * @return A pointer to the current state of the application.
    */
    State *getState();

    /**
    * @brief Sets the state of the application.
    *
    * @details This method sets the current state of the application to the specified state.
    *
    * @param state A pointer to the new state of the application.
    */
    void setState(State* state);

    /**
    * @brief Gets the data object associated with the application.
    *
    * @return A pointer to the Data object used by the application.
    */
    Data *getData();

    /**
    * @brief Sets the data for the application.
    *
    * @details This method attempts to read files and set the data for the application.
    * If an exception occurs during the file reading process, it is caught and rethrown.
    *
    * @throws std::exception if an error occurs during file reading.
    */
    void setData();

    /**
    * @brief Clears the existing data and creates a new instance of data for the application.
    *
    * @details This method deletes the existing data object and creates a new instance of Data class,
    * effectively clearing the previous data and resetting the data state for the application.
    */
    void clearData();

    /**
    * @brief Sets the file path for edges data.
    *
    * @details This method sets the file path for edges data in the application's data object.
    *
    * @param file_path The file path to set for edges data.
    */
    void setEdgesFilePath(const filesystem::path &file_path);

    /**
    * @brief Sets the file path for edges data.
    *
    * @details This method sets the file path for nodes data in the application's data object.
    *
    * @param file_path The file path to set for nodes data.
    */
    void setNodesFilePath(const filesystem::path &file_path);

    /**
    * @brief Displays the current state of the application.
    */
    void display() const;

    /**
    * @brief Handles the user input for the current state of the application.
    */
    void handleInput();
};


#endif //FEUP_DA_PROJECT_2_APP_H
