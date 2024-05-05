#include "App.h"
#include "States/MainMenuState.h"

App* App::instance = nullptr;

App::App() {
    currentState = new MainMenuState();
    data = new Data();
}

App::~App() {
    delete instance;
}

App *App::getInstance() {
    if (!instance) {
        instance = new App();
    }
    return instance;
}

State *App::getState() {
    return currentState;
}

void App::setState(State* state) {
    currentState = state;
}

void App::clearData() {
    delete this->data;
    this->data = new Data();
}

void App::setData() {
    try {
        this->data->readFiles();
    } catch (const exception& e) {
        throw e;
    }
}

void App::setEdgesFilePath(const filesystem::path &file_path) {
    this->data->setEdgesFilePath(file_path);
}

void App::setNodesFilePath(const filesystem::path &file_path) {
    this->data->setNodesFilePath(file_path);
}

void App::display() const {
    if(typeid(*currentState) == typeid(MainMenuState)) {
        cout << "\033[32m";
        cout << "------------------------------" << endl;
        cout << "\033[0m";
        cout << "> Loaded Graph?: " << (data->isGraphLoaded() ? "Yes" : ("\033[31mNo\033[30m")) << endl;
    }
    currentState->display();
}

void App::handleInput() {
    currentState->handleInput(this);
}

Data *App::getData() {
    return data;
}
