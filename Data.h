#ifndef FEUP_DA_PROJECT_2_DATA_H
#define FEUP_DA_PROJECT_2_DATA_H


using namespace std;

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <cmath>
#include "Graph.h"

/**
 * @brief Class that saves all the program data.
 */

class Data {
private:
    filesystem::path edgesFilePath;
    filesystem::path nodesFilePath;
    Graph g;
public:
    /**
    * @brief Default constructor for the Data class.
    *
    * @details This default constructor creates a new instance of the Data class without
    * specifying any initial values. It initializes the Data object with default values.
    */
    Data();

    bool isGraphLoaded();

    void setEdgesFilePath(const filesystem::path &file);

    void setNodesFilePath(const filesystem::path &file);

    void readFiles();

    void readEdgesFile(ifstream &file);

    void readNodesFile(ifstream &file);

    void TSPBacktracking();
};


#endif //FEUP_DA_PROJECT_2_DATA_H
