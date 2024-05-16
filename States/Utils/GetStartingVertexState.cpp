#include "GetStartingVertexState.h"
#include "TryAgainState.h"

GetStartingVertexState::GetStartingVertexState(State* backState, function<void(App*, int)> nextStateCallback)
        : backState(backState), nextStateCallback(std::move(nextStateCallback)) {}

void GetStartingVertexState::display() const {
    cout << "Insert starting vertex id (Ex: 0): ";
}

void GetStartingVertexState::handleInput(App* app) {
    int id;
    std::cin.ignore();
    std::cin >> id;

    bool vertexExists = app->getData()->vertexExists(id);

    if (vertexExists) {
        nextStateCallback(app, id);
    } else {
        cout << "\033[31m";
        cout << "Vertex does not exist." << endl;
        cout << "\033[0m";
        app->setState(new TryAgainState(backState, this));
    }
}
