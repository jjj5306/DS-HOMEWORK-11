#include <stdio.h>
#include <stdlib.h>

/*최대 vertex의 수는 10개로 설정한다.*/
#define MAX_Vertex 10

/*Graph는 Adjacent List로 구현한다.*/
typedef struct node {
	int visitflag; //간선이 검사되었는지 보는 flag

    struct Vertex* link;
} Vertex;

/* 현재 Vertex가 얼마나 있는지는 currentvertex로 관리한다. */
int currentvertex=0;

/* for stack */
#define MAX_STACK_SIZE		20
Vertex* stack[MAX_STACK_SIZE];
int top = -1;

Vertex* pop();
void push(Vertex* aVertex);


/* for queue */
#define MAX_QUEUE_SIZE		20
Vertex* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Vertex* deQueue();
void enQueue(Vertex* aVertex);


void InitializeGraph(Vertex** v ); //Graph 초기화 함수
void FreeGraph(Vertex* v); //Vertex free 함수


int main()
{
	char command;
	int key;
   /*adjList를 통해서 Graph를 나타 낼 것이다.*/
    Vertex* adjList;
	printf("2020039071 JoJunHwa");
	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                        Graph Searches                          \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph     = z                                       \n");
		printf(" Insert Vertex        = v      Insert Edge                  = d \n");
		printf(" Depth Fisrt Search   = r      Breath First Search          = t \n");
		printf(" Print Graph          = p      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			InitializeGraph(&adjList);
			break;
		case 'v': case 'V':
			
			break;
		case 'e': case 'E':
			
			break;
		case 'd': case 'D':
			
			break;

		case 'b': case 'B':
			
			break;
		case 'p': case 'P':
			
			break;

		case 'q': case 'Q':
			
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

void InitializeGraph(Vertex** v )
{
    /*그래프가 비어있지 않다면 먼저 free를 진행해준다.*/
    if (*v != NULL)
		FreeGraph(*v);
    
    /*MAX_Vertex만큼의 SIZE를 할당해준다.*/
    *v = (Vertex*)malloc(sizeof(Vertex)*MAX_Vertex);
    currentvertex = 0;
    
    /*큐와 스택을 위한 초기화*/
    top = -1;

	front = rear = -1;
}