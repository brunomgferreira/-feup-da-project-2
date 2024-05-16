#include "GetNodesFileMenuState.h"
#include "States/MainMenuState.h"
#include "GetNodesFilePathState.h"
#include "GetEdgesFilePathState.h"

// Constructor for GetNodesFileMenuState
GetNodesFileMenuState::GetNodesFileMenuState() = default;

// Display function to prompt the user to load nodes file
void GetNodesFileMenuState::display() const {
    cout << "\033[32m";
    cout << "=============================" << endl;
    cout << "\033[0m";
    cout << " Load nodes file ?           \n" << endl;

    cout << "   1. Yes                    " << endl;
    cout << "   2. No                     \n" << endl;

    cout << "   q. Main Menu              " << endl;
    cout << "\033[32m";
    cout << "-----------------------------" << endl;
    cout << "\033[0m";
    cout << "Enter your choice: ";
}

// Function to handle user input for loading nodes file
void GetNodesFileMenuState::handleInput(App* app) {
    string choice;
    cin >> choice;

    if (choice.size() == 1) { // Check if input is a single character
        switch (choice[0]) {
            case '1':
                // Transition to GetNodesFilePathState and then to GetEdgesFilePathState
                // Set callback functions to handle transitions and data setting
                cin.ignore();
                app->setState(new GetNodesFilePathState(this, [&](App *app) {
                    PressEnterToContinue(1);
                    app->setState(new GetEdgesFilePathState(this, [&](App *app) {
                        cout << "This might take some time... " << endl << endl;
                        clock_t start, end;
                        start = clock();
                        app->setData();
                        end = clock();
                        cout << "Network loaded successfully! " << endl;
                        cout << "Elapsed time: " << fixed <<  setprecision(2) << double(end - start) / CLOCKS_PER_SEC << "s" << endl << endl;
                        PressEnterToContinue(1);
                        app->setState(new MainMenuState()); // Transition back to main menu
                    }));
                }));
                break;
            case '2':
                // Transition directly to GetEdgesFilePathState without loading nodes file
                // Set callback function to handle transitions and data setting
                cin.ignore();
                app->setState(new GetEdgesFilePathState(this, [&](App *app) {
                    app->setNodesFilePath(filesystem::path());
                    cout << "This might take some time... " << endl << endl;
                    clock_t start, end;
                    start = clock();
                    app->setData();
                    end = clock();
                    cout << "Network loaded successfully! " << endl;
                    cout << "Elapsed time: " << fixed <<  setprecision(2) << double(end - start) / CLOCKS_PER_SEC << "s" << endl << endl;
                    PressEnterToContinue(1);
                    app->setState(new MainMenuState()); // Transition back to main menu
                }));
                break;
            case 'q':
                app->setState(new MainMenuState()); // Transition back to main menu
                break;
            default:
                // Display error message for invalid choice
                cout << "\033[31m" << "Invalid choice. Please try again." << "\033[0m"  << endl;
        }
    } else {
        // Display error message for invalid input
        cout << "\033[31m";
        cout << "Invalid input. Please enter a single character." << endl;
        cout << "\033[0m";
    }
}
