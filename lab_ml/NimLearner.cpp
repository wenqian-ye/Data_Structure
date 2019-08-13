/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#include "NimLearner.h"
#include <ctime>


/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true, true) {
    /* Your code goes here! */


    // Create a new graph and insert vertices = startingTokens + 1 because of the extra "0"
    for(unsigned i = 0; i <= startingTokens; i++) {
        g_.insertVertexByLabel("p1-"+std::to_string(i));
        g_.insertVertexByLabel("p2-"+std::to_string(i));
    }

    // Not much use, only for playRandomGame easier to initialize
    startingVertex_ = g_.getVertexByLabel("p1-"+std::to_string(startingTokens));
    for(unsigned i = startingTokens; i > 1; i--){
        // Create Edges between player 1 and the two vertexes of player 2
        g_.insertEdge(g_.getVertexByLabel("p1-"+std::to_string(i)), g_.getVertexByLabel("p2-"+std::to_string(i-1)));
        g_.setEdgeWeight(g_.getVertexByLabel("p1-"+std::to_string(i)), g_.getVertexByLabel("p2-"+std::to_string(i-1)), 0);
        g_.insertEdge(g_.getVertexByLabel("p1-"+std::to_string(i)), g_.getVertexByLabel("p2-"+std::to_string(i-2)));
        g_.setEdgeWeight(g_.getVertexByLabel("p1-"+std::to_string(i)), g_.getVertexByLabel("p2-"+std::to_string(i-2)), 0);

        // Create Edges between player 2 and the two vertexes of player 1
        g_.insertEdge(g_.getVertexByLabel("p2-"+std::to_string(i)), g_.getVertexByLabel("p1-"+std::to_string(i-1)));
        g_.setEdgeWeight(g_.getVertexByLabel("p2-"+std::to_string(i)), g_.getVertexByLabel("p1-"+std::to_string(i-1)), 0);
        g_.insertEdge(g_.getVertexByLabel("p2-"+std::to_string(i)), g_.getVertexByLabel("p1-"+std::to_string(i-2)));
        g_.setEdgeWeight(g_.getVertexByLabel("p2-"+std::to_string(i)), g_.getVertexByLabel("p1-"+std::to_string(i-2)), 0);
    }

    // Create edges between player 1 and last two vertexof player 2
    g_.insertEdge(g_.getVertexByLabel("p1-1"), g_.getVertexByLabel("p2-0"));
    g_.setEdgeWeight(g_.getVertexByLabel("p1-1"), g_.getVertexByLabel("p2-0"), 0);

    // Create edges between player 1 and last two vertexof player 2
    g_.insertEdge(g_.getVertexByLabel("p2-1"), g_.getVertexByLabel("p1-0"));
    g_.setEdgeWeight(g_.getVertexByLabel("p2-1"), g_.getVertexByLabel("p1-0"), 0);

    //Update startingVertex_
    startingVertex_ = g_.getVertexByLabel("p1-"+std::to_string(startingTokens));
}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;
 /* Your code goes here! */
    Vertex start = startingVertex_;
    Vertex v;
    int r;
    while (!g_.getAdjacent(start).empty()){
        vector<Vertex> possible_next = g_.getAdjacent(start);
        r = rand() % (possible_next.size());
        v = possible_next.at(r);
        Edge e = g_.getEdge(start, v);
        path.push_back(e);
        start = v;
    }
  return path;
}

/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {
 /* Your code goes here! */
    bool tool;
    if (path.size()%2 == 0){//even, p2 win
        tool = true;
    }else{
        tool = false;
    }
    for (const Edge& e : path){
        if (tool){
            g_.setEdgeWeight(e.source, e.dest, g_.getEdgeWeight(e.source, e.dest)-1);
            tool = false;
        }else{
            g_.setEdgeWeight(e.source, e.dest, g_.getEdgeWeight(e.source, e.dest)+1);
            tool = true;
        }
    }
}

/**
 * Label the edges as "WIN" or "LOSE" based on a threshold.
 */
void NimLearner::labelEdgesFromThreshold(int threshold) {
  for (const Vertex & v : g_.getVertices()) {
    for (const Vertex & w : g_.getAdjacent(v)) {
      int weight = g_.getEdgeWeight(v, w);

      // Label all edges with positve weights as "WINPATH"
      if (weight > threshold)           { g_.setEdgeLabel(v, w, "WIN"); }
      else if (weight < -1 * threshold) { g_.setEdgeLabel(v, w, "LOSE"); }
    }
  }
}

/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
