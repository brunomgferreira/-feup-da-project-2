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

