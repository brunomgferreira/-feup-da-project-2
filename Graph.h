#ifndef FEUP_DA_PROJECT_2_GRAPH_H
#define FEUP_DA_PROJECT_2_GRAPH_H

#include "MutablePriorityQueue.h"

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Edge;

/************************* Vertex  **************************/

/**
* @brief Represents a vertex in the graph.
*/
class Vertex {
private:
    int id;            // id of the node
    double longitude = numeric_limits<double>::max();
    double latitude = numeric_limits<double>::max();
    unordered_map<int, Edge *> adj;  // outgoing edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    double dist = 0;
    Vertex *path = nullptr;

    int queueIndex = 0; 		// required by MutablePriorityQueue

    friend class MutablePriorityQueue<Vertex>;

public:

    /**
     * @brief Constructor forS Vertex class.
     *
     * @param id The id associated with the vertex.
     */
    explicit Vertex(int id);

    /**
    * @brief Constructor forS Vertex class.
    *
    * @param id The id associated with the vertex.
    * @param longitude The longitude associated with the vertex.
    * @param latitude The latitude associated with the vertex.
    */
    Vertex(int id, double longitude, double latitude);

    /**
     * @brief Less-than comparison operator for vertices based on distance.
     *
     * @param vertex The vertex to compare against.
     * @return True if this vertex's distance is less than the other vertex's distance, otherwise false.
     */
    bool operator<(Vertex & vertex) const;

    /**
     * @brief Get the id associated with the vertex.
     *
     * @return The id of the vertex.
     */
    [[nodiscard]] int getId() const;

    /**
     * @brief Get the longitude associated with the vertex.
     *
     * @return The longitude of the vertex.
     */
    [[nodiscard]] double getLongitude() const;

    /**
     * @brief Get the latitude associated with the vertex.
     *
     * @return The latitude of the vertex.
     */
    [[nodiscard]] double getLatitude() const;

    /**
     * @brief Get the adjacent edges of the vertex.
     *
     * @return Vector of pointers to adjacent edges.
     */
    [[nodiscard]] unordered_map<int, Edge *> getAdj() const;

    /**
     * @brief Check if the vertex has been visited.
     *
     * @return True if the vertex has been visited, otherwise false.
     */
    [[nodiscard]] bool isVisited() const;

    /**
     * @brief Get the path associated with the vertex.
     *
     * @return Pointer to the path vertex.
     */
    [[nodiscard]] Vertex *getPath() const;

    /**
     * @brief Set the visited status of the vertex.
     *
     * @param isVisited True if the vertex is visited, otherwise false.
     */
    void setVisited(bool isVisited);

    /**
     * @brief Get the distance associated with the vertex.
     *
     * @return Distance of the vertex.
     */
    double getDist() const;

    /**
     * @brief Set the distance of the vertex.
     *
     * @param value The new distance of the vertex.
     */
    void setDist(double value);

    /**
     * @brief Set the path associated with the vertex.
     *
     * @param newPath Pointer to the new path vertex.
     */
    void setPath(Vertex *newPath);

    /**
     * @brief Add an edge between this vertex and a destination vertex.
     *
     * @param dest Pointer to the destination vertex.
     * @param w Weight of the edge.
     *
     * @return Pointer to the newly added edge.
     */
    Edge * addEdge(Vertex *dest, double w);

    /**
     * @brief Find an edge between this vertex and a destination vertex.
     *
     * @param destVertex Pointer to the destination vertex.
     *
     * @return Pointer to the found edge if exists, otherwise nullptr.
     */
    Edge * findEdge(int destId);
};

/********************** Edge  ****************************/

/**
* @brief Class representing an edge in a graph.
*/
class Edge {
private:
    Vertex *dest; // destination vertex
    double weight; // edge weight

