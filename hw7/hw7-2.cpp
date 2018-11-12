#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

struct RiskNode{
	int x;
	int y;
	int r;
	int p;
};   

struct Route{
	int x1;
	int y1;
	int x2;
	int y2;
	double risk;
};

void inputNodeAndRoute(RiskNode riskNode[], int m, Route route[], int routeNum);
void calculateRouteRisk(RiskNode riskNode[], int m, Route route[], int routeNum);
void printResult(Route route[], int routeNum);
double distance(double x1, double y1, int x2, int y2);
double risk(double x1, double y1, RiskNode &riskNode);
double allRisk(double x1, double y1, RiskNode riskNode[], int riskNum);

const double MAX_RISK = 9999999999;


int main(){
    
	RiskNode* riskNode;
	Route *route;
	

    //input
    int n=0, m=0, routeNum=0;
    cin >> n >> m >> routeNum;
   
    riskNode = new RiskNode[m];
	route = new Route[routeNum];

    inputNodeAndRoute(riskNode, m, route, routeNum);
    calculateRouteRisk(riskNode, m, route, routeNum);
    printResult(route, routeNum);

    delete[] riskNode;
    delete[] route;
 
} 
 
void inputNodeAndRoute(RiskNode riskNode[], int m, Route route[], int routeNum){
	//crate node array & route array
	
	//x
    for(int i=0; i<m; i++){
        cin >> riskNode[i].x;
    }
    //y
    for(int i=0; i<m; i++){
        cin >> riskNode[i].y;
    }
    //R
    for(int i=0; i<m; i++){
        cin >> riskNode[i].r;
    }
    //P
    for(int i=0; i<m; i++){
        cin >> riskNode[i].p;
    }
     
    //input route
    for(int i=0; i<routeNum; i++){
        cin >> route[i].x1 >> route[i].y1 >> route[i].x2 >> route[i].y2;
    } 
}

void calculateRouteRisk(RiskNode riskNode[], int m, Route route[], int routeNum){

	for(int k=0; k<routeNum; k++){	

    	//origin & destination
    	double originX = route[k].x1, originY = route[k].y1;
    	double destX = route[k].x2, destY = route[k].y2;
    	
		//unit vector
    	double vectorLength = pow(pow(route[k].x2-route[k].x1,2) + pow(route[k].y2-route[k].y1,2), 0.5);
    	double unitVecX = (route[k].x2-route[k].x1)/vectorLength;
    	double unitVecY = (route[k].y2-route[k].y1)/vectorLength;
    	
    	//number of internal nodes
    	int interNodeNum = ceil(vectorLength)-1;
    	
		//cout << "vectorLength: " << vectorLength << endl;
    	//cout << "interNodeNum: " << interNodeNum << endl;
    	//cout << "unitVecX: " << unitVecX << endl;
    	//cout << "unitVecY: " << unitVecY << endl;
	
		//risk
		double routeRiskSum = 0;
		for(int i=1; i<=interNodeNum; i++){
			double routeX = originX + i*unitVecX;
			double routeY = originY + i*unitVecY;
			routeRiskSum += allRisk(routeX, routeY, riskNode, m);
		}
		
		//save risk
		route[k].risk = routeRiskSum;
		//cout << "route: " << k+1 << " risk: " << routeRiskSum << endl;
	}

}

void printResult(Route route[], int routeNum){

	//output
	int minRiskRouteId = 0,  maxRiskRouteId=0;
	double minRisk = MAX_RISK, maxRisk = -1;
	
	//find min
	for(int i=0; i<routeNum; i++){
		if(route[i].risk<minRisk){
			minRisk = route[i].risk;
			minRiskRouteId = i+1;
		}
	}
	//find max
	for(int i=0; i<routeNum; i++){
		if(route[i].risk>maxRisk){
			maxRisk = route[i].risk;
			maxRiskRouteId = i+1;
		}
	}
	//cout minId, maxId
	cout << minRiskRouteId << " " << maxRiskRouteId << endl;
}

double distance(double x1, double y1, int x2, int y2){
    return pow(pow((x1-x2),2) + pow((y1-y2),2), 0.5);
}
 
double risk(double x1, double y1, RiskNode &riskNode){	
	
    int x2 = riskNode.x;
    int y2 = riskNode.y;
    double r = riskNode.r;
    double p = riskNode.p; 
    double d = distance(x1,y1,x2,y2);
    return p*(max((r-d)/r,0.0));
}

double allRisk(double x1, double y1, RiskNode riskNode[], int riskNum){	
	
	//risk for risk node k
	double dotRiskSum = 0;
	for(int k=0; k<riskNum; k++){
        dotRiskSum += risk(x1, y1, riskNode[k]);   
    }
    //cout << "dot risk: " << x1 << " " << y1 << " " << dotRiskSum << endl;
    return dotRiskSum;
}


