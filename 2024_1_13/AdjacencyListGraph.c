#include<stdio.h>
#include<stdlib.h>

#define MaxVertexNum 100

const int INF = 0x3f3f3f3f;

typedef char vexType;
typedef int arcType;

typedef struct ArcNode{
    int adjvex;
    struct ArcNode* next;
    arcType weight;
}ArcNode;

typedef struct VNode
{
    vexType data;
    ArcNode* firstNext;
}VNode,AdjList[MaxVertexNum];

typedef struct ALGraph
{
    int vexNum;
    int arcNum;
    AdjList vertice;
}ALGraph;


ALGraph* initGraph(int vexNum){
    ALGraph* G = (ALGraph*)malloc(sizeof(ALGraph));
    G->vexNum = vexNum;
    G->arcNum = 0;
    for(int i = 0; i < vexNum; i++){
        G->vertice[i].data = '0';
        G->vertice[i].firstNext = NULL;
    }
    return G;
}



//用于查找下标
int find(ALGraph* G,vexType x){
    for(int i = 0; i < G->vexNum; i++){
        if(x == G->vertice[i].data)
            return i;
    }
}

void createGraph(ALGraph* G, vexType* vexs, int vexNum, vexType arcList[][2], int arcListLength){
    G->arcNum = arcListLength;
    for(int i = 0; i < G->vexNum; i++){
        G->vertice[i].data = vexs[i];
        printf("%c  \n",vexs[i]);
    }
    for(int i = 0; i < G->arcNum; i++){
        //headInsert
        vexType v = arcList[i][0];
        vexType w = arcList[i][1];

        //
        ArcNode* pArcNode = (ArcNode*)malloc(sizeof(ArcNode));
        pArcNode->adjvex = find(G,w);
        pArcNode->next = G->vertice[find(G,v)].firstNext;
        G->vertice[find(G,v)].firstNext = pArcNode;

        //
        ArcNode* pArcNode_new = (ArcNode*)malloc(sizeof(ArcNode));
        pArcNode_new->adjvex = find(G,v);
        pArcNode_new->next = G->vertice[find(G,w)].firstNext;
        G->vertice[find(G,w)].firstNext = pArcNode_new;
    }
}

void print(ALGraph* G){
    for(int i = 0; i < G->vexNum; i++){
        for(ArcNode* pcurNode = G->vertice[i].firstNext; pcurNode != NULL; pcurNode = pcurNode->next){
            printf("%c --> %c\n",G->vertice[i].data, G->vertice[pcurNode->adjvex].data);
        }
    }
}

int main(){
    ALGraph* G = initGraph(5);
    vexType vList[5] = {'A','B','C','D','E'};
    vexType ArcList[3][2] = {'A','E',
                'B','C',
                'D','E'};
    createGraph(G,vList, 5, ArcList, 3);
    print(G);
    return 0;
}