    // used for bidirectional edges
    Vertex *orig;
    Edge *reverse = nullptr;

public:
    /**
    * @brief Constructor for the Edge class.
    *
    * @details Initializes an instance of the Edge class with the specified origin vertex, destination vertex and edge weight.
    *
    * @param orig Pointer to the origin vertex.
    * @param dest Pointer to the destination vertex.
    * @param weight Weight of the edge.
    */
    Edge(Vertex *orig, Vertex *dest, double weight);

    /**
    * @brief Get the destination vertex associated with the edge.
    *
    * @return Pointer to the destination vertex.
    */
    [[nodiscard]] Vertex * getDest() const;

    /**
     * @brief Get the weight associated with the edge.
     *
     * @return The weight of the edge.
     *
     */
    [[nodiscard]] double getWeight() const;

    /**
     * @brief Get the origin vertex associated with the edge.
     *
     * @return Pointer to the origin Vertex.
     *
     */
    [[nodiscard]] Vertex * getOrig() const;

    /**
     * @brief Get reverse edge associated with the edge.
     *
     * @return Pointer to the reverse edge.
     *
     */
    [[nodiscard]] Edge *getReverse() const;

    /**
     * @brief Set the reverse edge associated with this edge.
     *
     * @param reverseEdge Pointer to the reverse edge to set.
     */
    void setReverse(Edge *reverseEdge);
};

/********************** Graph  ****************************/

/**
* @brief Class representing a graph.
*/

class Graph {
private:
    unordered_map<int, Vertex *> vertices;    // vertex set

public:

    /**
     * @brief Finds a vertex in the graph based on its id.
     *
     * @details This function searches for a vertex with the given id in the graph's vertex set. If
     * the vertex is found, a pointer to it is returned; otherwise, nullptr is returned to indicate that
     * the vertex could not be found.
     *
     * @param id The id of the vertex to be found.
     *
     * @return A pointer to the vertex if found, nullptr otherwise.
     *
     * @complexity The time complexity of this function depends on the time complexity of finding an
     * element in an unordered_map, which is O(1) in the worst case.
     */
    Vertex *findVertex(int id) const;

    /**
     * @brief Adds a vertex to the graph.
     *
     * @details This function adds a vertex with the given id and type to the graph. If a vertex with
     * the same id already exists in the graph, the function returns false, indicating that the vertex
     * could not be added. Otherwise, it creates a new vertex, inserts it into the graph's vertex set,
     * and returns true to indicate a successful addition.
     *
     * @param id The id of the vertex to be found.
     *
     * @return True if the vertex is successfully added, false otherwise.
     *
     * @complexity The time complexity of this function depends on the time complexity of finding a
     * vertex in the graph, which is O(1) in the worst case, and inserting a new vertex into
     * the vertex set, which is also O(1) in the worst case.
     */
    bool addVertex(int id);

    /**
     * @brief Adds a vertex to the graph.
     *
     * @details This function adds a vertex with the given id and type to the graph. If a vertex with
     * the same id already exists in the graph, the function returns false, indicating that the vertex
     * could not be added. Otherwise, it creates a new vertex, inserts it into the graph's vertex set,
     * and returns true to indicate a successful addition.
     *
     * @param id The id of the vertex to be found.
     * @param longitude The longitude of the vertex to be found.
     * @param latitude The latitude of the vertex to be found.
     *
     * @return True if the vertex is successfully added, false otherwise.
     *
     * @complexity The time complexity of this function depends on the time complexity of finding a
     * vertex in the graph, which is O(1) in the worst case, and inserting a new vertex into
     * the vertex set, which is also O(1) in the worst case.
     */
    bool addVertex(int id, double longitude, double latitude);

