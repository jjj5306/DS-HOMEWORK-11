#include <stdio.h>
#include <stdlib.h>

/*최대 vertex의 수는 10개로 설정한다.*/
#define MAX_Vertex 10

/*Graph는 Adjacent List로 구현한다.*/
typedef struct Vertex {
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
    Vertex* adjList= NULL;
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
    FreeGraph(adjList);
	return 1;
}

void InitializeGraph(Vertex** v )
{
    /*그래프가 비어있지 않다면 먼저 free를 진행해준다.*/
    if (*v != NULL)
		FreeGraph(*v);
    /*MAX_Vertex만큼의 SIZE를 할당해준다.*/
    *v = (Vertex*)malloc(sizeof(Vertex)*MAX_Vertex);
    
    /*adjList의 link들도 초기화 해준다. */
    for(int i = 0;i<MAX_Vertex;i++)
        (*v)->link = NULL;
    currentvertex = 0;
    
    /*큐와 스택을 위한 초기화*/
    top = -1;

	front = rear = -1;
}

void FreeGraph(Vertex* v)
{
    Vertex* temp, * next;
    int i=0;
    /*첫 번째 for문에서 adjList vertex를 차례로 가리키게 함*/
    for(temp = &v[0]; i < MAX_Vertex; i++, temp = &v[i])
     {
         while(1) //첫 번째 if문에 해당되면 pass하기위해 while문을 사용
         {
         if(temp->link == NULL) //해당 vertex에 edge가 없다면
            break; //바로 반복문을 탈출한다
         else if(temp->link->link == NULL) //해당 vertex에 edge가 하나라면
				free(temp->link); //하나의 edge를 free한다
		 else if(temp->link->link->link == NULL) //해당 vertex에 edge가 두 개라면
		  {
			free(temp->link->link); //두 번째 vertex를 free한다
			free(temp->link); //첫 번째 vertex를 free한다
		  }
		 else
		  {
			temp = temp->link;
			next = temp->link;
			//현재 temp는 첫 번째 edge를 next는 두 번째 edge를 가리키고 있다.
			do
			{
				free(temp);
				temp = next;
				next = next->link;
			}while(next->link != NULL); //반복문 안에서 temp를 free하고 temp와 next는 끝까지 이동한다
			//반복문을 나왔으므로 temp와 next만 free해주면 해당 vertex는 free가 끝난다
			free(temp);
			free(next);
		  }
         }
     }
	 //adjList만 free 해 주면 된다
	 for(int i=0;i<MAX_Vertex;i++)
	  free(&v[i]);
}