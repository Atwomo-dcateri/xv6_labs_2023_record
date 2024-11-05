#include<stdio.h>//无向带权图
#include<stdlib.h>
#include<string.h>
#define Infinity 2000//表示无穷大
#define MaxVertexNum 20
#define MAX 40
#define key 11//key为顶点个数
#include <unistd.h>
typedef struct arcell//边的权值信息
{
    int adj;//权值
}arcell, adjmatrix[MaxVertexNum][MaxVertexNum];//图的邻接矩阵类型
typedef struct vexsinfo//顶点信息
{
    int position;//景点的编号
    char name[32];//景点的名称
    char introduction[256];//景点的介绍
    char super_introduction[512];//景点的详细介绍
}vexsinfo;
typedef struct mgraph//图结构信息
{
    vexsinfo vexs[MaxVertexNum];//顶点向量（数组）
    adjmatrix arcs;//邻接矩阵
    int vexnum, arcnum;//顶点数和边数
}mgraph;
//全局变量
mgraph campus; //图变量
int d[30];
int visited[30];
int shortest[MaxVertexNum][MaxVertexNum];//定义全局变量存储最小路径
int pathh[MaxVertexNum][MaxVertexNum];//定义存储路径
mgraph initgraph()
{
    int i = 0, j = 0;
    mgraph c;
    c.vexnum = 11;//顶点个数
    c.arcnum = 20;//边的个数
    for (i = 1; i <= key; i++)//依次设置顶点编号
        c.vexs[i].position = i;
    //依次输入顶点信息
    strcpy(c.vexs[1].name, "冰雪家族的狂欢派对"); strcpy(c.vexs[1].super_introduction, "\n由18根高低不等的晶莹冰柱群建成的欢乐主塔，象征冰雪王国从第1届到第18届的辉煌。\n");
    strcpy(c.vexs[1].introduction, "由18根高低不等的晶莹冰柱群建成的欢乐主塔，象征冰雪王国从第1届到第18届的辉煌。");
    strcpy(c.vexs[2].name, "冰雪家族的月光圣殿"); strcpy(c.vexs[2].super_introduction, "\n你将登上广寒宫与嫦娥仙子共舞。\n");
    strcpy(c.vexs[2].introduction, "你将登上广寒宫与嫦娥仙子共舞。");
    strcpy(c.vexs[3].name, "冰雪家族的梦幻餐厅"); strcpy(c.vexs[3].super_introduction, "\n在这里，你将变成小矮人，与鸡蛋哥和草莓姐合影留念\n");
    strcpy(c.vexs[3].introduction, "在这里，你将变成小矮人，与鸡蛋哥和草莓姐合影留念");
    strcpy(c.vexs[4].name, "冰雪家族的宠物乐园"); strcpy(c.vexs[4].super_introduction, "\n在这里，你将遇到十二生肖的动物朋友，共同演奏冰雪欢乐颂歌。\n");
    strcpy(c.vexs[4].introduction, "室内运动场、游泳馆");
    strcpy(c.vexs[5].name, "冰雪家族的爆炸实验室"); strcpy(c.vexs[5].super_introduction, "\n在这里，你将穿梭时空，来到蒸汽时代，触摸未来世界\n");
    strcpy(c.vexs[5].introduction, "在这里，你将穿梭时空，来到蒸汽时代，触摸未来世界");
    strcpy(c.vexs[6].name, "冰雪家族的游乐场"); strcpy(c.vexs[6].super_introduction, "\n在这里，你将驾驭欢乐的龙舟，与小伙伴们畅游欢乐世界\n");
    strcpy(c.vexs[6].introduction, "在这里，你将驾驭欢乐的龙舟，与小伙伴们畅游欢乐世界");
    strcpy(c.vexs[7].name, "南大门暖心小屋"); strcpy(c.vexs[7].super_introduction, "\n南大门：我们冰雪大世界的南门，刷门票进入\n");
    strcpy(c.vexs[7].introduction, "大世界大门、进出口");
    strcpy(c.vexs[8].name, "新南小门"); strcpy(c.vexs[8].super_introduction, "\n小南门，为方便景区人员的出行和管理。\n");
    strcpy(c.vexs[8].introduction, "距离高铁站比较近，方便出行");
    strcpy(c.vexs[9].name, "欢乐儿童城"); strcpy(c.vexs[9].super_introduction, "\n全球首创室内冰雪主题乐园，世界级并雕刻大师倾情创作。多种颜色采冰打造的主题乐园带领小朋友们穿越奇妙夜、漫步欢乐节、探秘冒险岛、狂欢冰世界\n");
    strcpy(c.vexs[9].introduction, "全球首创室内冰雪主题乐园，世界级并雕刻大师倾情创作。多种颜色采冰打造的主题乐园带领小朋友们穿越奇妙夜、漫步欢乐节、探秘冒险岛、狂欢冰世界");
    strcpy(c.vexs[10].name, "中华锦绣"); strcpy(c.vexs[10].super_introduction, "\n该景区以原有的土山为基础，以闻名世界的皇家园林景观——北京颐和园为蓝本，建立冰雪园林奇葩。\n");
    strcpy(c.vexs[10].introduction, "在该区还设立每年作为冰雪大世界的传统景观大佛，第五届纪念物长鼓等，形成了北高南低的布局。");
    strcpy(c.vexs[11].name, "东门"); strcpy(c.vexs[11].super_introduction, "\n东门\n");
    strcpy(c.vexs[11].introduction, "景区主要大门");
    for (i = 1; i <= key; i++)
        for (j = 1; j <= key; j++)
            c.arcs[i][j].adj = Infinity;//先初始化图的邻接矩阵
    c.arcs[1][2].adj = 60; c.arcs[1][5].adj = 70; c.arcs[2][3].adj = 40; c.arcs[2][4].adj = 40; c.arcs[3][4].adj = 15;
    c.arcs[3][9].adj = 10; c.arcs[3][10].adj = 30; c.arcs[4][5].adj = 30; c.arcs[4][9].adj = 20; c.arcs[5][6].adj = 60;
    c.arcs[5][7].adj = 60; c.arcs[5][8].adj = 30; c.arcs[5][9].adj = 40; c.arcs[6][7].adj = 10; c.arcs[7][8].adj = 30;
    c.arcs[8][9].adj = 50; c.arcs[8][11].adj = 200; c.arcs[9][10].adj = 35; c.arcs[9][11].adj = 10; c.arcs[10][11].adj = 20;
    for (i = 1; i <= key; i++)//邻接矩阵是对称矩阵，对称赋值（无向图需要对称赋值）
        for (j = 1; j <= key; j++)
            c.arcs[j][i].adj = c.arcs[i][j].adj;
    return c;
}//initgraph
//2.查找景点在图中的序号
int locatevex(mgraph c, int v)//locatevex
{
    int i;
    for (i = 1; i <= c.vexnum; i++)
        if (v == c.vexs[i].position)  return i;//找到，返回顶点序号i
    return -1;//没有找到这个顶点
}
//3.查找并输出序号为m,n景点间的长度不超过8个景点的路径
void path(mgraph c, int m, int n, int k)
{
    int s, t = k + 1, length = 0;//t用于存放路径上下一个顶点对应的d[]数组元素的下标
    if (d[k] == n && k < 8)//若d[k]是终点n且景点个数<=8,则输出该路径
    {
        for (s = 0; s < k; s++)//计算路径长度
        {
            length = length + c.arcs[d[s]][d[s + 1]].adj;
        }
        if (length <= 100)//打印路径长度小于定长的路径
        {
            for (s = 0; s < k; s++)//输出该路径。s=0时为起点m
            {
                printf("%d%s--->", d[s], c.vexs[d[s]].name);
            }
            printf("%d%s  ", d[s], c.vexs[d[s]].name);//输出最后一个景点名（即顶点n的名字，此时s==k）
            printf("总路线长为%d米\n\n", length);
        }
    }
    else
    {
        s = 1;
        while (s <= c.vexnum)//从第m个顶点，试探所有顶点是否有路径
        {
            if ((c.arcs[d[k]][s].adj < Infinity) && (visited[s] == 0))//顶点m到顶点s有边(权值不为无穷大)，且未被访问
            {
                visited[s] = 1;
                d[k + 1] = s;//存储顶点编号
                path(c, m, n, t);
                visited[s] = 0;//将找到的路径上顶点的访问标志重新设置为0，以用于试探新的路径
            }
            s++;//试探从下一个顶点s开始是否有到终点的路径
        }
    }
}
//4.查找两景点间的景点的所有路径
int allpath(mgraph c)
{
    int k, i, j, m, n;
    printf("\n\n请输入您想要查询的两个景点的编号：\n\n");
    scanf("%d %d", &i, &j); printf("\n\n");
    m = locatevex(c, i);//locatevex 确定该顶点是否存在。若存在，返回该顶点编号。
    n = locatevex(c, j);
    d[0] = m;//存储路径起点m（int d[]数组是全局变量）
    for (k = 0; k < key; k++)//全部顶点访问标志初值设为0
        visited[k] = 0;
    visited[m] = 1;//第m个顶点访问标志设置为1
    path(c, m, n, 0);//调用程序。k=1，对应起点d[1]==m。k为d[]数组下标
    return 1;
}
//5.用迪杰斯特拉算法，求出一个景点到其他景点间的最短路径，
void shortestpath_dij(mgraph c)
{
    int v0, v, w, k = 1, min, t, p;
    int final[MaxVertexNum];//final[w]=1表示已经求得顶点V0到Vw的最短路径
    int Patharc[MaxVertexNum];//用于存储最短路径下标的数组
    int ShortPathtable[MaxVertexNum];//用于存储到各点最短路径的权值和
    printf("\n请输入一个起始景点的编号：");
    scanf("%d", &v0); printf("\n\n");
    while (v0<0 || v0>key)
    {
        printf("\n您输入的景点编号不存在\n");
        printf("请重新输入：");
        scanf("%d", &v0);
    }
    //初始化数据
    for (v = 1; v <= c.vexnum; v++)//数组0还是空出来
    {
        final[v] = 0;//全部顶点初始化为未找到最短路径
        ShortPathtable[v] = c.arcs[v0][v].adj;//将与v0点有连线的顶点加上权值
        Patharc[v] = 0;//初始化路径数组p为0
    }
    ShortPathtable[v0] = 0; // V0至v0的路径为0
    final[v0] = 1;//V0至v0不需要路径
    //开始主循环，每次求得V0到某个v顶点的 最短路径
    for (v = 1; v <= c.vexnum; v++)
    {
        min = Infinity;
        for (w = 1; w <= c.vexnum; w++)//找出最近的顶点和权值
        {
            if (!final[w] && ShortPathtable[w] < min)//有边
            {
                k = w;
                min = ShortPathtable[w];
            }
        }
        final[k] = 1;//将目前找到的最近的顶点置1
        //修正当前最短路径及距离
        for (w = 1; w <= c.vexnum; w++)
        {  //如果经过v顶点的路径比现在这条路径的长度短的话，更新
            if (!final[w] && (min + c.arcs[k][w].adj < ShortPathtable[w]))
            {
                ShortPathtable[w] = min + c.arcs[k][w].adj;//修改当前路径长度
                Patharc[w] = k; //存放前驱结点（像糖葫芦）
            }
        }
    }


    printf("打印P数组:");
    for (t = 1; t <= c.vexnum; t++)
    {
        printf("%d ", Patharc[t]);
    }
    printf("\n\n");
    //打印s数组
    printf("打印S数组:");
    for (t = 1; t <= c.vexnum; t++)
    {
        printf("%d ", ShortPathtable[t]);
    }
    printf("\n\n");

    //打印最短路径
    for (t = 1; t <= c.vexnum; t++)
    {
        p = t;
        if (t != v0)//反向输出
        {
            printf("%d%s", t, c.vexs[t].name);
            for (w = 1; w <= c.vexnum; w++)
            {
                if (Patharc[p] != 0)
                {
                    printf("<--%d%s",Patharc[p],c.vexs[Patharc[p] ].name); 
                    p = Patharc[p];
                }
            }
            printf("<--%d%s", v0, c.vexs[v0].name);
            printf("\n总路线长为%d米\n\n", ShortPathtable[t]);
        }
    }
}
//菜单
void menu()
{
    printf(" ┌──────────────────────────────────────────────────────┐\n");
    printf(" │ ╭ ═══════════════════════════════════════════════ ╮  │\n");
    printf(" │ ││    欢 迎 使 用 哈 尔 滨 导 游 系 统       ││  │\n");
    printf(" │ ╰ ═══════════════════════════════════════════════ ╯  │\n");
    printf(" │                      欢迎来到                        │\n");
    printf(" │                  双李一林一明一阳导游系统            │\n");
    printf(" │                     菜 单 选 择                      │\n");
    printf(" │  *************************************************** │\n");
    printf(" │  *  1.菜单                **   2.查看游览路线（迪）* │\n");// 景点介绍
    printf(" │  *************************************************** │\n");
    printf(" │  *  3.查询景点间最短路径  **   4.查询景点间所有路径* │\n");
    printf(" │  *************************************************** │\n");
    printf(" │  *  5.景点介绍            **   6.景点信息查询      * │\n");//
    printf(" │  *************************************************** │\n");
    printf(" │  *  7.景点地图            **   8.更改图信息        * │\n");
    printf(" │  *************************************************** │\n");
    printf(" │  *  0.退出                **   双李意林*^_^*       * │\n");
    printf(" │  *************************************************** │\n");
    printf(" └──────────────────────────────────────────────────────┘\n");
}
//以下是修改图的相关信息。包括建图、更新信息、删除、增加结点和边
//6.重新构造图
int creatgraph(mgraph* c)
{
    int i, j, m, n, v0, v1, distance;
    printf("请输入图的顶点数和边数: \n");
    scanf("%d %d", &c->vexnum, &c->arcnum);
    printf("下面请输入景点的信息： \n");
    for (i = 1; i <= c->vexnum; i++)
    {
        printf("请输入景点的编号：");
        scanf("%d", &c->vexs[i].position);
        printf("\n请输入景点的名称：");
        scanf("%s", &c->vexs[i].name);
        printf("\n请输入景点的简介：");
        scanf("%s", &c->vexs[i].introduction);
        printf("\n请输入修改后景点的详细介绍:");
        scanf("%s", &c->vexs[i].super_introduction);
    }
    for (i = 1; i <= c->vexnum; i++)
        for (j = 1; j <= c->vexnum; j++)//权值全部初始化为无穷
            c->arcs[i][j].adj = Infinity;
    printf("下面请输入图的边的信息：\n");
    for (i = 1; i <= c->vexnum; i++)
    {
        printf("\n第%d条边的起点 终点 长度为：", i);
        scanf("%d %d %d", &v0, &v1, &distance);
        m = locatevex(campus, v0);//判断一下点是否存在，存在就返回位置
        n = locatevex(campus, v1);
        if (m > 0 && n > 0)
        {
            c->arcs[m][n].adj = distance;
            c->arcs[n][m].adj = c->arcs[m][n].adj;
        }
    }
    return 1;
}
//7.更新图的部分信息。返回值：1***比如某个信息输错了，需要改
int newgraph(mgraph* c)
{
    int changenum;
    int i, m, n, t, distance, v0, v1;
    printf("\n下面请输入您要修改的景点的个数：\n");
    scanf("%d", &changenum);
    while (changenum<0 || changenum>key)
    {
        printf("\n输入错误！请重新输入");
        scanf("%d", &changenum);
    }
    for (i = 0; i < changenum; i++)
    {
        printf("\n请输入景点的编号：");
        scanf("%d", &m);
        t = locatevex(campus, m);
        printf("\n请输入修改后景点的名称:");
        scanf("%s", &c->vexs[t].name);
        printf("\n请输入修改后景点的简介:");
        scanf("%s", &c->vexs[t].introduction);
        printf("\n请输入修改后景点的详细介绍:");
        scanf("%s", &c->vexs[t].super_introduction);
    }
    printf("\n下面请输入您要更新的边数");
    scanf("%d", &changenum);
    while (changenum<0 || changenum>key)
    {
        printf("\n输入错误！请重新输入");
        scanf("%d", &changenum);
    }
    if (changenum != 0)
        printf("\n下面请输入更新边的信息：\n");
    for (i = 1; i <= changenum; i++)
    {
        printf("\n修改的第%d条边的起点 终点 长度为：", i);
        scanf("%d %d %d", &v0, &v1, &distance);
        m = locatevex(campus, v0);
        n = locatevex(campus, v1);
        if (m >= 0 && n >= 0)
        {
            c->arcs[m][n].adj = distance;
            c->arcs[n][m].adj = c->arcs[m][n].adj;
        }
    }
    return 1;
}
//8.增加一条边。返回值：1***
int enarc(mgraph* c)
{
    int m, n, distance;
    printf("\n请输入边的起点和终点编号，权值：");
    scanf("%d %d %d", &m, &n, &distance);
    while (m<0 || m>c->vexnum || n<0 || n>c->vexnum)
    {
        printf("输入错误，请重新输入：");
        scanf("%d %d", &m, &n);
    }
    if (locatevex(campus, m) < 0)
    {
        printf("此节点%d已删除", m);
        return 1;
    }
    if (locatevex(campus, n) < 0)
    {
        printf("此节点%d已被删除", n);
        return 1;
    }

    c->arcs[m][n].adj = distance;//在邻接矩阵中多加一个值
    c->arcs[n][m].adj = c->arcs[m][n].adj;
    c->arcnum--;//图中边数+1
    return 1;
}
//9.增加一个结点。返回值：1***
int envex(mgraph* c)
{
    int i;
    c->vexnum++;//顶点个数+1
    printf("请输入您要增加结点的信息：");
    printf("\n编号：");
    scanf("%d", &c->vexs[c->vexnum].position);
    printf("名称：");
    scanf("%s", &c->vexs[c->vexnum].name);
    printf("简介：");
    scanf("%s", &c->vexs[c->vexnum].introduction);
    printf("详细介绍：");
    scanf("%s", &c->vexs[c->vexnum].super_introduction);

    for (i = 1; i <= c->vexnum; i++)
    {
        c->arcs[c->vexnum][i].adj = Infinity;
        c->arcs[i][c->vexnum].adj = Infinity;
    }
    return 1;
}
//10.删除图的一个顶点。返回值：1***
int delvex(mgraph* c)
{
    int i = 0, j;
    int m, v;
    if (c->vexnum <= 0)
    {
        printf("图中已无顶点");
        return 1;
    }
    printf("\n下面请输入您要删除的景点编号：");
    scanf("%d", &v);
    while (v<0 || v>key)
    {
        printf("\n输入错误！请重新输入:");
        scanf("%d", &v);
    }
    m = locatevex(campus, v);
    if (m < 0)
    {
        printf("此顶点%d已删除\n", v);
        return 1;
    }
    for (i = m; i <= c->vexnum - 1; i++)
        for (j = 1; j <= c->vexnum; j++)//将二维数组中的第m+1行依次向前移动一行（删除第m行）
            c->arcs[i][j] = c->arcs[i + 1][j];
    for (i = m; i <= c->vexnum - 1; i++)
        for (j = 1; j <= c->vexnum; j++)//将二维数组中的第m+1列依次向前移动一列（删除第m列）
            c->arcs[j][i] = c->arcs[j][i + 1];
    c->vexs[v].position = -1;//表示此点已删除，后期打印也不会显示该点
    c->vexnum--;//顶点个数-1
    return 1;
}
//11.删除图的一条边。返回值：1***
int delarc(mgraph* c)
{
    int m, n, v0, v1;
    if (c->vexnum <= 0)
    {
        printf("图中已无边，无法删除。");
        return 1;
    }
    printf("\n下面请输入您要删除的边的起点和终点编号：");
    scanf("%d %d", &v0, &v1);
    m = locatevex(campus, v0);
    if (m < 0)
    {
        printf("此%d顶点已删除", v0);
        return 1;
    }
    n = locatevex(campus, v1);
    if (n < 0)
    {
        printf("此%d顶点已删除", v1);
        return 1;
    }
    c->arcs[m][n].adj = Infinity;//将删掉的边的权值改为无穷
    c->arcs[n][m].adj = Infinity;
    c->arcnum--;//图中边数减1
    return 1;
}
//12.输出图的邻接矩阵的值***
void printmatrix(mgraph c)
{
    int i, j, k = 0;
    for (i = 1; i <= key; i++)
    {
        if (c.vexs[i].position != -1)
            printf("%6d", i);//横着的标号1到11
    }
    printf("\n");
    for (i = 1; i <= c.vexnum; i++)
    {
        for (j = 1; j <= c.vexnum; j++)
        {
            if (c.arcs[i][j].adj == Infinity)
                printf(" *#@* ");
            else
                printf("%6d", c.arcs[i][j].adj);
            k++;
            if (k % c.vexnum == 0) printf("\n");
        }
    }
}
//13.图的操作主调函数。返回值：1***
int changegraph(mgraph* c)
{
    int yourchoice;
    printf("(1)重新建图     (2)删除结点  (3)删除边\n");
    printf("(4)增加结点     (5)增加边    (6)更新信息\n");
    printf("(7)打印邻接矩阵 (8)返回上一级\n");
    do
    {
        printf("请输入您的选择：");
        scanf("%d", &yourchoice);
        switch (yourchoice)
        {
        case 1:creatgraph(c); break;
        case 2:delvex(c); break;
        case 3:delarc(c); break;
        case 4:envex(c); break;
        case 5:enarc(c); break;
        case 6:newgraph(c); break;
        case 7:printmatrix(campus); break;
        case 8:system("cls"); menu(); return 1;//break;
        default:printf("未找到该功能，请输入有效选项！\n"); break;
        }
    } while (yourchoice);
}
int user_log()
{
    int i;
    int a[6] = { 1,2,3,4,5,6 }, b[6];
    //for(i=0;i<6;i++)
    //printf("%d ",a[i]);
    printf("\n请输入6位密码(每输入一位密码间隔一个空格)：\n");
    for (i = 0; i < 6; i++)
        scanf("%d", &b[i]);
    for (i = 0; i < 6; i++)
    {
        if (a[i] != b[i])
        {
            printf("密码错误!自动返回上一级\n"); menu(); return 0;
        }
    }
    printf("密码正确，登陆成功！\n\n");
    changegraph(&campus);
}
//14.查询两景点间的最短路径（floyd算法）
void floyd(mgraph c)//一种暴力破解获取最短路径的算法
{
    int i, j, k;
    for (i = 1; i <= key; i++)//将图的邻接矩阵赋值给 shortest二维数组，将矩阵pathh全部初始化为-1
    {
        for (j = 1; j <= key; j++)
        {
            shortest[i][j] = c.arcs[i][j].adj;
            pathh[i][j] = j;
        }
    }
    int i1, j1, k1 = 0;
    for (i1 = 1; i1 <= key; i1++)
        printf("%6d", i1);//横着的标号1到11
    printf("\n");
    for (i1 = 1; i1 <= key; i1++)
    {
        printf("%d", i1);//竖着的标号1到11
        for (j1 = 1; j1 <= key; j1++)
        {
            printf("%6d", pathh[i1][j1]);
            k1++;
            if (k1 % key == 0) printf("\n");
        }
    }
    printf("\n\n\n");

    for (k = 1; k <= key; k++)//核心操作，完成了以k为中间点对所有的顶点对（i,j）进行检测和修改
    {
        for (i = 1; i <= key; i++)
        {
            for (j = 1; j <= key; j++)
            {
                if (shortest[i][j] > shortest[i][k] + shortest[k][j])
                {
                    shortest[i][j] = shortest[i][k] + shortest[k][j];
                    pathh[i][j] = pathh[i][k];//记录一下所走的路 //P数组用来存放前驱顶点
                }
            }
        }
    }
}
void printf_Pshuzu()
{
    int i, j, k = 0;
    for (i = 1; i <= key; i++)
        printf("%6d", i);//横着的标号0到11
    printf("\n");
    for (i = 1; i <= key; i++)
    {
        printf("%d", i);//竖着的标号0到11
        for (j = 1; j <= key; j++)
        {
            printf("%6d", pathh[i][j]);
            k++;
            if (k % key == 0) printf("\n");
        }
    }
    printf("\n\n\n");
}
//打印出最短路径
void display(mgraph c, int i, int j)
{
    int a, b;
    a = i; b = j;
    printf("您要查询的两景点间最短路径：\n\n");
    printf("%d%s", a, c.vexs[a].name);
    while (pathh[i][j] != b)
    {
        printf("-->%d%s", pathh[i][j], c.vexs[pathh[i][j]].name);
        i = pathh[i][j];
    }
    printf("-->%d%s\n\n", b, c.vexs[b].name);
    printf("%s-->%s的最短路径是：%d 米。\n\n", c.vexs[a].name, c.vexs[b].name, shortest[a][b]);
}
//任意两点间最短距离（弗洛伊德算法）
int shortdistance(mgraph c)
{
    int i, j;
    printf("请输入要查询的两个景点的数字编号（1->11）中间用空格间隔开。\n");
    scanf("%d %d", &i, &j);
    if (i > key || i<0 || j>key || j < 0)
    {
        printf("输入信息错误！\n\n");
        printf("请输入要查询的两个景点的数字编号（1->11）中间用空格间隔开。\n");
        scanf("%d %d", &i, &j);
    }
    else
    {
        floyd(c); printf_Pshuzu();
        display(c, i, j);
    }
    return 1;
}
//15.查询景点的信息
void seeabout(mgraph c)
{
    int k;
    printf("\n请输入要查询的景点编号：");
    scanf("%d", &k);
    while (k <= 0 || k > key)
    {
        printf("\n您所输入的景点编号不存在！");
        printf("\n请重新输入景点编号：");
        scanf("%d", &k);
    }
    printf("\n\n编号：%-4d\n", c.vexs[k].position);
    printf("\n景点名称：%-10s\n", c.vexs[k].name);
    printf("\n详细介绍：%-80s\n\n", c.vexs[k].super_introduction);
}
//16.显示所有景点信息
void browsecompus(mgraph c)
{
    int i;
    printf(" \n\n编号        景点名称                   简介\n");
    printf("____________________________________________________________________________________________\n");
    for (i = 1; i <= key; i++)
    {
        if (c.vexs[i].position != -1)
            printf("%-10d%-25s%-80s\n", c.vexs[i].position, c.vexs[i].name, c.vexs[i].introduction);
    }
    printf("____________________________________________________________________________________________\n");
}
//17.地图
void school_map()//│││││   ┌┌┌   ╰╰╰╭═  ╭═  ═╰═ ╭╭=  =╮  =╯  =■□■□  ══=
{
    printf(" ---------------------------------------哈尔滨双李意林景点地图--------------------------------------------\n");
    printf(" ---------------------------------------------------------------------------------------------------------\n");
    printf(" ___________                                                                                            ==\n");
    printf("││冰雪家 ││*                        梦幻                餐厅                            中华锦绣        == \n");
    printf("││_______││*                       * *  * * * * *  *  *  *   **   *  *  *  *  *  *  *  *  * *  * *  *   == \n");
    printf(" __________ *                     *        ##                *                       *               *  == \n");
    printf(" │族的狂 │ *-->***鼎山***假山*                            *   ___________          *                  * ==\n");
    printf(" │_______│ *                              ##     宠物乐园     *  │        │          *                 *东\n");
    printf(" __________ *                              ##               *   │ 欢乐儿童城  │        * * * * * * ** * * *--> \n");
    printf(" │欢派对 │ *                              ##              *     │________│          *    _________     *门 \n");
    printf(" │_______│  *                     假山        ##        *                        *    │ 月光  │      * == \n");
    printf(" ##           *                              ##      *                          *    │__圣殿__│      * ==\n");
    printf(" ##            ******        **********  爆炸实验室    ##  *                          *              * ==\n");
    printf(" ##              *             *          * * * * * * * * * * * * * * * * * ** * * * * * * * * * *  *  ==\n");
    printf(" ##  停车场      *             *           ###           *                          _________          ==\n");
    printf(" ##              *             *           ###          *                          │    │              ==\n");
    printf(" ##   游乐       *             *           ###           *                          │_  _│             ==\n");
    printf(" ##     馆      *             *            ### 职工餐厅  *                                               ==\n");
    printf(" ##  超市        *             *           ###           *            ==================================== \n");
    printf(" ##  一餐        *             *           ###        *              ==  \n");
    printf(" ##              *         *               ###           *            ==    \n");
    printf(" ================ 双李意林学院 =======================小南门============  \n");
    printf(" ================     南门     =======================      ============\n");
    printf("\n                                                      西<---|--->东  \n");
}
//18.主要工作函数。操作区用户界面
void mainwork()
{
     menu();
    int yourchoice;
    campus = initgraph();
    do
    {
        printf("请输入您的选择：");
        scanf("%d", &yourchoice);
        switch (yourchoice)
        {
        case 1:system("cls"); menu(); break;
        case 2:system("cls"); shortestpath_dij(campus); break;
        case 3:system("cls"); shortdistance(campus); break;
        case 4:system("cls"); allpath(campus); break;
        case 5:system("cls"); browsecompus(campus); break;
        case 6:system("cls"); seeabout(campus); break;
        case 7:system("cls"); school_map(); break;
        case 8:system("cls"); user_log(); break;
        case 0:system("cls"); printf("谢谢使用\n"); break;
        default:printf("未找到该功能，请输入有效选项！\n"); break;
        }
    } while (yourchoice);
}
int main()
{
    system("color 5E");//背景颜色
    system("mode con: cols=200 lines=140");//程序页面长宽
    
	 	//sleep(3);
    //system("SchoolGraph.png");//调用景区地图 （就是一个图片）
     mainwork();
   
    return 0;
}

