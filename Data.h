#ifndef FEUP_DA_PROJECT_2_DATA_H
#define FEUP_DA_PROJECT_2_DATA_H


using namespace std;

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <limits>
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

    /**
    * @brief Checks if the graph data is loaded.
    *
    * @details This method checks if the graph data is loaded by verifying if the vertex set
    * of the graph is empty or not.
    *
    * @return true if the graph data is loaded, false otherwise.
    *
    * @complexity O(1).
    */
    bool isGraphLoaded();

    /**
    * @brief Sets the file path for edges data.
    *
    * @details This method sets the file path for edges data in the Data object.
    *
    * @param file_path The file path to set for edges data.
    *
    * @complexity O(1).
    */
    void setEdgesFilePath(const filesystem::path &file);

    /**
    * @brief Sets the file path for nodes data.
    *
    * @details This method sets the file path for nodes data in the Data object.
    *
    * @param file_path The file path to set for nodes data.
    *
    * @complexity O(1).
    */
    void setNodesFilePath(const filesystem::path &file);

    /**
    * @brief Reads files containing nodes and edges data.
    *
    * @details This method attempts to read files containing nodes and edges data.
    * If the edges file path is empty or if there are issues opening the files,
    * appropriate exceptions are thrown.
    *
    * @throws std::runtime_error if there are issues with file paths or opening files.
    */
    void readFiles();

    /**
    * @brief Reads edges data from a file.
    *
    * @details This method reads edges data from a file line by line, parses each line
    * to extract origin, destination, and distance information. It then adds vertices and
    * bidirectional edges to the graph accordingly. Carriage return characters are removed
    * if present in the input file.
    *
    * @param file An input file stream containing edges data.
    *
    * @complexity The time complexity of this method is O(n), where n is the number of lines
    * in the input file. Within each iteration of the while loop, the operations of reading
    * lines, parsing data, and adding vertices/edges to the graph are all done in constant time
    * or linear time with respect to the size of the input data. Therefore, the overall time
    * complexity is linear with respect to the number of lines in the input file.
    */

    void readEdgesFile(ifstream &file);

    /**
    * @brief Reads nodes data from a file.
    *
    * @details This method reads nodes data from a file line by line, parses each line
    * to extract node ID, longitude, and latitude information. It then adds vertices to
    * the graph with the corresponding information.
    * Carriage return characters are removed if present in the input file.
    *
    * @param file An input file stream containing nodes data.
    *
    * @complexity The time complexity of this method is O(n), where n is the number of lines
    * in the input file. Within each iteration of the while loop, the operations of reading
    * lines, parsing data, and adding vertices to the graph are all done in constant time
    * or linear time with respect to the size of the input data. Therefore, the overall time
    * complexity is linear with respect to the number of lines in the input file.
    */
    void readNodesFile(ifstream &file);

    /**
    * @brief Checks the existence of a vertex.
    *
    * @details This method checks whether a vertex with the given id exists.
    *
    * @param id The id of the vertex to be checked for existence.
    *
    * @return True if the vertex exists, false otherwise.
    *
    * @complexity O(1), as the function performs a constant-time map lookup.
    */
    bool vertexExists(int id);

    /**
    * @brief Solves the Traveling Salesman Problem (TSP) using backtracking.
    *
    * @details This method initializes the TSP solution process by setting all vertices as unvisited,
    * then starts the backtracking algorithm from the starting vertex (vertex with ID 0). It explores
    * all possible paths using backtracking and calculates the minimum cost of the TSP tour.
    * The final result is printed to the standard output.
    *
    * @complexity The time complexity of this function depends on the number of permutations of
    * vertices to explore, resulting in O(V!) in the worst case, where 'V' is the number of
    * vertices in the graph.
    */
    void TSPBacktracking();

    /**
    * @brief Solves the Traveling Salesman Problem (TSP) using a triangular approximation.
    *
    * @details This method approximates the TSP solution by finding a minimum spanning tree
    * (MST) of the graph and then traversing it in a specific manner to form a tour.
    * The length of this tour is calculated and printed as the TSP triangular approximation result.
    */
    void TSPTriangular();

    /**
    * @brief Solves the Traveling Salesman Problem (TSP) using the nearest neighbor heuristic.
    *
    * @details This method approximates the TSP solution by starting from the vertex with id 0
    * and iteratively selecting the nearest unvisited neighbor until all vertices are visited.
    * The length of the resulting tour is calculated and printed as the TSP nearest neighbor
    * approximation result.
    *
    * @complexity The time complexity of this function primarily depends on the number of vertices
    * in the graph and the implementation of finding the nearest neighbor, resulting in O(|V|^2),
    * where |V| is the number of vertices.
    */
    void TSPNearestNeighbor();

    /**
    * @brief Solves the Traveling Salesman Problem (TSP) using a real-world nearest neighbor heuristic.
    *
    * @details This method approximates the TSP solution by starting from a user-specified starting vertex
    * and iteratively selecting the nearest unvisited neighbor until all vertices are visited.
    * Additionally, it considers constraints specific to real-world scenarios (the graph is not fully connected).
    * If no solution is found within the constraints, an exception is thrown.
    * The length of the resulting tour is calculated and printed as the TSP real-world nearest neighbor
    * approximation result.
    *
    * @param starting_vertex The ID of the starting vertex for the TSP tour.
    *
    * @throws std::runtime_error if no feasible solution is found within the constraints.
    *
    * @complexity The time complexity of this function primarily depends on the number of vertices
    * in the graph and the implementation of finding the nearest neighbor, resulting in O(|V| + |E|),
    * where |V| is the number of vertices and |E| is the number of edges in the graph.
    */
    void TSPRealWorldNearestNeighbor(int startingVertexId);
};


#endif //FEUP_DA_PROJECT_2_DATA_H
