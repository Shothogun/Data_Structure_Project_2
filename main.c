#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "Freq_prog.h"
#include "Dijkstra_prog.h"
#include "Prim_prog.h"
#include "IO.h"

// Main program (argc and argv as parameter, used for reading)
int main(int argc, char* argv[]){

	// Negative weight edge flag
	int flag;
	
	// M.S.T weight
	double weight = 0;
	
	//Graph's size
	unsigned int size;
	
	//Root's id
	unsigned int r;

	/*Verify command type
	(if program get less than two commands in terminal for frequence
	 , it don't uses source id)*/
	if ( argc > 2){
		r = atoi(argv[2]);
	}

	// Second Vertice from distance
	unsigned int end = 0;
	
	/* Verify commnad type(if number of commands greater than 3  
	in terminal, the program set end vertex's id for distance computation, 
	else program doesn't computes distance).
	*/
	
	if ( argc > 3)
	{
		end = atoi(argv[3]);
	}

	scanf("%u%*c", &size);

	// Graph's memory allocation
	Graph *G = Init_graph(size);
	
	//Graph's information reading
	flag = read(G);

	// Verifies command required
	if(strcmp(argv[1], "Dijkstra") == 0)
	{
		//Dijkstra doesn't works with negative edges
		if(flag == 1){
			printf("Nao é possivel processar arestas negativas\n");
			return 0;
		}
		// Computes Short-path tree
		Dijkstra(G, r);

		// Prints distance from source to end Vertex
		print_distance(G, end);

		// Prints total distance between both vertices
		printf("Distancia:%lf\n", G->Vertex[end-1].key);
	}
	else if (strcmp(argv[1], "MST") == 0)
	{
		// Computes Minimum spanning tree
		MST_Prim(G, r);

		// Prints M.S.T.
		print_MST(G, r, &weight);

		// Prints tree's weight
		printf("Peso Total:%lf\n", weight);
				
	}
	else if (strcmp(argv[1], "Freq") == 0)
	{
		// Combination of v vertices
		unsigned int total = (G->size)*(G->size-1)/2;

		// Creates histogram
		DFD_List* dfd_list = Freq (G->size, G);

		//Frequence printing
		printFreq(dfd_list, total);

		// DFD free
		freeDFD(dfd_list);
	}
	else
	{
		// Report command error 
		printf("ERROR");
	}

	

	/*
	for(unsigned int i=0; i<size; i++)
	{
		for(List_Node *v = G->Vertex[i].head->next ; v != NULL; v = v->next)
		{
			printf("Vertice (%u) adj (%u) w (%lf)\n", i+1, v->id, v->WT);
		}
		printf("parent (%u)\n", G->Vertex[i].pi);
	}
	*/

	//Graph's free allocation 
	Free_graph(G);

	return 0;
}
