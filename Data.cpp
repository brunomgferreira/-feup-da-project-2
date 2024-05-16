#include <set>
#include "Data.h"

// Constructor
Data::Data() = default;

// Check if the graph is loaded
bool Data::isGraphLoaded() {
    return !g.getVertexSet().empty(); // Return true if the vertex set is not empty
}

// Set file path for edges
void Data::setEdgesFilePath(const filesystem::path &file_path) {
    edgesFilePath = file_path; // Assign the provided file path to edgesFilePath
}

// Set file path for nodes
void Data::setNodesFilePath(const filesystem::path &file_path) {
    nodesFilePath = file_path; // Assign the provided file path to nodesFilePath
}

// Read files and populate graph
void Data::readFiles() {
    try {
        if(edgesFilePath.empty()) throw runtime_error("Invalid input. Some files are missing in the given path."); // Throw exception if edges file path is empty

        if(!nodesFilePath.empty()) {
            ifstream nodesFile(nodesFilePath);
            if (!nodesFile.is_open()) throw runtime_error("Error opening the nodes file."); // Throw exception if nodes file cannot be opened

            readNodesFile(nodesFile); // Read nodes file
        }

        ifstream edgesFile(edgesFilePath);
        if (!edgesFile.is_open()) throw runtime_error("Error opening the edges file."); // Throw exception if edges file cannot be opened

        readEdgesFile(edgesFile); // Read edges file

    } catch (const exception& e) {
        throw; // Rethrow any caught exceptions
    }
}

// Read edges file and populate graph
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

        g.addBidirectionalEdge(origin, dest, distance); // Add edge to the graph
    }
}

// Read nodes file and add vertices to the graph
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

        g.addVertex(id, longitude, latitude); // Add vertex to the graph
    }
}

// Check if vertex exists in the graph
bool Data::vertexExists(int id) {
    Vertex *v = g.findVertex(id);
    if(v) return true;
    return false;
}

// Perform TSP using backtracking algorithm
void Data::TSPBacktracking() {

    for(auto pair : g.getVertexSet()) {
        pair.second->setVisited(false); // Reset visited flag for all vertices
    }

    double res = numeric_limits<double>::max();
    Vertex *v = g.findVertex(0);
    v->setVisited(true); // Mark the starting vertex as visited

    g.TSPBacktracking(v, 0, 1, 0, res); // Perform TSP using backtracking

    cout << endl;
    cout << "TSP Backtracking result: " << setprecision(1) << res << endl; // Output result
}

// Perform TSP using triangular approximation algorithm
void Data::TSPTriangular() {

    double res = 0;
    g.TSPTriangular(res); // Perform TSP using triangular approximation

    cout << endl;
    cout << "TSP Triangular approximation result: " << setprecision(1) << res << endl; // Output result
}

// Perform TSP using nearest neighbor algorithm
void Data::TSPNearestNeighbor() {

    double res = 0;
    g.TSPNearestNeighbor(res); // Perform TSP using nearest neighbor

    cout << endl;
    cout << "TSP Nearest Neighbor result: " << setprecision(1) << res << endl; // Output result
}

// Perform TSP using real-world nearest neighbor algorithm
void Data::TSPRealWorldNearestNeighbor(int startingVertexId) {

    try {
        double res = 0;
        g.TSPRealWorldNearestNeighbor(res, startingVertexId); // Perform TSP using real-world nearest neighbor

        cout << "Starting vertex id: " << startingVertexId << endl;
        cout << endl;
        cout << "TSP Real World Nearest Neighbor result: " << setprecision(1) << res << endl; // Output result
    } catch (...) {
        cout << "\033[31m";
        cout << endl;
        cout << "There is no possible solution!" << endl << endl; // Output error message if no solution found
        cout << "\033[0m";
    }
}