    /**
     * @brief Adds an edge between two vertices in the graph.
     *
     * @details This function adds an edge from the vertex with the source id to the vertex with the
     * destination id. If either of the vertices does not exist in the graph, the function returns
     * false, indicating that the edge could not be added. Otherwise, it adds the edge to the origin
     * vertex and checks if there is a corresponding reverse edge in the destination vertex. If a
     * reverse edge exists and has the same weight as the newly added edge, it sets the reverse
     * pointers for both edges to maintain bidirectionality.
     *
     * @param source The id of the source vertex.
     * @param dest The id of the destination vertex.
     * @param w The weight of the edge.
     *
     * @return True if the edge is successfully added, false otherwise.
     *
     * @complexity The time complexity of this function depends on the time complexity of finding
     * vertices in the graph, adding edges to the vertices, and setting reverse pointers, all of which
     * are O(1) in the worst case.
     */
    bool addEdge(int source, int dest, double w) const;

    /**
     * @brief Adds a bidirectional edge between two vertices in the graph.
     *
     * @details This function adds a bidirectional edge between the vertices with the given source and
     * destination ids. If either of the vertices does not exist in the graph, the function returns
     * false, indicating that the edge could not be added. Otherwise, it creates two edges: one from
     * source to dest and another from dest to source, each with the specified weight.
     * Additionally, it sets the reverse pointers for the edges to maintain bidirectionality.
     *
     * @param source The id of the source vertex.
     * @param dest The id of the destination vertex.
     * @param w The weight of the edge.
     *
     * @return True if the bidirectional edge is successfully added, false otherwise.
     *
     * @complexity The time complexity of this function depends on the time complexity of finding
     * vertices in the graph, adding edges to the vertices, and setting reverse pointers, all of which
     * are O(1) in the worst case.
     */
    bool addBidirectionalEdge(int source, int dest, double w) const;

    /**
     * @brief Retrieves the set of vertices in the graph.
     *
     * @return An unordered map containing the vertices of the graph, where the keys are vertex ids
     * and the values are pointers to the corresponding vertices.
     *
     * @details This function returns a copy of the unordered map containing all vertices in the graph.
     * It does not modify the original graph.
     *
     * @complexity O(1)
     */
    unordered_map<int, Vertex *> getVertexSet() const;

    /**
     * @brief Retrieves the weight of the edge between two vertices in the graph.
     *
     * @details This function retrieves the weight of the edge between the specified source and
     * destination vertices. It first attempts to find the edge connecting the two vertices. If
     * the edge does not exist, it calculates the weight using the Haversine formula based on the
     * latitude and longitude coordinates of the vertices. If either of the vertices has invalid
     * coordinates (latitude or longitude set to numeric_limits<double>::max()), indicating that
     * it's not a valid vertex, the function throws a runtime error. If the edge exists, it returns
     * the weight of the edge.
     *
     * @param source A pointer to the source vertex.
     * @param dest A pointer to the destination vertex.
     *
     * @return The weight of the edge between the source and destination vertices, or the calculated
     * distance based on their coordinates if the edge does not exist.
     *
     * @throws std::runtime_error If the edge is not found and either of the vertices has invalid
     * coordinates.
     *
     * @complexity The time complexity of this function depends on the time complexity of finding
     * the edge between the vertices, which is O(1) in the average case for most graph
     * representations. If the edge does not exist, the complexity of calculating the distance
     * between the vertices using the Haversine formula is O(1).
    */
    double getEdgeWeight(Vertex* source, Vertex* dest);

    /**
     * @brief Performs the Traveling Salesman Problem (TSP) using backtracking algorithm.
     *
     * @details This function recursively explores all possible paths starting from the current
     * vertex to find the shortest Hamiltonian cycle that visits all vertices exactly once and
     * returns to the starting vertex. It backtracks when all vertices have been visited to check
     * if the current path forms a cycle and updates the minimum cost if necessary.
     *
     * @param currentVertex A pointer to the current vertex being visited in the TSP traversal.
     * @param destId The id of the destination vertex (starting vertex) for completing the cycle.
     * @param count The number of vertices visited in the current path.
     * @param cost The total cost of the current path.
     * @param res Reference to the minimum cost found so far, updated recursively.
     *
     * @complexity The time complexity of this function depends on the number of permutations of
     * vertices to explore, resulting in O(V!) in the worst case, where 'V' is the number of
     * vertices in the graph.
    */
    void TSPBacktracking(Vertex *currentVertex, int destId, int count, double cost, double &res);

