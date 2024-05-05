#include <valarray>
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

vector<Edge *> Vertex::getAdj() const {
    return this->adj;
}

bool Vertex::isVisited() const {
    return this->visited;
}

Edge *Vertex::getPath() const {
    return this->path;
}

vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}

double Vertex::getFlow() const {
    return this->flow;
}

bool Vertex::hasFlow() const {
    double inFlow = 0;
    double outFlow = 0;

    for (auto e: this->getIncoming()) inFlow += e->getFlow();
    for (auto e: this->getAdj()) outFlow += e->getFlow();

    if((inFlow > 0) || (outFlow > 0)) return true;
    return false;
}

void Vertex::setFlow(double value) {
    this->flow = value;
}

void Vertex::updateFlow() {
    double incomingFlow = 0;
    if(this->incoming.empty()) {
        for (auto e: this->adj) {
            incomingFlow += e->getFlow();
        }
    }
    else {
        for (auto e: this->incoming) {
            incomingFlow += e->getFlow();
        }
    }
    this->flow = incomingFlow;
}

void Vertex::setVisited(bool isVisited) {
    this->visited = isVisited;
}

void Vertex::setPath(Edge *newPath) {
    this->path = newPath;
}

Edge * Vertex::addEdge(Vertex *dest, double c, double f) {
    auto newEdge = new Edge(this, dest, c);
    newEdge->setFlow(f);
    adj.push_back(newEdge);
    dest->incoming.push_back(newEdge);
    return newEdge;
}

Edge * Vertex::findEdge(Vertex *destVertex) {
    for(auto e : adj) {
        Vertex *dest = e->getDest();
        if(dest->getId() == destVertex->getId()) {
            return e;
        }
    }
    return nullptr;
}

/********************** Edge  ****************************/

Edge::Edge(Vertex *orig, Vertex *dest, double capacity) : orig(orig), dest(dest), capacity(capacity) {}

Vertex * Edge::getDest() const {
    return this->dest;
}

double Edge::getCapacity() const {
    return this->capacity;
}

Vertex * Edge::getOrig() const {
    return this->orig;
}

Edge *Edge::getReverse() const {
    return this->reverse;
}

double Edge::getFlow() const {
    return this->flow;
}

void Edge::setReverse(Edge *reverseEdge) {
    this->reverse = reverseEdge;
}

void Edge::setFlow(double newFlow) {
    this->flow = newFlow;
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

bool Graph::addEdge(int source, int dest, double c, double f) const {
    Vertex *originVertex = findVertex(source);
    Vertex *destVertex = findVertex(dest);

    if (originVertex && destVertex) {
        auto e1 = originVertex->addEdge(destVertex, c, f);
        auto e2 = destVertex->findEdge(originVertex);

        if(e2 != nullptr) {
            if(e1->getCapacity() == e2->getCapacity()) {
                e1->setReverse(e2);
                e2->setReverse(e1);
            }
        }
        return true;
    }

    return false;
}

bool Graph::addBidirectionalEdge(int source, int dest, double c, double flow, double reverseFlow) const {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, c, flow);
    auto e2 = v2->addEdge(v1, c, reverseFlow);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

unordered_map<int, Vertex *> Graph::getVertexSet() const {
    return this->vertices;
}
