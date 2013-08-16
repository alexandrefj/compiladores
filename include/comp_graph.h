#ifndef COMP_GRAPH_H
#define COMP_GRAPH_H

typedef struct comp_graph_t {
	int nodes;
	int** matrix;
} Graph;

void createGraph(Graph* graph, int nodes);
void destroyGraph(Graph* graph);
void addEdge(Graph *graph, int i, int f);
void printGraph(Graph *graph);

#endif
