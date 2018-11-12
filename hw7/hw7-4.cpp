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
		
		checkListCapacity(i, positionJ, distance, listCount, listMaxSize);
	
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

		route[k] = new int[routeCount];
		for(int i=0; i<routeCount; i++){
			cin >> route[k][i];	
		}
	
		int* pathVisitedNode = new int [MAX_PATH_SIZE];
		int* pathVisitedNodeDistance = new int [MAX_PATH_SIZE];
		int pathVisitedNodeCount = 1;
		pathVisitedNode[0] = route[k][0];
		pathVisitedNodeDistance[0] = 0;
		//check route
		for(int i=1; i<routeCount; i++){
			
			int start = route[k][i-1];
			int dest = route[k][i];
			//cout << "start and dest: " << start << " " << dest << endl;
			//if visited, get the best distance
			int bestStartDist = getNodeAccumulateDistance(start, pathVisitedNode, pathVisitedNodeDistance, pathVisitedNodeCount);
			int bestDestDist = getNodeAccumulateDistance(dest, pathVisitedNode, pathVisitedNodeDistance, pathVisitedNodeCount);
			int pathDistance = isConnected(start, dest, positionJ, distance, listCount);
			//cout << "dist " << bestStartDist << " " << bestDestDist << " " << pathDistance <<endl;
			if(pathDistance==-1){
				// no link
				routeDistnace[k] = -1;
				break;
			}
			else{
				int newDestDist = 0;
				if(bestDestDist<0){
					// not visited
					newDestDist = bestStartDist + pathDistance;	
				}
				else if(bestStartDist + pathDistance < bestDestDist){
					//shorter distance
							
				}
				else{
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
		
		delete[] distance[i];
		delete[] positionJ[i];
		
		distance[i] = newDistanceList;
		positionJ[i] = newpositionJList;
		
		newDistanceList = NULL;
		newpositionJList = NULL;
	}
}

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

int getNodeAccumulateDistance(int dest, int* nodes, int* distance, int count){
			
	for(int i=0; i<count; i++){
		if(nodes[i]==dest){
			//cout << "node " << dest << " distance " << distance[i] << endl;
			return distance[i];
		}
	}		
	return -1;
}

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
