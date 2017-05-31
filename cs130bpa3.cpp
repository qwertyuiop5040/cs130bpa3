/*
	PA 3, CS130b
	Hanqing Wang, 9594458
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <string>
#include <sstream>
#include <numeric>
#include <map>
#include <cmath>
#include <iomanip>
using namespace std;
#define forn(i,n) for(int i=0;i<n;i++)
#define forn1(i,n) for(int i=1;i<=n;i++)
#define mp make_pair
#define pb push_back
#define fi first
#define se second
int m,n;
vector<double>pts[3];//x,y,z
double dist(double x1,double y1,double z1,double x2,double y2,double z2){
	double dx=(x1-x2);
	double dy=(y1-y2);
	double dz=(z1-z2);
	return pow(dx*dx+dy*dy+dz*dz,0.5);
}
double dist(int idx,int idx2){return dist(pts[0][idx],pts[1][idx],pts[2][idx],pts[0][idx2],pts[1][idx2],pts[2][idx2]);}
double area(int idx,int idx2,int idx3){
	double a=dist(idx,idx2);
	double b=dist(idx2,idx3);
	double c=dist(idx,idx3);
	double s=(a+b+c)/2;
	return pow(s*(s-a)*(s-b)*(s-c),0.5);
}
int main(){
 	cin>>n>>m;
 	cout<<setprecision(16);
 	forn(i,n+m){
 		forn(j,3){
 			double a=0;
 			cin>>a;
 			pts[j].push_back(a);
 		}
 	}
 	pair<double,int>**dp=new pair<double,int>*[n+3];//double=minimum area so far, int= direction optimal solution came from, used for backtracking later
 	forn(i,n+3)dp[i]=new pair<double,int>[m+3];
 	double best=-1;
 	vector<int>bestIdx[3];
 	forn(i,n){//i=offset: we assume i and n (zero based array) are connected, because the optimal solution has n connected to some element in 0...n, one of these solutions must be right.
 		forn(j,n+3)
 			forn(k,m+3)
 				dp[j][k]=mp(-1,-2);//reset everything essentially NULL
 		dp[1][1]=mp(0,-1);//first two points have an area of zero
 		for(int j=2;j<=n+m+2;j++){
 			for(int x=j-1;x>=1;x--){
 				int y=j-x;
 				if(x>n+1||y>m+1)continue;
 				double prevBest=dp[x][y].fi;
 				if(prevBest==-1)continue;
 				int xIdx=(i+x-1)%n;
 				int yIdx=n+(y-1)%m;
 				int right=(i+x)%n;//we can either increase x by 1, or y by 1. We also make sure it loops properly with the mod function.
 				int down=n+(y)%m;
 				double pr=prevBest+area(xIdx,yIdx,right);
 				double pd=prevBest+area(xIdx,yIdx,down);
 				if(dp[x+1][y].fi==-1||pr<dp[x+1][y].fi)dp[x+1][y]=mp(pr,0);//if x increases, then the pair's second value=0;
 				if(dp[x][y+1].fi==-1||pd<dp[x][y+1].fi)dp[x][y+1]=mp(pd,1);//if y increases, then the pair's second value=1;
 			}
 		}
 		if(best==-1||best>dp[n+1][m+1].fi){//only if we found a smaller optimal area or we haven't set the first optimal area, do we choose it as the actual optimal area
 			bestIdx[0].clear();
 			bestIdx[1].clear();
 			bestIdx[2].clear();
 			best=dp[n+1][m+1].fi;
 			int x=n+1,y=m+1;
 			while(dp[x][y].se!=-1){//backtrack to see which nodes we visited
 				int xIdx=(i+x-1)%n;
 				int yIdx=n+(y-1)%m;
 				int three=-1;
 				if(dp[x][y].se==0){
 					three=(n+i+x-2)%n;
 					x--;
 				}else if(dp[x][y].se==1){
 					three=n+(m+y-2)%m;
 					y--;
 				}
 				bestIdx[0].pb(xIdx);
 				bestIdx[1].pb(yIdx);
 				bestIdx[2].pb(three);
 			}
 		}
 	}
 	for(int i=0;i<bestIdx[0].size();i++)cout<<bestIdx[0][i]+1<<" "<<bestIdx[1][i]+1<<" "<<bestIdx[2][i]+1<<endl;
 	forn(i,n+3)delete []dp[i];
 	delete []dp;
	return 0;
}