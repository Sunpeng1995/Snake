void enqueue(struct node n);
struct node dequeue();

struct node{
	int x;
	int y;
	int preIndex;
};
struct node queue[512], qtemp;
int qhead = 0, qtail = 0;

void enqueue(struct node n){
	queue[qtail] = n;
	qtail++;
}

struct node dequeue(){
	qhead++;
	return queue[qhead - 1];
}

struct node toNext(int x, int y, int pre, int maze[][]){
	struct node t;
	maze[x][y] = 2;
	t.x = x;
	t.y = y;
	t.preIndex = pre;
	return t;
}