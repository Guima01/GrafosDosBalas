#include "Node.h"
#include "Edge.h"
#include <iostream>

using namespace std;

/**************************************************************************************************
 * Defining the Node's methods
**************************************************************************************************/

// Constructor
Node::Node(int id){

    this->id = id;
    this->in_degree = 0;
    this->out_degree = 0;
    this->weight = 0;
    this->first_edge = nullptr;
    this->last_edge = nullptr;
    this->next_node = nullptr;

};

// Destructor
Node::~Node(){

    Edge* next_edge = this->first_edge;

    while(next_edge != nullptr){

        Edge* aux_edge = next_edge->getNextEdge();
        delete next_edge;
        next_edge = aux_edge;

    }

};

// Getters
Edge* Node::getFirstEdge(){

    return this->first_edge;

}

Edge* Node::getLastEdge(){

    return this->last_edge;

}

int Node::getId(){

    return this->id;

}

int Node::getInDegree(){

    return this->in_degree;

}

int Node::getOutDegree(){

    return this->out_degree;

}

float Node::getWeight(){

    return this->weight;

}

Node* Node::getNextNode(){

    return this->next_node;

}

// Setters

void Node::setNextNode(Node* next_node){

    this->next_node = next_node;

}

void Node::setWeight(float weight){

    this->weight = weight;

}

// Other methods
void Node::insertEdge(int target_id, float weight){
    // Verifies whether there are at least one edge in the node
    if(this->first_edge != nullptr){
        // Allocating the new edge and keeping the integrity of the edge list
        Edge* edge = new Edge(target_id);
        edge->setWeight(weight);
        this->last_edge->setNextEdge(edge);
        this->last_edge = edge;

    }
    else{
         // Allocating the new edge and keeping the integrity of the edge list
        this->first_edge = new Edge(target_id);
        this->first_edge->setWeight(weight);
        this->last_edge = this->first_edge;

    }

}

void Node::removeAllEdges(){
    // Verifies whether there are at least one edge in the node
    if(this->first_edge != nullptr){

        Edge* next = nullptr;
        Edge* aux = this->first_edge;
        // Removing all edges of the node
        while(aux != nullptr){

            next = aux->getNextEdge();
            delete aux;

        }

    }

    this->first_edge = this->last_edge = nullptr;

}

int Node::removeEdge(int id, bool directed, Node* target_node){
    // Verifies whether the edge to remove is in the node
    if(this->searchEdge(id)){

        Edge* aux = this->first_edge;
        Edge* previous = nullptr;
        // Searching for the edge to be removed
        while(aux->getTargetId() != id){

            previous = aux;
            aux = aux->getNextEdge();

        }
        // Keeping the integrity of the edge list
        if(previous != nullptr)
            previous->setNextEdge(aux->getNextEdge());

        else
            this->first_edge = aux->getNextEdge();

        if(aux == this->last_edge)
            this->last_edge = previous;

        if(aux->getNextEdge() == this->last_edge)
            this->last_edge = aux->getNextEdge();

        delete aux;
        // Verifies whether the graph is directed
        if(directed)
            this->decrementOutDegree();

        else{

            this->decrementInDegree();
            target_node->decrementInDegree();

        }

        return 1;

    }

    return 0;

}

bool Node::searchEdge(int target_id){
     // Verifies whether there are at least one edge in the node
    if(this->first_edge != nullptr){
        // Searching for a specific edge of target id equal to target id
        for(Edge* aux = this->first_edge; aux != nullptr; aux = aux->getNextEdge())
            if(aux->getTargetId() == target_id)
                return true;

    }

    return false;

}

void Node::incrementInDegree(){

    this->in_degree++;

}

void Node::incrementOutDegree(){

    this->out_degree++;

}

void Node::decrementInDegree(){

    this->in_degree--;

}

void Node::decrementOutDegree(){

    this->out_degree--;

}

Edge* Node::hasEdgeBetween(int target_id)
{

    for(Edge *auxEdge = this->first_edge; auxEdge != nullptr; auxEdge = auxEdge->getNextEdge())
    {
        if(auxEdge->getTargetId() == target_id)
            return auxEdge;
    }
    return nullptr;
}
