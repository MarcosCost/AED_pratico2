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

// Compute a MIN VERTEX DOMINATING SET of the graph
// using an EXHAUSTIVE SEARCH approach
// Return the/a dominating set
//
IndicesSet* GraphComputeMinDominatingSet(const Graph* g) {
  assert(g != NULL);
  assert(GraphIsDigraph(g) == 0);

  if (GraphGetNumVertices(g) == 0) {
    return IndicesSetCreateEmpty(GraphGetVertexRange(g));
  }

  int vertex_range = GraphGetVertexRange(g);

  // Change this according to your algorithm
  IndicesSet* result = NULL;
  IndicesSet* allVertices =  GraphGetSetVertices(g);
  IndicesSet* iterator = IndicesSetCreateEmpty(vertex_range);
  int minsize = GraphGetNumVertices(g) + 1;

  do
  {
    IndicesSet* candidate = IndicesSetCreateCopy(iterator);
    IndicesSetIntersection(candidate, allVertices);

    if (IndicesSetIsEmpty(candidate))
    {
      IndicesSetDestroy(&candidate);
      continue;
    }
    
    

    if (GraphIsDominatingSet(g, candidate))
    {
      int currentSize = IndicesSetGetNumElems(candidate);
      if (currentSize < minsize)
      {
        minsize = currentSize;
        if (result != NULL)
        {
          IndicesSetDestroy(&result);
        }
        result = IndicesSetCreateCopy(candidate);    
        if (minsize == 1)
        {
          IndicesSetDestroy(&candidate);
          break;
        }
        
      }
      
    }
    IndicesSetDestroy(&candidate);

  } while (IndicesSetNextSubset(iterator));
  

  IndicesSetDestroy(&allVertices);
  IndicesSetDestroy(&iterator);

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

  int vertex_range = GraphGetVertexRange(g);

  // The minimum weight dominating set for an empty graph is the empty set.
  if (GraphGetNumVertices(g) == 0) {
    return IndicesSetCreateEmpty(vertex_range);
  }

  IndicesSet* result = NULL;
  IndicesSet* allVertices = GraphGetSetVertices(g);
  IndicesSet* iterator = IndicesSetCreateEmpty(vertex_range);

  double* vertexWeights = GraphComputeVertexWeights(g);
  double minWeight = -1.0; 

  do {
    IndicesSet* candidate = IndicesSetCreateCopy(iterator);
    IndicesSetIntersection(candidate, allVertices);

    if (IndicesSetIsEmpty(candidate)) {
      IndicesSetDestroy(&candidate);
      continue;
    }

    if (GraphIsDominatingSet(g, candidate)) {
      double currentWeight = 0.0;
      int v = IndicesSetGetFirstElem(candidate);
      while (v != -1) {
        currentWeight += vertexWeights[v];
        v = IndicesSetGetNextElem(candidate);
      }

      if (minWeight < 0.0 || currentWeight < minWeight) {
        minWeight = currentWeight;
        if (result != NULL) {
          IndicesSetDestroy(&result);
        }
        result = IndicesSetCreateCopy(candidate);
      }
    }
    IndicesSetDestroy(&candidate);

  } while (IndicesSetNextSubset(iterator));

  free(vertexWeights);
  IndicesSetDestroy(&allVertices);
  IndicesSetDestroy(&iterator);

  return result;
}
