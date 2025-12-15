//
// Algoritmos e Estruturas de Dados --- 2025/2026
//
// Joaquim Madeira - Nov 2025
//
// GraphDominatingSets - Computing Vertex Dominating Sets for UNDIRECTED graphs
//

// Student Name :
// Student Number :
// Student Name :
// Student Number :

/*** COMPLETE THE GraphIsDominatingSet FUNCTION ***/
/*** COMPLETE THE GraphMinDominatingSet FUNCTION ***/
/*** COMPLETE THE GraphMinWeightDominatingSet FUNCTION ***/

#include "GraphDominatingSets.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "IndicesSet.h"
#include "instrumentation.h"

//
// TO BE COMPLETED
//
// Check if the given set is a dominating set for the graph
// Return 1 if true, or 0 otherwise
//
// A dominating set is a set of graph vertices such that every other
// graph vertex not in the set is adjacent to a graph vertex in the set
//
int GraphIsDominatingSet(const Graph* g, IndicesSet* vertSet) {
  assert(g != NULL);
  assert(GraphIsDigraph(g) == 0);
  assert(IndicesSetIsEmpty(vertSet) == 0);

  // If the graph is empty, any non-empty set is a dominating set.
  if (GraphGetNumVertices(g) == 0) {
    return 1;
  }
  
  IndicesSet* allVertices = GraphGetSetVertices(g);

  IndicesSet* coveredVertices = IndicesSetCreateCopy(vertSet);

  int v = IndicesSetGetFirstElem(vertSet);
  while (v != -1)
  {
    IndicesSet* adjacents = GraphGetSetAdjacentsTo(g, v);

    IndicesSetUnion(coveredVertices, adjacents);

    IndicesSetDestroy(&adjacents);
    v = IndicesSetGetNextElem(vertSet);
  }
  

  int isDominating = IndicesSetIsEqual(coveredVertices, allVertices);

  IndicesSetDestroy(&allVertices);
  IndicesSetDestroy(&coveredVertices);

  return isDominating;
}

//
// TO BE COMPLETED
//
// Compute a MIN VERTEX DOMINATING SET of the graph
// using an EXHAUSTIVE SEARCH approach
// Return the/a dominating set
//
IndicesSet* GraphComputeMinDominatingSet(const Graph* g) {
  assert(g != NULL);
  assert(GraphIsDigraph(g) == 0);

  //
  // TO BE COMPLETED
  //

  // Change this according to your algorithm
  IndicesSet* result = IndicesSetCreateEmpty(GraphGetVertexRange(g));

  return result;
}

//
// TO BE COMPLETED
//
// Compute a MIN WEIGHT VERTEX DOMINATING SET of the graph
// using an EXHAUSTIVE SEARCH approach
// Return the dominating set
//
IndicesSet* GraphComputeMinWeightDominatingSet(const Graph* g) {
  assert(g != NULL);
  assert(GraphIsDigraph(g) == 0);

  //
  // TO BE COMPLETED
  //

  // Change this according to your algorithm
  IndicesSet* result = IndicesSetCreateEmpty(GraphGetVertexRange(g));

  return result;
}
