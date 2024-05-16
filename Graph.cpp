#include <valarray>
#include <stack>
#include "Graph.h"

/************************* Vertex  **************************/

// Constructor for Vertex with only id
Vertex::Vertex(int id) : id(id) {}

// Constructor for Vertex with id and coordinates
Vertex::Vertex(int id, double longitude, double latitude) : id(id), longitude(longitude), latitude(latitude) {}

// Overloaded less than operator for comparing vertices based on distance
bool Vertex::operator<(Vertex & vertex) const {
    return this->dist < vertex.dist;
}

// Getter for vertex id
int Vertex::getId() const {
    return this->id;
}

// Getter for vertex longitude
double Vertex::getLongitude() const {
    return this->longitude;
}

// Getter for vertex latitude
double Vertex::getLatitude() const {
    return this->latitude;
}

// Getter for adjacent vertices
unordered_map<int, Edge *> Vertex::getAdj() const {
    return this->adj;
}

// Getter for visited status
bool Vertex::isVisited() const {
    return this->visited;
}

// Getter for shortest path
Vertex *Vertex::getPath() const {
    return this->path;
}

// Getter for distance from source
double Vertex::getDist() const {
    return this->dist;
}

// Setter for distance from source
void Vertex::setDist(double value) {
    this->dist = value;
}

// Setter for visited status
void Vertex::setVisited(bool isVisited) {
    this->visited = isVisited;
}

// Setter for shortest path
void Vertex::setPath(Vertex *newPath) {
    this->path = newPath;
}

// Method to add an edge to the vertex
Edge * Vertex::addEdge(Vertex *dest, double w) {
    auto newEdge = new Edge(this, dest, w);
    adj.insert({dest->getId(), newEdge});
    return newEdge;
}

// Method to find an edge given the destination vertex id
Edge * Vertex::findEdge(int destId) {
    auto it = this->adj.find(destId);
    if (it != this->adj.end()) {
        return it->second;
    }
    return nullptr;
}

/********************** Edge  ****************************/

// Constructor for Edge
Edge::Edge(Vertex *orig, Vertex *dest, double weight) : orig(orig), dest(dest), weight(weight) {}

// Getter for destination vertex
Vertex * Edge::getDest() const {
    return this->dest;
}

// Getter for edge weight
double Edge::getWeight() const {
    return this->weight;
}

// Getter for origin vertex
Vertex * Edge::getOrig() const {
    return this->orig;
}

// Getter for reverse edge
Edge *Edge::getReverse() const {
    return this->reverse;
}

// Setter for reverse edge
void Edge::setReverse(Edge *reverseEdge) {
    this->reverse = reverseEdge;
}


/********************** Graph  ****************************/

// Method to find a vertex in the graph given its ID
Vertex *Graph::findVertex(int id) const {
    auto it = this->vertices.find(id);
    if (it != this->vertices.end()) {
        return it->second;
    }
    return nullptr;
}

// Method to add a vertex to the graph
bool Graph::addVertex(int id) {
    if(findVertex(id) == nullptr) {
        auto *newVertex = new Vertex(id);
        this->vertices.insert({id, newVertex});
        return true;
    }
    return false;
}

// Method to add a vertex with coordinates to the graph
bool Graph::addVertex(int id, double longitude, double latitude) {
    if(findVertex(id) == nullptr) {
        auto *newVertex = new Vertex(id, longitude, latitude);
        this->vertices.insert({id, newVertex});
        return true;
    }
    return false;
}

// Method to add a directed edge between two vertices
bool Graph::addEdge(int source, int dest, double w) const {
    Vertex *originVertex = findVertex(source);
    Vertex *destVertex = findVertex(dest);

    if (originVertex && destVertex) {
        auto e1 = originVertex->addEdge(destVertex, w);
        auto e2 = destVertex->findEdge(originVertex->getId());

        if(e2 != nullptr) {
            if(e1->getWeight() == e2->getWeight()) {
                e1->setReverse(e2);
                e2->setReverse(e1);
            }
        }
        return true;
    }

    return false;
}

// Method to add a bidirectional edge between two vertices
bool Graph::addBidirectionalEdge(int source, int dest, double w) const {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w);
    auto e2 = v2->addEdge(v1, w);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

// Method to get the vertex set of the graph
unordered_map<int, Vertex *> Graph::getVertexSet() const {
    return this->vertices;
}

// Method to get the weight of an edge between two vertices
double Graph::getEdgeWeight(Vertex* source, Vertex* dest) {
    Edge* e = source->findEdge(dest->getId());
    if (!e) {
        // If the edge is not found, calculate the distance using haversine formula
        if (source->getLongitude() == numeric_limits<double>::max() ||
            source->getLatitude() == numeric_limits<double>::max() ||
            dest->getLongitude() == numeric_limits<double>::max() ||
            dest->getLatitude() == numeric_limits<double>::max())
            throw runtime_error("Edge not found");
        return haversine(source->getLatitude(), source->getLongitude(), dest->getLatitude(), dest->getLongitude());
    } else {
        return e->getWeight();
    }
}

// Method to perform TSP using backtracking
void Graph::TSPBacktracking(Vertex *currentVertex, int destId, int count, double cost, double &res) {

    // If all vertices are visited, check for return edge to the starting vertex and update the result
    if(count == this->vertices.size()) {
        Edge *finalEdge = currentVertex->findEdge(destId);
        if(finalEdge) res = min(res, cost + finalEdge->getWeight());
        return;
    }

    // Traverse through adjacent vertices and recursively explore possible paths
    for(auto pair : currentVertex->getAdj()) {
        Edge *e = pair.second;
        Vertex *v = e->getDest();
        if(!v->isVisited()) {
            v->setVisited(true);
            TSPBacktracking(v, destId, count + 1, cost + e->getWeight(), res);
            v->setVisited(false);
        }
    }
}

