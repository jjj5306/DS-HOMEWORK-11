#include <stdio.h>
#include <stdlib.h>
/*최대 vertex의 수는 10개로 설정한다.*/
#define MAX_Vertex 10

/*Graph는 Adjacent List로 구현한다.*/
/*Edge 구조체는 Edge를 나타낸다 */
typedef struct Edge {
	struct Edge* link;
} Edge;

/*Vertex 구조체는 Vertex를 인접 리스트로 나타내며 data로 Vertex에 들어있는 data, link로 다음 Edge를 가리킨다.*/
typedef struct Vertex {
	int data;
	struct Edge* link;
} Vertex;

/*Vertexhead 구조체는 배열로 선언되어 index에 맞게 vertex 번호를 가리키게 한다. */
typedef struct Vertexhead {
	struct Vertex* link;
}Vertexhead;


/* 현재 Vertex가 얼마나 있는지는 currentvertex로 관리한다. */
int currentvertex = 0;

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


void InitializeGraph(Vertexhead* v); //Graph 초기화 함수
void FreeGraph(Vertexhead* v); //Vertex free 함수

void Insertvertex(Vertexhead* v); //vertex를 삽입한다.
void Insertedge();


int main()
{
	char command;
	
	/*adjList를 통해서 Graph를 나타 낼 것이다. Insert Vertex를 호출하면 headList가 해당 번호에 맞게 vertex를 활성화한다. */
	Vertexhead headList[MAX_Vertex] ;

	printf("2020039071 JoJunHwa\n");

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
			InitializeGraph(headList);
			break;
		case 'v': case 'V':
			/*currentvertex가 MAX_Vertex를 넘지 않아야 한다*/
			if (currentvertex >= MAX_Vertex)
			{
				printf("Vertex 수가 최대입니다.\n");
				break;
			}
			Insertvertex(headList);
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
	FreeGraph(headList);
	return 1;
}

void InitializeGraph(Vertexhead* v)
{
	/*그래프가 비어있지 않다면 먼저 free를 진행해준다. currentcertex 는 insert vertex가 일어날 때 마다 ++되므로 0이 아니면 그래프가 비지 않았을 때 뿐이다*/
	if (currentvertex != 0)
		FreeGraph(v);

	/*headList의 link도 초기화 해준다. */
	for (int i = 0; i < MAX_Vertex; i++)
		v[i].link = NULL;
	currentvertex = 0;

	/*큐와 스택을 위한 초기화*/
	top = -1;

	front = rear = -1;
}

void FreeGraph(Vertexhead* v)
{
	Vertexhead* head;
	Edge* temp, * next;
	int i = 0;
	/*그래프가 비어있는 경우 그냥 종료*/
	if (currentvertex == 0)
		return;
	/*첫 번째 for문에서 adjList vertex를 차례로 가리키게 함*/
	for (head = &v[0]; i < MAX_Vertex; i++, head = &v[i])
	{
		while (1) //첫 번째 if문에 해당되면 pass하기위해 while문을 사용
		{
			if (head->link == NULL) //해당 head에 vertex가 없다면
				break; //바로 반복문을 탈출한다
			else if (head->link->link == NULL) //해당 head에 edge는 없고 vertex만 존재한다면
			{
				free(head->link); //하나의 edge를 free한다
				head->link = NULL;
			}
			else if (head->link->link->link == NULL) //해당 vertex에 edge가 한 개라면
			{
				free(head->link->link); //두 번째 vertex를 free한다
				free(head->link); //첫 번째 vertex를 free한다
				head->link = NULL;
			}
			else
			{
				temp = head->link->link;
				next = temp->link;
				//현재 temp는 첫 번째 edge를 next는 두 번째 edge를 가리키고 있다.
				do
				{
					free(temp);
					temp = next;
					next = next->link;
				} while (next->link != NULL); //반복문 안에서 temp를 free하고 temp와 next는 끝까지 이동한다
				//반복문을 나왔으므로 temp와 next만 free해주면 해당 vertex는 free가 끝난다
				free(temp);
				free(next);
				free(head->link);
				head->link = NULL;
			}
		}
	}
}

void Insertvertex(Vertexhead* v)
{
	int vertexnumber = 0;
	printf("Vertex Number (0~9) : ");
	scanf("%d", &vertexnumber);

	/*오류 검사*/
	if (vertexnumber >= 0 && vertexnumber <= 9) //vertexnumber가 0~9인지 체크
	{
		if (v[vertexnumber].link != NULL) //vertexnumber의 vertex가 존재하는지 체크
		{
			printf("이미 존재하는 vertex 입니다.\n");
			return;
		}
	}
	else
	{
		printf("유효하지 않은 입력입니다.\n");
		return;
	}
	/*vertexhead의 vertexnumber의 link는 vertex를 가리킬 것이다 */
	v[vertexnumber].link = (Vertex*)malloc(sizeof(Vertex));
	v[vertexnumber].link->link = NULL;
	currentvertex++;
}