#include <set>
#include "Data.h"

Data::Data() = default;

bool Data::isGraphLoaded() {
    return !g.getVertexSet().empty();
}

void Data::setEdgesFilePath(const filesystem::path &file_path) {
    edgesFilePath = file_path;
}

void Data::setNodesFilePath(const filesystem::path &file_path) {
    nodesFilePath = file_path;
}

void Data::readFiles() {
    try {
        if(edgesFilePath.empty()) throw runtime_error("Invalid input. Some file are missing in the given path.");

        if(!nodesFilePath.empty()) {
            ifstream nodesFile(nodesFilePath);
            if (!nodesFile.is_open()) throw runtime_error("Error opening the nodes file.");

            readNodesFile(nodesFile);
        }

        ifstream edgesFile(edgesFilePath);
        if (!edgesFile.is_open()) throw runtime_error("Error opening the edges file.");

        readEdgesFile(edgesFile);

    } catch (const exception& e) {
        throw;
    }
}

void Data::readEdgesFile(ifstream &file) {
    string line;

    while(getline(file, line)) {
        // Remove carriage return characters if present
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());

        stringstream ss(line);
        string origin_str, dest_str, distance_str;

        getline(ss, origin_str, ',');
        getline(ss, dest_str, ',');
        getline(ss, distance_str, ',');

        if(origin_str.empty() || dest_str.empty() || distance_str.empty())
            continue;

        int origin, dest;
        double distance;

        try {
            origin = stoi(origin_str);
            dest = stoi(dest_str);
            distance = stod(distance_str);
        } catch(const std::exception& e) {
            // Skip this line if conversion fails
            continue;
        }

        if(g.findVertex(origin) == nullptr)
            g.addVertex(origin);

        if(g.findVertex(dest) == nullptr)
            g.addVertex(dest);

        g.addBidirectionalEdge(origin, dest, distance);
    }

}

void Data::readNodesFile(ifstream &file) {
    string line;

    while(getline(file, line)) {
        // Remove carriage return characters if present
        line.erase(remove(line.begin(), line.end(), '\r'), line.end());

        stringstream ss(line);
        string id_str, longitude_str, latitude_str;

        getline(ss, id_str, ',');
        getline(ss, longitude_str, ',');
        getline(ss, latitude_str, ',');

        if(id_str.empty() || longitude_str.empty() || latitude_str.empty())
            continue;

        int id;
        double longitude, latitude;

        try {
            id = stoi(id_str);
            longitude = stod(longitude_str);
            latitude = stod(latitude_str);
        } catch(const std::exception& e) {
            // Skip this line if conversion fails
            continue;
        }

        g.addVertex(id, longitude, latitude);
    }
}

void Data::TSPBacktracking() {

    for(auto pair : g.getVertexSet()) {
        pair.second->setVisited(false);
    }

    double res = numeric_limits<double>::max();
    Vertex *v = g.findVertex(0);
    v->setVisited(true);

    g.TSPBacktracking(v, 0, 1, 0, res);

    cout << endl;
    cout << "TSP Backtracking result: " << setprecision(1) << res << endl;
}

void Data::TSPTriangular() {

    double res = 0;
    g.TSPTriangular(res);

    cout << endl;
    cout << "TSP Triangular approximation result: " << setprecision(1) << res << endl;
}

void Data::TSPNearestNeighbor() {

    double res = 0;
    g.TSPNearestNeighbor(res);

    cout << endl;
    cout << "TSP Nearest Neighbor result: " << setprecision(1) << res << endl;
}

void Data::TSPRealWorldNearestNeighbor() {

    try {
        double res = 0;
        g.TSPRealWorldNearestNeighbor(res);

        cout << endl;
        cout << "TSP Real World Nearest Neighbor result: " << setprecision(1) << res << endl;
    } catch (...) {
        cout << "\033[31m";
        cout << endl;
        cout << "There is no possible solution!" << endl << endl;
        cout << "\033[0m";
    }
}

