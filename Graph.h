#ifndef FEUP_DA_PROJECT_2_GRAPH_H
#define FEUP_DA_PROJECT_2_GRAPH_H

#include "data_structures/MutablePriorityQueue.h"

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cmath>
#include <algorithm>
#include <unordered_map>

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

    double flow = 0;

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    double dist = 0;
    Edge *path = nullptr;

    vector<Edge *> incoming; // incoming edges
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
     * @return Pointer to the path edge.
     */
    [[nodiscard]] Edge *getPath() const;

    /**
     * @brief Get the incoming edges of the vertex.
     *
     * @return Vector of pointers to incoming edges.
     */
    [[nodiscard]] vector<Edge *> getIncoming() const;

    /**
     * @brief Get the flow value associated with the vertex.
     *
     * @return The flow value of the vertex.
     */
    [[nodiscard]] double getFlow() const;

    /**
     * @brief Check if the vertex has non-zero flow.
     *
     * @return True if the vertex has non-zero flow, otherwise false.
     *
     * @complexity O(E)
     */
    [[nodiscard]] bool hasFlow() const;

    /**
     * @brief Set the flow value associated with the vertex.
     *
     * @param value The flow value to set.
     */
    void setFlow(double value);

    /**
     * @brief Update the flow value associated with the vertex based on incoming edges.
     *
     * @complexity O(n) where n is the number of incoming edges or, if there's no incoming edges the number of out edges.
     */
    void updateFlow();

    /**
     * @brief Set the visited status of the vertex.
     *
     * @param isVisited True if the vertex is visited, otherwise false.
     */
    void setVisited(bool isVisited);

    double getDist() const;

    void setDist(double value);

    /**
     * @brief Set the path associated with the vertex.
     *
     * @param newPath Pointer to the new path edge.
     */
    void setPath(Edge *newPath);

    /**
     * @brief Add an edge between this vertex and a destination vertex.
     *
     * @param dest Pointer to the destination vertex.
     * @param w Weight of the edge.
     * @param f Flow of the edge.
     *
     * @return Pointer to the newly added edge.
     */
    Edge * addEdge(Vertex *dest, double w, double f = 0);

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
    bool selected = false;

    double flow{}; // for flow-related problems

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
     * @brief Get the flow associated with the edge.
     *
     * @return The flow of the edge.
     *
     */
    [[nodiscard]] double getFlow() const;

    /**
     * @brief Set the reverse edge associated with this edge.
     *
     * @param reverseEdge Pointer to the reverse edge to set.
     */
    void setReverse(Edge *reverseEdge);

    /**
     * @brief Set the flow of the edge.
     *
     * @param newFlow The new flow value to set.
     */
    void setFlow(double newFlow);

    bool getSelected() const;

    void setSelected(bool value);
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
     * @param f The flow through the edge from source to dest.
     *
     * @return True if the edge is successfully added, false otherwise.
     *
     * @complexity The time complexity of this function depends on the time complexity of finding
     * vertices in the graph, adding edges to the vertices, and setting reverse pointers, all of which
     * are O(1) in the worst case.
     */
    bool addEdge(int source, int dest, double w, double f = 0) const;

    /**
     * @brief Adds a bidirectional edge between two vertices in the graph.
     *
     * @details This function adds a bidirectional edge between the vertices with the given source and
     * destination ids. If either of the vertices does not exist in the graph, the function returns
     * false, indicating that the edge could not be added. Otherwise, it creates two edges: one from
     * source to dest and another from dest to source, each with the specified weight and flow.
     * Additionally, it sets the reverse pointers for the edges to maintain bidirectionality.
     *
     * @param source The id of the source vertex.
     * @param dest The id of the destination vertex.
     * @param w The weight of the edge.
     * @param flow The flow through the edge from source to dest.
     * @param reverseFlow The flow through the reverse edge from dest to source.
     *
     * @return True if the bidirectional edge is successfully added, false otherwise.
     *
     * @complexity The time complexity of this function depends on the time complexity of finding
     * vertices in the graph, adding edges to the vertices, and setting reverse pointers, all of which
     * are O(1) in the worst case.
     */
    bool addBidirectionalEdge(int source, int dest, double w, double flow = 0, double reverseFlow = 0) const;

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

    void TSPBacktracking(Vertex *currentVertex, int destId, int count, double cost, double &res);

    void TSPTriangular(double &res);

    void prim();
};

// AUX functions

inline void preorderTraversal(Vertex *v, std::vector<Vertex *> &preorder, int n) {
    preorder.push_back(v);

    for (auto pair : v->getAdj()) {
        Edge *e = pair.second;

        if(!e->getSelected()) continue;
        Vertex *w = e->getDest();

        if(preorder.size() == n) return;

        preorderTraversal(w, preorder, n);
    }
}

inline double convert_to_radians(const double coord)
{
    return coord * (M_PI / 180);
}

inline double haversine(const double lat1, const double lon1, const double lat2, const double lon2)
{
    const double earths_radius = 6371;

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
