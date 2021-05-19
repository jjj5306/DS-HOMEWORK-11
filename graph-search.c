#include <stdio.h>
#include <stdlib.h>


/*최대 vertex의 수는 10개로 설정한다.*/
#define MAX_Vertex 10

/*Graph는 Adjacent List로 구현한다.*/
/*Edge 구조체는 Edge를 나타낸다 */
typedef struct Edge {
	struct Edge* link; //다음 Edge
	int vertex; //가리키는 vetex 번호
} Edge;

/*Vertex 구조체는 Vertex를 인접 리스트로 나타내며 data로 Vertex에 들어있는 data, link로 다음 Edge를 가리킨다.*/
typedef struct Vertex {
	int data;
	struct Edge* link;
	int visitflag; //탐색에서 사용할 flag
} Vertex;

/*Vertexhead 구조체는 배열로 선언되어 index에 맞게 vertex 번호를 가리키게 한다. */
typedef struct Vertexhead {
	struct Vertex* link;
}Vertexhead;

/* 현재 Vertex가 얼마나 있는지는 currentvertex로 관리한다. */
int currentvertex = 0;

/* for stack */
#define MAX_STACK_SIZE		20
int stack[MAX_STACK_SIZE];
int top = -1;
int currentstack = 0;

int pop();
void push(int aVertex);

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
void Insertedge(Vertexhead* v);

void DFS_iterative(Vertexhead* v);
/*규칙에 맞게 push 하고 push하면서 차례로 dfs 리스트에 넣기 위해서 총 몇개를 push했는지 기록하는 currentstack 사용 자세한 규칙은 함수 내부에 서술*/
int find_least_index(Vertexhead* v); //vertex 중 Edge가 존재하면서 vertexnumber가 가장 작은 vertex의 number 리턴
int find_next_index(Vertexhead* head, Vertex* v); //다음에 탐색할 vertex를 찾는다
int main()
{
	char command;

	/*adjList를 통해서 Graph를 나타 낼 것이다. Insert Vertex를 호출하면 headList가 해당 번호에 맞게 vertex를 활성화한다. */
	Vertexhead headList[MAX_Vertex];

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
		case 'd': case 'D':
			Insertedge(headList);
			break;
		case 'r': case 'R':
			DFS_iterative(headList);
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
	currentstack = 0;
	front = -1;
	rear = -1;
	for (int i = 0; i < MAX_STACK_SIZE; i++)
	{
		stack[i] = 0;
		queue[i] = 0;
	}
	
}

void FreeGraph(Vertexhead* v)
{
	Vertexhead* head;
	Vertex* vertex;
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
				while (next != NULL) //next가 NULL이면 반복문을 탈출한다
				{
					free(temp);
					temp = next;
					next = next->link;
				}
				//반복문을 나왔으므로 temp만 free해주면 해당 vertex는 free가 끝난다
				free(temp);
				free(head->link);
				head->link = NULL;
			}
		}
	}
}

void Insertvertex(Vertexhead* v)
{
	int vertexnumber = 0, data = 0;
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
	v[vertexnumber].link = (Vertexhead*)malloc(sizeof(Vertex));
	v[vertexnumber].link->visitflag = 0;
	v[vertexnumber].link->link = NULL; //Edge는 NULL
	printf("Data : ");
	scanf("%d", &data);
	v[vertexnumber].link->data = data;
	currentvertex++;
}

void Insertedge(Vertexhead* v)
{
	int start, destination;
	Edge* check = NULL;
	Vertex* check2 = NULL; //check2는 vertex에 Edge가 없을 떄 사용
	printf("Edge를 연결 할 출발 vertex number을 입력하세요.\n");
	scanf("%d", &start);
	/*생성된 vertex인지 확인*/
	if (v[start].link == NULL)
	{
		printf("생성되지 않은 vertex입니다.\n");
		return;
	}

	printf("도착할 vertex number을 입력하세요.\n");
	scanf("%d", &destination);
	/*생성된 vertex인지 확인*/
	if (v[destination].link == NULL)
	{
		printf("생성되지 않은 vertex입니다.\n");
		return;
	}

	/*이미 존재하는 Edge인지 확인*/
	/*먼저 destination의 리스트부터 확인*/
	check = v[destination].link->link;
	while (check != NULL) //check가 start의 리스트 Edge를 모두 검사할 때 까지 반복
	{
		if (check->vertex == start) //destination까지의 Edge가 존재한다면 종료
		{
			printf("이미 존재하는 Edge입니다. \n");
			return;
		}
		check = check->link;
	}
	/* start의 리스트도 확인*/
	check = v[start].link->link;
	if (check != NULL) //start의 리스트의 Edge가 하나도 없으면 다르게 처리
	{
		while (check->link != NULL) //check가 start의 리스트 Edge를 마지막 빼고 모두 검사할 때 까지 반복
		{
			if (check->vertex == destination) //destination까지의 Edge가 존재한다면 종료
			{
				printf("이미 존재하는 Edge입니다. \n");
				return;
			}
			check = check->link;
		}
		if (check->vertex == destination)
		{
			printf("이미 존재하는 Edge입니다. \n");
			return;
		}
	}
	else
	{
		/*start의 리스트에 Egde가 하나도 없는 경우 */
		check2 = v[start].link; //check2가 start의 리스트의 vertex를 가리키고 있다
		/*check2 뒤에 Edge를 삽입하면 끝*/
		check2->link = (Edge*)malloc(sizeof(Edge));
		check2->link->vertex = destination;
		check2->link->link = NULL;
		printf("vertex %d번에서 vertex %d번 까지 Edge를 생성했습니다.\n", start, destination);
		return;
	}
	/*현재 check는 start의 리스트의 끝을 가리키고 있다.*/
	check->link = (Edge*)malloc(sizeof(Edge));
	check->link->vertex = destination;
	check->link->link = NULL;
	//Edge 생성 완료
	printf("vertex %d번에서 vertex %d번 까지 Edge를 생성했습니다.\n", start, destination);
}

