// 代码来自 http://www.cnblogs.com/gfc-g/p/3860953.html
// 自己写的一直WA， 可能与visit数组未考虑kss有关

#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;

const int maxn = 30 ;

struct node {
    int x,y;
    int step;
    int ks;
    void init (int nx,int ny,int nstep,int nks){
        x=nx;y=ny;step=nstep;ks=nks;
    }
};

int n,m,k;
int map[maxn][maxn],visit[maxn][maxn][maxn];
int dir[4][2]={1,0,-1,0,0,1,0,-1};

int bfs (){
    queue<node> q;
    while (!q.empty ())
        q.pop ();
    node a,b;
    a.init (1,1,0,0);
    q.push (a);
    while (!q.empty ()){
        a=q.front ();
        q.pop ();

        int xx,yy,sstep,kss;
        for (int i=0;i<4;i++){
            xx=a.x;yy=a.y;sstep=a.step;kss=a.ks;
            xx+=dir[i][0];
            yy+=dir[i][1];
            sstep+=1;
            if (xx<1||xx>n||yy<1||yy>m)
                continue ;
            if (map[xx][yy])
                kss++;
            else kss=0;
            if (kss>k)
                continue ;
            if (visit[kss][xx][yy])
                continue ;
            if (xx==n&&yy==m)
                return sstep ;
            b.init (xx,yy,sstep,kss);
            q.push (b);
            visit[kss][xx][yy]=1;
        }
    }
    return -1;
}

int main (){
    int t;
    cin>>t;
    while (t--){
        cin>>n>>m>>k;
        if (n==m&&n==1){
            cout<<0<<"error"<<endl;
            continue ;
        }
        memset (visit,0,sizeof visit);
        for (int i=1;i<=n;i++)
            for (int j=1;j<=m;j++)
                cin>>map[i][j];
        int ans=bfs ();
        cout<<ans<<endl;
    }
    return 0;
}