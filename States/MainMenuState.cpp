#include "MainMenuState.h"
#include "States/Utils/GetNodesFileMenuState.h"

MainMenuState::MainMenuState() = default;

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

void MainMenuState::handleInput(App* app) {
    string choice;
    cin >> choice;

    if (choice.size() == 1) {
        if(!app->getData()->isGraphLoaded()) {
            switch (choice[0]) {
                case '1':
                    app->setState(new GetNodesFileMenuState());
                    break;
                case 'q':
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
                    cout << endl;
                    cout << "\033[31m" << "> No graph loaded. Please load a graph first." << "\033[0m" << endl << endl;
                    PressEnterToContinue();
            }
        }
        else {
                switch (choice[0]) {
                    case '1':
                        app->clearData();
                        app->setState(new GetNodesFileMenuState());
                        break;
                    case '2':
                        app->setState(this);
                        PressEnterToContinue();
                        break;
                    case '3':
                        app->setState(this);
                        PressEnterToContinue();
                        break;
                    case '4':
                        app->setState(this);
                        PressEnterToContinue();
                        break;
                    case '5':
                        app->setState(this);
                        PressEnterToContinue();
                        break;
                    case 'q':
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
                        cout << "\033[31m" << "Invalid choice. Please try again." << "\033[0m" << endl;
                }
            }
    } else {
        cout << "\033[31m";
        cout << "Invalid input. Please enter a single character." << endl;
        cout << "\033[0m";
    }
}