void DFS_iterative(Vertexhead* v)
{
	/* 라인별로 주석을 달기 어려워서 미리 알고리즘을 설명했습니다.
	가장 vertex number가 작은 vertex를 찾아서 그 vertex부터 push하고
	인접한 vertex들 중에서 visit하지 않았고 vertex number가 가장 작은 vertex를 push한다.
	인접한 vertex가 없으면 스택에서 pop하고 top에 있는 vertex에 대해서 다시 인접한 vertex를 조사하는 식으로
	구성하였다. push할 때 배열의 currentstack index에 data와 vertex number을 저장해서 나중에 출력할 때 사용한다.*/

	/*
	vertex number가 가장 작고 Edge가 존재하는 vertex를 push
	while(스택이 빌 때 까지 반복한다. )
	{
		while(top의 vertex의 non-visit edge가 없을때까지)
		{
			인접한 vertex중 가장 번호가 작은 vertex를 push
		}
		pop
	}
	*/

	int next_index = find_least_index(v);
	int DFS_Vertexnumber[MAX_Vertex] = { 0, }; //DFS탐색 후 차례로 탐색 결과의 Vertexnumber가 저장 될 배열
	int DFS_Vertexdata[MAX_Vertex]={ 0, }; //DFS탐색 후 차례로 탐색 결과의 Vertex data가 저장 될 배열
	if (next_index == -1)
	{
		printf("Egde가 존재하지 않는 그래프입니다.\n");
		return;
	}

	DFS_Vertexnumber[currentstack] = next_index;
	DFS_Vertexdata[currentstack] = v[next_index].link->data;
	v[next_index].link->visitflag = 1;
	push(next_index); //탐색 시작점의 index를 push

	while (top != -1) //스택이 빌 때 까지 반복한다
	{
		next_index = find_next_index(v, v[stack[top]].link);
		while (next_index != -1) //다음 방문할 Vertex가 없을 때 까지 반복한다
		{ //다음에 방문할 vertex를 push하고 출력하기위한 배열에 넣는다
			DFS_Vertexnumber[currentstack] = next_index;
			DFS_Vertexdata[currentstack] = v[next_index].link->data;
			v[next_index].link->visitflag = 1;
			push(next_index);
			next_index = find_next_index(v, v[stack[top]].link);
		}
		pop();
	}

	printf("Vertex number : ");
	for (int i = 0; i < currentstack; i++)
		printf("%d ", DFS_Vertexnumber[i]);
	printf("\n");

	printf("Vertex data : ");
	for (int i = 0; i < currentstack; i++)
		printf("%d ", DFS_Vertexdata[i]);
}

int find_least_index(Vertexhead* v)
{
	for (int i = 0; i < MAX_Vertex; i++)
		if(v[i].link != NULL)
			if (v[i].link->link != NULL)
				return i;
	return -1; //못 찾았으면 -1 리턴
}

int find_next_index(Vertexhead* head, Vertex* v)
{
	/*입력 파라메터로 들어온 vertex의 다음에 방문할 vertex를 찾는다.
	 visitflag가 0이고 가장 vertexnumber가 작은 vertex를 찾으면 된다. */
	int min_index = 11;
	Edge* temp;
	temp = v->link;
	while (temp != NULL) //temp가 해당 vertex의 Edge를 모두 탐색할 때 까지 반복
	{
		if (v[temp->vertex].visitflag == 0) //아직 방문하지 않은 인접 Vertex가 있고 
			if (min_index > temp->vertex) //그 vertex number가 전에 탐색한 vertex number보다 작다면 min_index에 넣는다
				min_index = temp->vertex;
		temp = temp->link;
	}
	if (min_index == 11)
		return -1; //방문하지않은 인접 vertex가 없다면 -1 리턴
	else
		return min_index;
}

int pop()
{
	int vertex;
	if (top == -1) //스택이 비어있다면 -1 리턴
		return -1;
	else
	{
		vertex = top--;
		return vertex;
	}
}

void push(int aVertex)
{
	stack[++top] = aVertex;
	currentstack++;
}