#include "GetNodesFileMenuState.h"
#include "States/MainMenuState.h"
#include "GetNodesFilePathState.h"
#include "GetEdgesFilePathState.h"

GetNodesFileMenuState::GetNodesFileMenuState() = default;

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

void GetNodesFileMenuState::handleInput(App* app) {
    string choice;
    cin >> choice;

    if (choice.size() == 1) {
        switch (choice[0]) {
            case '1':
                app->setState(new GetNodesFilePathState(this, [&](App *app) {
                    PressEnterToContinue(1);
                    app->setState(new GetEdgesFilePathState(this, [&](App *app) {
                        cout << "This might take some time... " << endl << endl;
                        clock_t start, end;
                        start = clock();
                        app->setData();
                        end = clock();
                        cout << "Elapsed time: " << setprecision(2) << double(end - start) / CLOCKS_PER_SEC << "s" << endl;
                        cout << "Network loaded successfully! " << endl;
                        PressEnterToContinue(1);
                        app->setState(new MainMenuState());
                    }));
                }));
                break;
            case '2':
                cin.ignore();
                app->setState(new GetEdgesFilePathState(this, [&](App *app) {
                    app->setNodesFilePath(filesystem::path());
                    cout << "This might take some time... " << endl << endl;
                    clock_t start, end;
                    start = clock();
                    app->setData();
                    end = clock();
                    cout << "Elapsed time: " << setprecision(2) << double(end - start) / CLOCKS_PER_SEC << "s" << endl;
                    cout << "Network loaded successfully! " << endl;
                    PressEnterToContinue(1);
                    app->setState(new MainMenuState());
                }));
                break;
            case 'q':
                app->setState(new MainMenuState());
                break;
            default:
                cout << "\033[31m" << "Invalid choice. Please try again." << "\033[0m"  << endl;
        }
    } else  {
        cout << "\033[31m";
        cout << "Invalid input. Please enter a single character." << endl;
        cout << "\033[0m";
    }
}
