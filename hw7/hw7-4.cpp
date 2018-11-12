#include <iostream>
#include <iomanip> 
using namespace std;

const int LIST_SIZE_ITERATE = 50;
const int MAX_PATH_SIZE = 50;

void checkListCapacity(int i, int** positionJ, int** distance, int* listCount, int* listMaxSize);
void printAdjList(int** positionJ, int** distance, int n ,int* listCount);
int isConnected(int i, int j ,int** positionJ, int** distance, int* listCount);
int getNodeAccumulateDistance(int id, int* route, int* accuDistList, int listSize);
int storeNodeAcculateDistance(int nodeId, int newDist, int* nodes, int* distanceList,  int count);

int main(){
	
	//initialization
	int n=0, m=0, routeNum=0;
	cin >> n >> m >> routeNum;
	n = n+1;
	//dynamic array
	int** distance = new int*[n];
	int** positionJ = new int*[n];
	int* listMaxSize = new int[n];
	int* listCount = new int[n];
	
	int** route = new int*[routeNum];
	int* routeDistnace = new int[routeNum];
	 
	for(int i = 0; i < n; ++i){
		distance[i] = NULL;
		positionJ[i] = NULL;
		listMaxSize[i] = 0;
		listCount[i] = 0;
	}
	
	for(int i=0; i<routeNum; i++){
		route[i] = NULL;
		routeDistnace[i] = 0;
	}
	
	//insert new link
	for(int k=0; k<m; k++){
		
		// new link
		int i=0, j=0, d=0;
		cin >> i >> j >> d;
		
		//check list size if not enough then expand
		checkListCapacity(i, positionJ, distance, listCount, listMaxSize);
	
		//insert
		int newJ = listCount[i];
		distance[i][newJ] = d;
		positionJ[i][newJ] = j;
		listCount[i]++;
	}
	
	//printAdjList(positionJ, distance, n ,listCount);

	//route input
	for(int k=0; k<routeNum; k++){
		int routeCount = 0;
		cin >> routeCount;

		//insert
		route[k] = new int[routeCount];
		for(int i=0; i<routeCount; i++){
			cin >> route[k][i];	
		}
	
		//distance record of nodes in path
		int* pathVisitedNode = new int [MAX_PATH_SIZE];
		int* pathVisitedNodeDistance = new int [MAX_PATH_SIZE];
		int pathVisitedNodeCount = 1;
		pathVisitedNode[0] = route[k][0];
		pathVisitedNodeDistance[0] = 0;
		
		//check route
		for(int i=1; i<routeCount; i++){
			
			int start = route[k][i-1];
			int dest = route[k][i];
			
			//if visited, get the best distance
			int bestStartDist = getNodeAccumulateDistance(start, pathVisitedNode, pathVisitedNodeDistance, pathVisitedNodeCount);
			int bestDestDist = getNodeAccumulateDistance(dest, pathVisitedNode, pathVisitedNodeDistance, pathVisitedNodeCount);
			int pathDistance = isConnected(start, dest, positionJ, distance, listCount);
		
			if(pathDistance==-1){
				// no link
				routeDistnace[k] = -1;
				break;
			}
			else{
				// link exist then check whether visited
				int newDestDist = 0;
				if(bestDestDist<0){
					// not visited
					newDestDist = bestStartDist + pathDistance;	
				}
				else if(bestStartDist + pathDistance < bestDestDist){
					// new route is shorter
					newDestDist = bestStartDist + pathDistance;		
				}
				else{
					// new route in
					newDestDist = bestDestDist;
				}
				//store new distance
				pathVisitedNodeCount = storeNodeAcculateDistance(dest, newDestDist, pathVisitedNode, pathVisitedNodeDistance, pathVisitedNodeCount);
				routeDistnace[k] = newDestDist;
			}	
		}
		//cout << "route " << k << " route distance " << routeDistnace[k] << endl << endl;
		
	}
	
	//output
	for(int k=0; k<routeNum; k++){
		if(k != routeNum-1){
			cout << routeDistnace[k] << " ";
		}
		else{
			cout << routeDistnace[k] << endl; 
		}
	}
} 

//check list size if not enough then expand
void checkListCapacity(int i, int** positionJ, int** distance, int* listCount, int* listMaxSize){
	
	//if not created crate adjacency list
	if(distance[i]==NULL){
		
		//create with size LIST_SIZE_ITERATE
		distance[i] = new int[LIST_SIZE_ITERATE];
		positionJ[i] = new int[LIST_SIZE_ITERATE];
		listMaxSize[i] = LIST_SIZE_ITERATE;
	}
	else if(listCount[i]>=listMaxSize[i]){
		
		//create new one and cpoy
		int newListSize = listMaxSize[i] + LIST_SIZE_ITERATE;
		int *newDistanceList = new int[newListSize];
		int *newpositionJList = new int[newListSize];
		
		for(int j=0; j<listCount[i]; j++){
			newDistanceList[j] = distance[i][j];
			newpositionJList[j] = positionJ[i][j];
		}
		
		//delete old list
		delete[] distance[i];
		delete[] positionJ[i];
		
		distance[i] = newDistanceList;
		positionJ[i] = newpositionJList;
		
		newDistanceList = NULL;
		newpositionJList = NULL;
	}
}

//print adjacency list
void printAdjList(int** positionJ, int** distance, int n ,int* listCount){
	
	for(int i=0; i<n; i++){
		cout << "***************************" << endl;
		for(int j=0; j<listCount[i]; j++){
			cout << "(i,j) = " << i << " " << positionJ[i][j] << " " << distance[i][j] << endl;
		}
	}

}

//return distance
int isConnected(int i, int j ,int** positionJ, int** distance, int* listCount){
	
	for(int k=0; k<listCount[i]; k++){
		if(j == positionJ[i][k]){
			return distance[i][k];
		}
	}
	
	return -1;
}

//get node accumulated shorted distance from start
int getNodeAccumulateDistance(int dest, int* nodes, int* distance, int count){
			
	for(int i=0; i<count; i++){
		if(nodes[i]==dest){
			//cout << "node " << dest << " distance " << distance[i] << endl;
			return distance[i];
		}
	}		
	return -1;
}

//write node accumulated shorted distance from start
int storeNodeAcculateDistance(int nodeId, int newDist, int* nodes, int* distanceList,  int count){
	int ListId = count;
	//cout << "write accu " << nodeId << " " << newDist << endl;
	//exist
	for(int i=0; i<count; i++){
		if(nodes[i]==nodeId){
			
			distanceList[i] = newDist;
			return count;	
		}
	}		
	nodes[count] = nodeId;
	distanceList[count] = newDist;
	return count +1;
}
