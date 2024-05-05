#include "GetEdgesFilePathState.h"
#include "TryAgainState.h"

GetEdgesFilePathState::GetEdgesFilePathState(State* backState, function<void(App*)> nextStateCallback)
        : backState(backState), nextStateCallback(std::move(nextStateCallback)) {}

void GetEdgesFilePathState::display() const {
    cout << "Insert path to the edges file (Ex: \"./dataset/edges.csv\"): ";
}

void GetEdgesFilePathState::handleInput(App* app) {
    string path;
    getline(cin, path);
    filesystem::path file_path;

    try {

        if (path.front() == '.') {
            file_path = filesystem::path(filesystem::current_path() / ("." + path));
        }
        else {
            file_path = filesystem::path(path);
        }

        if (filesystem::exists(file_path) && !filesystem::is_directory(file_path)) {
            app->setEdgesFilePath(file_path);
            nextStateCallback(app);
        } else {
            throw invalid_argument("Invalid path. Please enter a valid file path.");
        }
    } catch (const invalid_argument& e) {

        cout << "\033[31m";
        cout << e.what() << endl;
        cout << "\033[0m";
        app->setState(new TryAgainState(backState, this));

    }
}