    /**
     * @brief Solves the Traveling Salesman Problem (TSP) using the Triangular TSP heuristic.
     *
     * @details This function applies the Triangular TSP heuristic, which consists of constructing
     * a minimum spanning tree (MST) using Prim's algorithm with a binary heap-based priority queue,
     * and then performing a preorder traversal on the MST to generate a Hamiltonian cycle.
     * It calculates the total cost of the cycle by summing the weights of the edges in the preorder
     * traversal path.
     *
     * @param res Reference to the variable to store the total cost of the Hamiltonian cycle.
     *
     * @complexity The time complexity of this function primarily depends on the time complexity of
     * constructing the minimum spanning tree using Prim's algorithm, which is O((|V| + |E|) log |V|)
     * with adjacency list representation and a binary heap-based priority queue. The complexity
     * of the preorder traversal is O(|V|), and calculating edge weights is O(1) on average.
     * Overall, the complexity is dominated by Prim's algorithm.
    */
    void TSPTriangular(double &res);

    /**
     * @brief Constructs a minimum spanning tree (MST) using Prim's algorithm.
     *
     * @details This function implements Prim's algorithm to find the minimum spanning tree (MST)
     * of the graph starting from an arbitrary vertex. It initializes each vertex's distance to
     * infinity and sets its path and visited status accordingly. Then, it selects a starting vertex,
     * sets its distance to 0, and initializes a mutable priority queue to manage vertices based
     * on their distances. The algorithm iterates by extracting the vertex with the minimum distance
     * from the priority queue, marking it as visited, and updating the distances of its adjacent
     * vertices if shorter paths are found. The process continues until all vertices are visited.
     *
     * @complexity The time complexity of Prim's algorithm depends on the implementation of the
     * priority queue. Using a binary heap-based priority queue, the complexity is O((|V| + |E|) log |V|),
     * where |V| is the number of vertices and |E| is the number of edges in the graph.
    */
    void prim();

    /**
     * @brief Performs a preorder traversal starting from a given vertex.
     *
     * @details This function recursively performs a preorder traversal starting from the specified
     * vertex in the graph. It adds each visited vertex to the preorder vector and continues the
     * traversal by recursively visiting adjacent vertices that are connected to the current vertex
     * via their paths. The traversal continues until all vertices are visited or until the preorder
     * vector contains 'n' vertices, where 'n' is the total number of vertices in the graph.
     *
     * @param v A pointer to the starting vertex for the preorder traversal.
     * @param preorder Reference to the vector to store the vertices in preorder traversal order.
     * @param n The total number of vertices in the graph.
     *
     * @complexity The time complexity of this function depends on the number of vertices in the
     * graph and the structure of the graph. In the worst case, where the graph is a complete graph,
     * the complexity is O(|V| + |E|), where |V| is the number of vertices and |E| is the number of edges in the graph.
    */
    void preorderTraversal(Vertex *v, std::vector<Vertex *> &preorder, int n);

    /**
     * @brief Solves the Traveling Salesman Problem (TSP) using the Nearest Neighbor heuristic.
     *
     * @details This function applies the Nearest Neighbor heuristic to find an approximate solution
     * to the TSP. Starting from an arbitrary vertex, it iteratively selects the nearest unvisited
     * neighbor until all vertices are visited, forming a Hamiltonian cycle. It calculates the total
     * cost of the cycle by summing the weights of the edges traversed.
     *
     * @param res Reference to the variable to store the total cost of the Hamiltonian cycle.
     *
     * @throws std::runtime_error If no neighboring vertex is found during the traversal.
     *
     * @complexity The time complexity of this function primarily depends on the number of vertices
     * in the graph and the implementation of finding the nearest neighbor, resulting in O(|V|^2),
     * where |V| is the number of vertices.
    */
    void TSPNearestNeighbor(double &res);

