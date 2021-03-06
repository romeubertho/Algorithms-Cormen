// Bellman-Ford.cpp : Defines the entry point for the console application.
/*
 * created by fireass @ 9/14/2014
 */

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#define NUMBER_VERTICES 5
#define NUMBER_EDGES 10

//adjacency link list
typedef struct Node* NodePointer;
typedef struct Node{
	int index;
	int iWeight;	//edge weight
	Node* ptrLink;
};
int i,j,k;

void PrintGraph(NodePointer *ptr){
	for(i=0;i<NUMBER_VERTICES;i++){
		printf("[%d]",i);
		NodePointer p = ptr[i];
		while(p) {
			printf("->[%d %d]",p->index,p->iWeight);
			p = p->ptrLink;
		}
		printf("\n");
	}
}

void GraphGeneration(NodePointer *ptr, int *arr){

	for(i=0;i<NUMBER_EDGES*3;i+=3){

		NodePointer temp = (NodePointer)malloc(sizeof(Node));
		temp->index = *(arr+i+1);
		temp->iWeight = *(arr+i+2);
		temp->ptrLink = NULL;
		
		if(!ptr[*(arr+i)]) ptr[*(arr+i)] = temp;
		else{
			NodePointer p = ptr[*(arr+i)];
			while(p->ptrLink) p = p->ptrLink;
			p->ptrLink = temp;
		}
	}
}

void BELLMAN_FORD(NodePointer* ptr){
	int iBound[NUMBER_VERTICES]; //upper bound
	iBound[0]=0;for(i=1;i<NUMBER_VERTICES;i++){iBound[i]=INT_MAX;}
	
	int predecessor[NUMBER_VERTICES]; predecessor[0] = 0;

	for(i=0;i<NUMBER_VERTICES;i++){
		NodePointer p = ptr[i];
		while(p){
			if(iBound[p->index]>p->iWeight+iBound[i]){
				iBound[p->index] = p->iWeight+iBound[i];
				predecessor[p->index] = i;
			}
			p=p->ptrLink;
		}
		
	}
	for(j=0;j<NUMBER_VERTICES;j++){
		printf("iBound[%d]=%d  ",j,iBound[j]); printf("predecessor[%d]=%d\n",j,predecessor[j]);
	}
	printf("shortest-path: [0]");

	int value = 0;
	int temp = 0;
	for(j=0;j<NUMBER_VERTICES;j++){
		for(i=1;i<NUMBER_VERTICES;i++){
			if(predecessor[i]==value){
				
				value = i;
				printf("->[%d]",value);
				break;
			}
		}
	}
}

int main(void) {
	
	NodePointer* N = (NodePointer*)malloc(NUMBER_VERTICES*sizeof(Node));
	for(i=0;i<NUMBER_VERTICES;i++) N[i] = NULL;

	//beginner, end, edge weight, this example is from algorithm book page 652
	int arrEdges[NUMBER_EDGES][3] = { 
		{0,1,6},{0,2,7},{1,2,8},{1,3,5},{1,4,-4},
		{2,4,9},{2,3,-3},{3,1,-2},{4,0,2},{4,3,7}
	};
	
	GraphGeneration(N,&arrEdges[0][0]);
	PrintGraph(N);
	BELLMAN_FORD(N);
	system("pause");
	return 0;
}
