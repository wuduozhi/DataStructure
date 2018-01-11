#include<stdio.h>


int main(){
    int e[10][10],k,i,j,n,m,t1,t2,t3;
    int inf = 9999999;
    scanf("%d %d",&n,&m);

    //初始化
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            if(i==j)
                e[i][j]=0;
            else{
                e[i][j] = inf;
            }
        }
    }

    for(i=1;i<=m;i++){
        scanf("%d %d %d",&t1,&t2,&t3);
        e[t1][t2] = t3;
    }

    //Floyd-Warshall 算法核心语句
    for(i=1;i<n;i++){
        for(j=1;j<=n;j++){
            for(k=1;k<=n;k++){
                if(e[j][k]>e[j][i]+e[i][k]){
                    e[j][k] = e[j][i]+e[i][k];
                }
            }
        }
    }

    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            printf("%10d",e[i][j]);
        }

        printf("\n");
    }

    while(1){}

    return 0;
}