    /**
     * @brief Solves the Traveling Salesman Problem (TSP) using the Real-World Nearest Neighbor heuristic.
     *
     * @details This function applies the Real-World Nearest Neighbor heuristic to find an approximate
     * solution to the TSP. Starting from a specified vertex, it iteratively selects the nearest unvisited
     * neighbor based on real-world distances (edge weights) until all vertices are visited, forming a
     * Hamiltonian cycle. It calculates the total cost of the cycle by summing the weights of the edges
     * traversed.
     *
     * @param res Reference to the variable to store the total cost of the Hamiltonian cycle.
     * @param startingVertexId The ID of the vertex from which the traversal should start.
     *
     * @throws std::runtime_error If no neighboring vertex or path is found during the traversal.
     *
     * @complexity The time complexity of this function primarily depends on the number of vertices
     * in the graph and the implementation of finding the nearest neighbor, resulting in O(|V| + |E|),
     * where |V| is the number of vertices and |E| is the number of edges in the graph.
     */
    void TSPRealWorldNearestNeighbor(double &res, int startingVertexId);
};

// AUX functions

/**
 * @brief Converts an angle from degrees to radians.
 *
 * @details This function converts an angle from degrees to radians using the formula:
 * radians = degrees * (π / 180), where π (pi) is the mathematical constant representing
 * the ratio of a circle's circumference to its diameter.
 *
 * @param coord The angle in degrees to be converted to radians.
 *
 * @return The angle converted to radians.
 *
 * @complexity The time complexity of this function is O(1) since it involves a simple multiplication
 * operation followed by a division, both of which operate on constant-sized inputs.
*/
inline double convert_to_radians(const double coord)
{
    return coord * (M_PI / 180);
}

/**
 * @brief Calculates the distance between two points on the Earth's surface using the Haversine formula.
 *
 * @details This function computes the distance between two geographic coordinates specified in
 * latitude and longitude using the Haversine formula. The Earth's radius is assumed to be 6371000 meters.
 * It first converts the latitude and longitude differences between the two points into radians,
 * then computes the intermediate values required for the Haversine formula, and finally calculates
 * the distance between the two points on the Earth's surface.
 *
 * @param lat1 The latitude of the first point in degrees.
 * @param lon1 The longitude of the first point in degrees.
 * @param lat2 The latitude of the second point in degrees.
 * @param lon2 The longitude of the second point in degrees.
 *
 * @return The distance between the two points on the Earth's surface in meters.
 *
 * @note The Haversine formula is an approximation and assumes a spherical Earth, which may result
 * in slight inaccuracies for very long distances or near the poles.
 *
 * @complexity The time complexity of this function is O(1) since it involves simple arithmetic
 * operations and trigonometric functions that operate on constant-sized inputs.
*/
inline double haversine(const double lat1, const double lon1, const double lat2, const double lon2)
{
    const double earths_radius = 6371000;

    // Get the difference between our two points then convert the difference into radians
    const double delta_lat = convert_to_radians(lat2 - lat1);
    const double delta_lon = convert_to_radians(lon2 - lon1);

    const double converted_lat1 = convert_to_radians(lat1);
    const double converted_lat2 = convert_to_radians(lat2);

    const double aux = pow(sin(delta_lat / 2), 2) + cos(converted_lat1) * cos(converted_lat2) * pow(sin(delta_lon / 2), 2);

    const double c = 2 * atan2(sqrt(aux), sqrt(1 - aux));
    const double distance = earths_radius * c;

    return distance;
}


#endif //FEUP_DA_PROJECT_2_GRAPH_H
