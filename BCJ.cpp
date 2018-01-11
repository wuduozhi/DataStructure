#include<stdio.h>
/*
并查集
*/

int f[100]={0},n,m,k,sum=0;

void init(){
    for(int i=0;i<=n;i++){
        f[i] = i;
    }
}

int getf(int v){
    if(f[v]==v)
        return v;
    else{
        f[v] = getf(f[v]);
        return f[v];
    }
}

int merge(int v,int u){
    int t1 = getf(v);
    int t2 = getf(u);
    if(t1!=t2){
        f[t2] = t1;
    }
}

int main(){
    scanf("%d %d",&n,&m);
    init();
    int x,y;
    for(int i=0;i<m;i++){
        scanf("%d %d",&x,&y);
        merge(x,y);
    }

    for(int i=0;i<=n;i++){
        printf("%d ",f[i]);
        if(f[i] == i)
            sum++;
    }

    printf("\nSum:%d ",sum);

    while(1){}
    return 0;
}