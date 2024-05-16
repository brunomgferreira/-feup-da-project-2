#include <valarray>
#include <stack>
#include "Graph.h"

/************************* Vertex  **************************/

Vertex::Vertex(int id) : id(id) {}

Vertex::Vertex(int id, double longitude, double latitude) : id(id), longitude(longitude), latitude(latitude) {}

bool Vertex::operator<(Vertex & vertex) const {
    return this->dist < vertex.dist;
}

int Vertex::getId() const {
    return this->id;
}

double Vertex::getLongitude() const {
    return this->longitude;
}

double Vertex::getLatitude() const {
    return this->latitude;
}

unordered_map<int, Edge *> Vertex::getAdj() const {
    return this->adj;
}

bool Vertex::isVisited() const {
    return this->visited;
}

Vertex *Vertex::getPath() const {
    return this->path;
}

double Vertex::getDist() const {
    return this->dist;
}

void Vertex::setDist(double value) {
    this->dist = value;
}

void Vertex::setVisited(bool isVisited) {
    this->visited = isVisited;
}

void Vertex::setPath(Vertex *newPath) {
    this->path = newPath;
}

Edge * Vertex::addEdge(Vertex *dest, double w) {
    auto newEdge = new Edge(this, dest, w);
    adj.insert({dest->getId(), newEdge});
    return newEdge;
}

Edge * Vertex::findEdge(int destId) {
    auto it = this->adj.find(destId);
    if (it != this->adj.end()) {
        return it->second;
    }
    return nullptr;
}

/********************** Edge  ****************************/

Edge::Edge(Vertex *orig, Vertex *dest, double weight) : orig(orig), dest(dest), weight(weight) {}

Vertex * Edge::getDest() const {
    return this->dest;
}

double Edge::getWeight() const {
    return this->weight;
}

Vertex * Edge::getOrig() const {
    return this->orig;
}

Edge *Edge::getReverse() const {
    return this->reverse;
}

void Edge::setReverse(Edge *reverseEdge) {
    this->reverse = reverseEdge;
}


/********************** Graph  ****************************/

Vertex *Graph::findVertex(int id) const {
    auto it = this->vertices.find(id);
    if (it != this->vertices.end()) {
        return it->second;
    }
    return nullptr;
}

bool Graph::addVertex(int id) {
    if(findVertex(id) == nullptr) {
        auto *newVertex = new Vertex(id);
        this->vertices.insert({id, newVertex});
        return true;
    }
    return false;
}

bool Graph::addVertex(int id, double longitude, double latitude) {
    if(findVertex(id) == nullptr) {
        auto *newVertex = new Vertex(id, longitude, latitude);
        this->vertices.insert({id, newVertex});
        return true;
    }
    return false;
}

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

unordered_map<int, Vertex *> Graph::getVertexSet() const {
    return this->vertices;
}

double Graph::getEdgeWeight(Vertex* source, Vertex* dest) {
    //cout << u->getId() << " " << i << endl;
    Edge* e = source->findEdge(dest->getId());
    if (!e) {
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

void Graph::TSPBacktracking(Vertex *currentVertex, int destId, int count, double cost, double &res) {

    if(count == this->vertices.size()) {
        Edge *finalEdge = currentVertex->findEdge(destId);
        if(finalEdge) res = min(res, cost + finalEdge->getWeight());
        return;
    }

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

void Graph::TSPTriangular(double &res) {
    this->prim();

    vector<Vertex *> preorder;

    preorderTraversal(findVertex(0), preorder, (int) vertices.size());

    for (size_t i = 0; i < preorder.size() - 1; ++i) {
        Vertex *v = preorder[i];
        Vertex *u = preorder[i+1];
        //cout << u->getId() << " " << i << endl;
        res += getEdgeWeight(v, u);
    }

    Vertex *v = preorder[preorder.size() - 1];
    Vertex *u = preorder[0];
    res += getEdgeWeight(v, u);
}

void Graph::prim() {
    if (vertices.empty()) return;

    for (auto pair : vertices) {
        Vertex *v = pair.second;
        v->setDist(numeric_limits<double>::max());
        v->setPath(nullptr);
        v->setVisited(false);
    }

    Vertex* s = findVertex(0);

    s->setDist(0);
    MutablePriorityQueue<Vertex> q;
    q.insert(s);

    while (!q.empty()) {
        auto v = q.extractMin();
        v->setVisited(true);

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

void Graph::preorderTraversal(Vertex *v, std::vector<Vertex *> &preorder, int n) {
    preorder.push_back(v);

    for (auto pair : vertices) {
        Vertex *u = pair.second;
        if(!u->getPath() || u->getPath()->getId() != v->getId()) continue;

        if(preorder.size() == n) return;

        preorderTraversal(u, preorder, n);
    }
}

void Graph::TSPNearestNeighbor(double &res) {
    for (auto& pair : vertices) {
        pair.second->setVisited(false);
    }

    int count = 0;
    Vertex* v = findVertex(0);
    double currentWeight;
    Vertex* nearestNeighbor = nullptr;

    while (count < vertices.size()) {
        currentWeight = numeric_limits<double>::max();

        for (auto& pair : vertices) {
            Vertex* u = pair.second;

            if (u->isVisited()) continue;

            double weight = getEdgeWeight(v, u);

            if (currentWeight > weight) {
                currentWeight = weight;
                nearestNeighbor = u;
            }
        }

        if(!nearestNeighbor) throw runtime_error("No neighbour vertex found!");
        nearestNeighbor->setVisited(true);
        res += currentWeight;
        v = nearestNeighbor;

        count++;
    }

    Vertex *u = findVertex(0);
    res += getEdgeWeight(v, u);
}

void Graph::TSPRealWorldNearestNeighbor(double &res) {
    for (auto& pair : vertices) {
        pair.second->setVisited(false);
    }

    int count = 0;
    Vertex* v = findVertex(0);
    double currentWeight;
    Vertex* nearestNeighbor = nullptr;

    while (count < vertices.size()) {
        currentWeight = numeric_limits<double>::max();

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

        if (!nearestNeighbor) throw runtime_error("No neighbour vertex found!");
        nearestNeighbor->setVisited(true);

        if (currentWeight >= numeric_limits<double>::max()) throw runtime_error("No path found!");

        res += currentWeight;
        v = nearestNeighbor;

        count++;
    }

    Edge* e = v->findEdge(0);
    double weight = numeric_limits<double>::max();
    if (e) weight = e->getWeight();

    res += weight;

    if (res >= numeric_limits<double>::max()) throw runtime_error("No path found!");
}
