#include "MainMenuState.h"
#include "States/Utils/GetNodesFileMenuState.h"
#include "States/Utils/GetStartingVertexState.h"

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
                clock_t start, end;
                switch (choice[0]) {
                    case '1':
                        app->clearData();
                        app->setState(new GetNodesFileMenuState());
                        break;
                    case '2':
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
                        app->setState(new GetStartingVertexState(this, [&](App *app, int id) {
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