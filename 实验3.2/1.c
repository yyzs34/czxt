#include <stdio.h>
#include <stdlib.h>
#define getpch(type)(type*)malloc(sizeof(type))
struct pcb{     /*定义进程控制块*/
    char name [10];
    //进程名
    char state;
    //进程状态："W"表示就绪，"R"表示运行
    int nice;
    //进程优先数
    int ntime;
    //需要运行的时间
    int rtime;
    //已经运行的时间
    struct pcb*link;
}*ready=NULL,*p;

typedef struct pcb PCB;
char sort() /*进程优先数排序函数， 优先数大者优先， 并生成就绪队列*/
{
    PCB *first, *second;
    int insert=0;
    if((ready==NULL)||((p->nice)>(ready->nice))) /*优先数最大者插入队首*/
    {
        p->link=ready;
        ready=p;
    }
    else/*对进程比较优先数，并调整它们的位置*/
    {
        first=ready;
        second=first->link;
        while(second!=NULL)
        {
            if((p->nice)>(second->nice)) /*若插入的进程比当前进程的优先数大*/
            {                           /*插到当前进程的前面*/
                p->link=second;
                first->link=p;
                second=NULL;
                insert=1;
            }       
            else/*若插入的进程优先数最小，则插到队尾*/
            {
            first=first->link;
            second=second->link;
            }
        }
        if(insert==0) first->link=p;
    }
}
char input() /*输入各个进程参数，建立进程控制块并排序生成就绪队列*/
{
    int i, num;
    printf("\n 请输入被调度的进程数目: ");
    scanf("%d", &num);
    for(i=0;i<num;i++)
    {
        printf("\n 进程号 No.%d:",i);
        p=getpch(PCB);
        printf("\n 输入进程名: ");
        scanf("%s",p->name);
        printf(" 输入进程优先数: ");
        scanf("%d", &p->nice);
        printf("输入进程运行时间：");
        scanf("%d",&p->ntime);
        printf ("\n");
        p->rtime=0;
        p->state='W';
        p->link=NULL;
        sort ();    /*调用sort()函数*/
    }
}

int space()         /*链表中节点个数的统计函数*/
{
    int l=0;PCB*pr=ready;
    while(pr!=NULL)
    {
        l++;
        pr=pr->link;
    }
    return(1);
}

char disp(PCB*pr)   /*进程显示函数，用于显示当前进程*/
{
    printf("\n qname \t state \t nice \tndtime\truntime \n");
    printf("%s\t",pr->name);
    printf("%c\t",pr->state);
    printf ("%d\t",pr->nice);
    printf ("%d\t",pr->ntime);
    printf ("%d\t",pr->rtime);
    printf ("\n");
}
char check()    /*进程查看函数*/
{
    PCB*pr;
    printf("\n****当前正在运行的进程是:%s",p->name);/*显示当前运行的进程*/
    disp(p);
    pr=ready;
    if (pr!=NULL)
        printf("\n****当前就绪队列状态为：");    
    else
        printf("\n****当前就绪队列状态为：空\n");   /*显示就绪队列的状态为空*/
    
    while(pr!=NULL)
    {
        disp(pr);
        pr=pr->link;
    }
}

char destroy()  /*建立进程撤销函数（进程运行结束，撤销进程）*/
{
    printf("进程[%s]已完成.\n",p->name);
    free(p);
}

char running()      /*建立进程就绪函数（进程运行时间到，设置进程处于就绪状态）*/
{
    (p->rtime)++;
    if (p->rtime==p->ntime)
    destroy();  /*调用destroy()函数*/
    else
    {
        (p->nice)--;
        p->state='W';
        sort(); /*调用sort()函数*/
    }
}

int main()  /*主函数*/
{   
    int len,h=0;
    char ch;
    input();
    len=space();
    while ((len!=0)&&(ready!=NULL))
    {
        ch=getchar();
        h++;
        printf ("\n The execute number:%d \n",h);
        p=ready;
        ready=p->link;
        p->link=NULL;
        p->state='R';
        check();
        running();
        printf("\n按任意键继续......");
        ch=getchar();
    }
    printf("\n\n所有进程已经运行完成!\n");
    ch=getchar();
    return 0;
}
