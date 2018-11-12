#include <iostream>
#include <iomanip> 
using namespace std;

const int LIST_SIZE_ITERATE = 50;
const int MAX_PATH_SIZE = 50;

void checkListCapacity(int i, int** positionJ, int** distance, int* listCount, int* listMaxSize);
void printAdjList(int** positionJ, int** distance, int n ,int* listCount);
int isConnected(int i, int j ,int** positionJ, int** distance, int* listCount);

int main(){
	
	//initialization
	int n=0, m=0, routeNum=0;
	cin >> n >> m >> routeNum;
	//dynamic array
	int** distance = new int*[n];
	int** positionJ = new int*[n];
	int* listMaxSize = new int[n];
	int* listCount = new int[n];
	
	int** route = new int*[routeNum];
	int* routeDistnace = new int[routeNum];
	for(int i = 0; i < n; i++){
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
		int startId=0, destId=0, linkDist=0;
		cin >> startId >> destId >> linkDist;
		//cout << startId << " " <<destId << " "<< linkDist << endl; 
		checkListCapacity(startId, positionJ, distance, listCount, listMaxSize);
		int newJ = listCount[startId];
		distance[startId][newJ] = linkDist;
		positionJ[startId][newJ] = destId;
		listCount[startId]++;
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
		
		
		//check route
		for(int i=0; i<routeCount-1; i++){
			
			int start = route[k][i];
			int dest = route[k][i+1];
		
			int pathDistance = isConnected(start, dest, positionJ, distance, listCount);
			//cout << start << " " << dest << " "<< pathDistance << endl; 
			if(pathDistance != -1){
				routeDistnace[k] += pathDistance;
			}
			else{
				routeDistnace[k] = -1;
				break;
			}
		}
		
		
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
