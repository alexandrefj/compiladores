#include <stdio.h>
#include <stdlib.h>

#include "comp_graph.h"

void createGraph(Graph* graph, int nodes) {
	graph->matrix = calloc(nodes, sizeof(int*));
	graph->matrix[0] = NULL;

	int i;

	for (i = 1; i < nodes; i++) {
		graph->matrix = calloc(i, sizeof(int));
	}

	graph->nodes = nodes;
}

void destroyGraph(Graph* graph) {
	int i;

	for (i = 1; i < graph->nodes; i++) {
		free(graph->matrix[i]);
	}

	free(graph->matrix);
}

void addEdge(Graph *graph, int i, int f) {
	if (i > f) {
		graph->matrix[i][f] = 1;
	} else {
		graph->matrix[f][i] = 1;
	}
}

void printGraph(Graph *graph) {
	int i, j;

	for (i = 0; i < graph->nodes; i++) {
		for (j = 0; j < graph->nodes; j++) {
			printf("%d ", graph->matrix[i][j]);
		}
		printf("\n");
	}
}