// Method to perform TSP using triangularization
void Graph::TSPTriangular(double &res) {
    // Perform Prim's algorithm to get minimum spanning tree
    this->prim();

    // Perform preorder traversal to get vertices in a specific order
    vector<Vertex *> preorder;
    preorderTraversal(findVertex(0), preorder, (int) vertices.size());

    // Calculate total weight of the Hamiltonian cycle
    for (size_t i = 0; i < preorder.size() - 1; ++i) {
        Vertex *v = preorder[i];
        Vertex *u = preorder[i+1];
        res += getEdgeWeight(v, u);
    }

    Vertex *v = preorder[preorder.size() - 1];
    Vertex *u = preorder[0];
    res += getEdgeWeight(v, u);
}

// Method to perform Prim's algorithm for minimum spanning tree
void Graph::prim() {
    if (vertices.empty()) return;

    // Initialize distances, paths, and visited flags for vertices
    for (auto pair : vertices) {
        Vertex *v = pair.second;
        v->setDist(numeric_limits<double>::max());
        v->setPath(nullptr);
        v->setVisited(false);
    }

    // Start with a random vertex
    Vertex* s = findVertex(0);

    s->setDist(0);
    MutablePriorityQueue<Vertex> q;
    q.insert(s);

    // Main loop of Prim's algorithm
    while (!q.empty()) {
        auto v = q.extractMin();
        v->setVisited(true);

        // Traverse through adjacent vertices and update distances
        for (auto pair : vertices) {
            Vertex *u = pair.second;
            if(u->getId() == v->getId()) continue;

            double weight = getEdgeWeight(v, u);

            if (!u->isVisited()) {
                double oldDist = u->getDist();

                if (weight < oldDist) {
                    u->setDist(weight);
                    u->setPath(v);

                    if (oldDist == numeric_limits<double>::max()) q.insert(u);
                    else q.decreaseKey(u);
                }
            }
        }
    }
}

// Method to perform preorder traversal of the minimum spanning tree
void Graph::preorderTraversal(Vertex *v, std::vector<Vertex *> &preorder, int n) {
    preorder.push_back(v);

    // Traverse recursively through the tree
    for (auto pair : vertices) {
        Vertex *u = pair.second;
        if(!u->getPath() || u->getPath()->getId() != v->getId()) continue;

        if(preorder.size() == n) return;

        preorderTraversal(u, preorder, n);
    }
}

// Method to solve TSP using nearest neighbor heuristic
void Graph::TSPNearestNeighbor(double &res) {
    // Initialize visited flag for all vertices
    for (auto& pair : vertices) {
        pair.second->setVisited(false);
    }

    // Start from a random vertex
    int count = 0;
    Vertex* v = findVertex(0);
    double currentWeight;
    Vertex* nearestNeighbor = nullptr;

    // Main loop of the nearest neighbor heuristic
    while (count < vertices.size()) {
        currentWeight = numeric_limits<double>::max();

        // Find the nearest unvisited neighbor
        for (auto& pair : vertices) {
            Vertex* u = pair.second;

            if (u->isVisited()) continue;

            double weight = getEdgeWeight(v, u);

            if (currentWeight > weight) {
                currentWeight = weight;
                nearestNeighbor = u;
            }
        }

        // Handle cases where no neighbor is found
        if(!nearestNeighbor) throw runtime_error("No neighbour vertex found!");
        nearestNeighbor->setVisited(true);
        res += currentWeight;
        v = nearestNeighbor;

        count++;
    }

    // Add the edge back to the starting vertex to complete the cycle
    Vertex *u = findVertex(0);
    res += getEdgeWeight(v, u);
}

// Method to solve TSP using real-world nearest neighbor heuristic
void Graph::TSPRealWorldNearestNeighbor(double &res, int startingVertexId) {
    // Initialize visited flag for all vertices
    for (auto& pair : vertices) {
        pair.second->setVisited(false);
    }

    // Start from a specified vertex
    int count = 0;
    Vertex* v = findVertex(startingVertexId);
    double currentWeight;
    Vertex* nearestNeighbor = nullptr;

    // Main loop of the real-world nearest neighbor heuristic
    while (count < vertices.size()) {
        currentWeight = numeric_limits<double>::max();

        // Find the nearest unvisited neighbor considering real-world distances
        for (auto& pair : vertices) {
            Vertex* u = pair.second;

            if (u->isVisited()) continue;

            Edge* e = v->findEdge(u->getId());

            double weight = numeric_limits<double>::max();

            if (e) weight = e->getWeight();

            if (currentWeight > weight) {
                currentWeight = weight;
                nearestNeighbor = u;
            }
        }

        // Handle cases where no neighbor is found or no path is found
        if (!nearestNeighbor) throw runtime_error("No neighbour vertex found!");
        nearestNeighbor->setVisited(true);

        if (currentWeight >= numeric_limits<double>::max()) throw runtime_error("No path found!");

        res += currentWeight;
        v = nearestNeighbor;

        count++;
    }

    // Add the edge back to the starting vertex to complete the cycle
    Edge* e = v->findEdge(0);
    double weight = numeric_limits<double>::max();
    if (e) weight = e->getWeight();

    res += weight;

    if (res >= numeric_limits<double>::max()) throw runtime_error("No path found!");
}
