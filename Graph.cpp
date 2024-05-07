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

unordered_map<int, Edge *> Vertex::getAdj() const {
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
    for (auto pair: this->getAdj()) outFlow += pair.second->getFlow();

    if((inFlow > 0) || (outFlow > 0)) return true;
    return false;
}

void Vertex::setFlow(double value) {
    this->flow = value;
}

void Vertex::updateFlow() {
    double incomingFlow = 0;
    if(this->incoming.empty()) {
        for (auto pair: this->adj) {
            incomingFlow += pair.second->getFlow();
        }
    }
    else {
        for (auto e: this->incoming) {
            incomingFlow += e->getFlow();
        }
    }
    this->flow = incomingFlow;
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

void Vertex::setPath(Edge *newPath) {
    this->path = newPath;
}

Edge * Vertex::addEdge(Vertex *dest, double w, double f) {
    auto newEdge = new Edge(this, dest, w);
    newEdge->setFlow(f);
    adj.insert({dest->getId(), newEdge});
    dest->incoming.push_back(newEdge);
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

double Edge::getFlow() const {
    return this->flow;
}

void Edge::setReverse(Edge *reverseEdge) {
    this->reverse = reverseEdge;
}

void Edge::setFlow(double newFlow) {
    this->flow = newFlow;
}

bool Edge::getSelected() const {
    return this->selected;
}

void Edge::setSelected(bool value) {
    this->selected = value;
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

bool Graph::addEdge(int source, int dest, double w, double f) const {
    Vertex *originVertex = findVertex(source);
    Vertex *destVertex = findVertex(dest);

    if (originVertex && destVertex) {
        auto e1 = originVertex->addEdge(destVertex, w, f);
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

bool Graph::addBidirectionalEdge(int source, int dest, double w, double flow, double reverseFlow) const {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w, flow);
    auto e2 = v2->addEdge(v1, w, reverseFlow);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

unordered_map<int, Vertex *> Graph::getVertexSet() const {
    return this->vertices;
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

    for(const auto pair : vertices) {
        Vertex *v = pair.second;
        Edge *e = v->getPath();
        if ( e != nullptr )
            e->setSelected(true);
        // cout << v->getId() << " " << endl;
    }

    preorderTraversal(findVertex(0), preorder, (int) vertices.size());

    for (size_t i = 0; i < preorder.size() - 1; ++i) {
        Vertex *v = preorder[i];
        Vertex *u = preorder[i+1];
        //cout << u->getId() << " " << i << endl;
        res += v->findEdge(u->getId())->getWeight();
    }

    Vertex *v = preorder[preorder.size() - 1];
    res += v->findEdge(0)->getWeight();
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

            Edge *e = v->findEdge(u->getId());

            if  (!e) {
                if (v->getLongitude() == numeric_limits<double>::max() ||
                    v->getLatitude() == numeric_limits<double>::max())
                    throw runtime_error("Edge not found");
                double weight = haversine(v->getLatitude(), v->getLongitude(), u->getLatitude(), u->getLongitude());

                this->addBidirectionalEdge(v->getId(), u->getId(), weight);
                e = v->findEdge(u->getId());
            }

            if (!u->isVisited()) {
                double oldDist = u->getDist();

                if (e->getWeight() < oldDist) {
                    u->setDist(e->getWeight());
                    u->setPath(e);

                    if (oldDist == numeric_limits<double>::max()) q.insert(u);
                    else q.decreaseKey(u);
                }
            }
        }
    }
}
