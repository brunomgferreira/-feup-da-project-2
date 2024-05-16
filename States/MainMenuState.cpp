#include "MainMenuState.h"
#include "States/Utils/GetNodesFileMenuState.h"
#include "States/Utils/GetStartingVertexState.h"

// Constructor for MainMenuState
MainMenuState::MainMenuState() = default;

// Display function to print the main menu options
void MainMenuState::display() const {
    cout << "\033[32m";
    cout << "========== MAIN MENU ==========" << endl;
    cout << "\033[0m";
    cout << "   1. Load Graph               " << endl;
    cout << "   2. Backtracking Algorithm   " << endl;
    cout << "   3. Triangular Approximation " << endl;
    cout << "   4. Heuristic Algorithm      " << endl;
    cout << "   5. TSP in Real World Graphs \n" << endl;

    cout << "   q. Exit           " << endl;
    cout << "\033[32m";
    cout << "-------------------------------" << endl;
    cout << "\033[0m";
    cout << "Enter your choice: ";
}

// Function to handle user input and navigate through different states
void MainMenuState::handleInput(App* app) {
    string choice;
    cin >> choice;

    if (choice.size() == 1) {
        if(!app->getData()->isGraphLoaded()) {  // Check if a graph is loaded
            switch (choice[0]) {
                case '1':
                    app->setState(new GetNodesFileMenuState()); // Transition to GetNodesFileMenuState
                    break;
                case 'q':
                    // Display exit message and set state to nullptr to exit the program
                    // Also display system developers' information
                    cout << "\033[32m" << endl;
                    cout << "========================================" << endl;
                    cout << "\033[0m";
                    cout << "Exiting the program..." << endl << endl;
                    cout << "System Developed by:" << endl;
                    cout << "  > António Santos" << " - " << "up201705558@fe.up.pt" << endl;
                    cout << "  > Bruno Ferreira" << " - " << "up202207863@fe.up.pt" << endl;
                    cout << "  > Gonçalo Ferros" << " - " << "up202207592@fe.up.pt" << endl;
                    cout << "\033[32m";
                    cout << "========================================" << endl;
                    cout << "\033[0m";
                    app->setState(nullptr);
                    break;
                default:
                    // Display error message for invalid choice
                    cout << endl;
                    cout << "\033[31m" << "> No graph loaded. Please load a graph first." << "\033[0m" << endl << endl;
                    PressEnterToContinue();
            }
        }
        else { // If a graph is loaded
                clock_t start, end;
                switch (choice[0]) {
                    case '1':
                        // Clear loaded graph data and transition to GetNodesFileMenuState
                        app->clearData();
                        app->setState(new GetNodesFileMenuState());
                        break;
                    case '2':
                        // Execute TSPBacktracking algorithm, measure time, and display results
                        try {
                            start = clock();
                            app->getData()->TSPBacktracking();
                            end = clock();
                            cout << "Elapsed time: " << fixed <<  setprecision(2) << double(end - start) / CLOCKS_PER_SEC << "s" << endl << endl;
                        } catch (...) {
                            cout << "\033[31m";
                            cout << endl;
                            cout << "Theres was an error!" << endl;
                            cout << "Please check your graph." << endl << endl;
                            cout << "\033[0m";
                        }
                        PressEnterToContinue();
                        break;
                    case '3':
                        // Execute TSPTriangular algorithm, measure time, and display results
                        try {
                            start = clock();
                            app->getData()->TSPTriangular();
                            end = clock();
                            cout << "Elapsed time: " << fixed <<  setprecision(2) << double(end - start) / CLOCKS_PER_SEC << "s" << endl << endl;
                        } catch (...) {
                            cout << "\033[31m";
                            cout << endl;
                            cout << "Theres was an error!" << endl;
                            cout << "Please check your graph." << endl << endl;
                            cout << "\033[0m";
                        }
                        PressEnterToContinue();
                        break;
                    case '4':
                        // Execute TSPNearestNeighbor algorithm, measure time, and display results
                        try {
                            start = clock();
                            app->getData()->TSPNearestNeighbor();
                            end = clock();
                            cout << "Elapsed time: " << fixed <<  setprecision(2) << double(end - start) / CLOCKS_PER_SEC << "s" << endl << endl;
                        } catch (...) {
                            cout << "\033[31m";
                            cout << endl;
                            cout << "Theres was an error!" << endl;
                            cout << "Please check your graph." << endl << endl;
                            cout << "\033[0m";
                        }
                        PressEnterToContinue();
                        break;
                    case '5':
                        // Transition to GetStartingVertexState with a lambda function to handle user input
                        app->setState(new GetStartingVertexState(this, [&](App *app, int id) {
                            // Execute TSPRealWorldNearestNeighbor algorithm, measure time, and display results
                            try {
                                start = clock();
                                app->getData()->TSPRealWorldNearestNeighbor(id);
                                end = clock();
                                cout << "Elapsed time: " << fixed <<  setprecision(2) << double(end - start) / CLOCKS_PER_SEC << "s" << endl << endl;
                            } catch (...) {
                                cout << "\033[31m";
                                cout << endl;
                                cout << "Theres was an error!" << endl;
                                cout << "Please check your graph." << endl << endl;
                                cout << "\033[0m";
                            }
                            PressEnterToContinue();
                            app->setState(new MainMenuState);
                        }));
                        break;
                    case 'q':
                        // Display exit message and set state to nullptr to exit the program
                        cout << "\033[32m";
                        cout << "========================================" << endl;
                        cout << "\033[0m";
                        cout << "Exiting the program..." << endl << endl;
                        cout << "System Developed by:" << endl;
                        cout << "  > António Santos" << " - " << "up201705558@fe.up.pt" << endl;
                        cout << "  > Bruno Ferreira" << " - " << "up202207863@fe.up.pt" << endl;
                        cout << "  > Gonçalo Ferros" << " - " << "up202207592@fe.up.pt" << endl;
                        cout << "\033[32m";
                        cout << "========================================" << endl;
                        cout << "\033[0m";
                        app->setState(nullptr);
                        break;
                    default:
                        // Display error message for invalid choice
                        cout << "\033[31m" << "Invalid choice. Please try again." << "\033[0m" << endl;
                }
            }
    } else {
        // Display error message for invalid input (more than one character)
        cout << "\033[31m";
        cout << "Invalid input. Please enter a single character." << endl;
        cout << "\033[0m";
    }
}