#ifndef FEUP_DA_PROJECT_2_GET_NODES_FILE_MENU_STATE_H
#define FEUP_DA_PROJECT_2_GET_NODES_FILE_MENU_STATE_H


#include "States/State.h"

/**
* @brief Class representing the get nodes file menu state.
*/

class GetNodesFileMenuState : public State {
public:

    /**
    * @brief Default constructor for GetNodesFileMenuState.
    *
    * @details This constructor initializes an instance of the GetNodesFileMenuState class. It doesn't require any parameters,
    * as it represents the get nodes file menu state of the application, allowing users to choose if they want to to different functionalities
    * and sections of the program.
    */
    GetNodesFileMenuState();

    /**
    * @brief Displays the nodes file menu options.
    *
    * @details This method prints the nodes file menu options to the console, allowing users to choose from different
    * functionalities. Users input a single character corresponding to their desired option (1-7 for sections, 'q' to exit).
    * The method provides a visual representation of the nodes file menu and prompts the user to enter their choice.
    */
    void display() const override;

    /**
    * @brief Handles user input for the nodes file menu.
    *
    * @details This method prompts the user to input a single character representing their choice in the nodes file menu.
    * It uses a switch statement to determine the action corresponding to the user's choice. If the input is valid, the
    * method transitions to the appropriate state based on the user's choice.
    * If the input is invalid, the method notifies the user and prompts them to try again. The 'q' option exits the program.
    *
    * @param app A pointer to the application instance.
    */
    void handleInput(App* app) override;
};


#endif //FEUP_DA_PROJECT_2_GET_NODES_FILE_MENU_STATE_H
