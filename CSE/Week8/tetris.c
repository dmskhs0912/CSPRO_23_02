#include "tetris.h"

static struct sigaction act, oact;

int main(){
	int exit=0;

	initscr();
	noecho();
	keypad(stdscr, TRUE);	
	

	srand((unsigned int)time(NULL));
	first = (_Node*)malloc(sizeof(_Node));
	first->score = -1;
	first->link = NULL;

	createRankList();

	while(!exit){
		clear();
		switch(menu()){
		case MENU_PLAY: play(); break;
		case MENU_RANK: rank(); break;
		//case MENU_RECP: recommendedPlay(); break;
		case MENU_EXIT: exit=1; break;
		default: break;
		}
	}

	endwin();
	system("clear");
	return 0;
}

void InitTetris(){
	int i,j;

	for(j=0;j<HEIGHT;j++)
		for(i=0;i<WIDTH;i++)
			field[j][i]=0;

	nextBlock[0]=rand()%7;
	nextBlock[1]=rand()%7;
	nextBlock[2]=rand()%7;
	blockRotate=0;
	blockY=-1;
	blockX=WIDTH/2-2;
	score=0;	
	gameOver=0;
	timed_out=0;
	recRoot = (_RecNode*)malloc(sizeof(_RecNode));
	recRoot->lv = 0;
	recRoot->score = score;
	recRoot->parent = NULL;
	memcpy(recRoot->f, field, sizeof(field));
	//recommend(recRoot);
	modified_recommend(recRoot);
	freeAll(recRoot);
	DrawOutline();
	DrawField();
	DrawBlockWithFeatures(blockY,blockX,nextBlock[0],blockRotate);
	DrawNextBlock(nextBlock);
	PrintScore(score);
}

void DrawOutline(){	
	int i,j;
	/* 블럭이 떨어지는 공간의 태두리를 그린다.*/
	DrawBox(0,0,HEIGHT,WIDTH);

	/* next block을 보여주는 공간의 태두리를 그린다.*/
	move(2,WIDTH+10);
	printw("NEXT BLOCK");
	DrawBox(3,WIDTH+10,4,8);

	move(9, WIDTH+10);
	DrawBox(9,WIDTH+10,4,8);

	/* score를 보여주는 공간의 태두리를 그린다.*/
	move(16,WIDTH+10);
	printw("SCORE");
	DrawBox(17,WIDTH+10,1,8);
}

int GetCommand(){
	int command;
	command = wgetch(stdscr);
	switch(command){
	case KEY_UP:
		break;
	case KEY_DOWN:
		break;
	case KEY_LEFT:
		break;
	case KEY_RIGHT:
		break;
	case ' ':	/* space key*/
		/*fall block*/
		break;
	case 'q':
	case 'Q':
		command = QUIT;
		break;
	default:
		command = NOTHING;
		break;
	}
	return command;
}

int ProcessCommand(int command){
	int ret=1;
	int drawFlag=0;
	switch(command){
	case QUIT:
		ret = QUIT;
		break;
	case KEY_UP:
		if((drawFlag = CheckToMove(field,nextBlock[0],(blockRotate+1)%4,blockY,blockX)))
			blockRotate=(blockRotate+1)%4;
		break;
	case KEY_DOWN:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY+1,blockX)))
			blockY++;
		break;
	case KEY_RIGHT:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX+1)))
			blockX++;
		break;
	case KEY_LEFT:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX-1)))
			blockX--;
		break;
	default:
		break;
	}
	if(drawFlag) DrawChange(field,command,nextBlock[0],blockRotate,blockY,blockX);
	return ret;	
}

void DrawField(){
	int i,j;
	for(j=0;j<HEIGHT;j++){
		move(j+1,1);
		for(i=0;i<WIDTH;i++){
			if(field[j][i]==1){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(".");
		}
	}
}


void PrintScore(int score){
	move(18,WIDTH+11);
	printw("%8d",score);
}

void DrawNextBlock(int *nextBlock){
	int i, j;
	for( i = 0; i < 4; i++ ){
		move(4+i,WIDTH+13);
		for( j = 0; j < 4; j++ ){
			if( block[nextBlock[1]][0][i][j] == 1 ){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(" ");
		}
		move(10+i, WIDTH+13);
		for( j = 0; j < 4; j++ ){
			if( block[nextBlock[2]][0][i][j] == 1 ){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(" ");
		}
	}
}

void DrawBlock(int y, int x, int blockID,int blockRotate,char tile){
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++){
			if(block[blockID][blockRotate][i][j]==1 && i+y>=0){
				move(i+y+1,j+x+1);
				attron(A_REVERSE);
				printw("%c",tile);
				attroff(A_REVERSE);
			}
		}

	move(HEIGHT,WIDTH+10);
}

void DrawBox(int y,int x, int height, int width){
	int i,j;
	move(y,x);
	addch(ACS_ULCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_URCORNER);
	for(j=0;j<height;j++){
		move(y+j+1,x);
		addch(ACS_VLINE);
		move(y+j+1,x+width+1);
		addch(ACS_VLINE);
	}
	move(y+j+1,x);
	addch(ACS_LLCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_LRCORNER);
}

void play(){
	int command;
	clear();
	act.sa_handler = BlockDown;
	sigaction(SIGALRM,&act,&oact);
	InitTetris();
	do{
		if(timed_out==0){
			alarm(1);
			timed_out=1;
		}

		command = GetCommand();
		if(ProcessCommand(command)==QUIT){
			alarm(0);
			DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
			move(HEIGHT/2,WIDTH/2-4);
			printw("Good-bye!!");
			refresh();
			getch();

			return;
		}
	}while(!gameOver);

	alarm(0);
	getch();
	DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
	move(HEIGHT/2,WIDTH/2-4);
	printw("GameOver!!");
	refresh();
	getch();
	newRank(score);
}

char menu(){
	printw("1. play\n");
	printw("2. rank\n");
	printw("3. recommended play\n");
	printw("4. exit\n");
	return wgetch(stdscr);
}

/////////////////////////첫주차 실습에서 구현해야 할 함수/////////////////////////

int CheckToMove(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){
	int i, j;
	for(i=0; i<BLOCK_HEIGHT; i++){
		for(j=0; j<BLOCK_WIDTH; j++){
			if(block[currentBlock][blockRotate][i][j] == 1){
				if(i+blockY<0 || i+blockY>=HEIGHT || j+blockX<0 || j+blockX>=WIDTH) // field 범위 벗어난 경우
					return 0;
				if(f[i+blockY][j+blockX] == 1) // 이미 해당 field에 블록이 놓인 경우
					return 0;
			}
		}
	}

	return 1;
}

void DrawChange(char f[HEIGHT][WIDTH],int command,int currentBlock,int blockRotate, int blockY, int blockX){
	int oldRotate, oldY, oldX, i, j;
	int oldShadowY;
	oldRotate = blockRotate;
	oldY = blockY;
	oldX = blockX;
	
	switch(command){ 
	case KEY_UP :
		oldRotate = (blockRotate-1) % 4;
		break;
	case KEY_DOWN :
		oldY--;
		break;
	case KEY_RIGHT :
		oldX--;
		break;
	case KEY_LEFT :
		oldX++;
		break;
	}
	
	for(i=1; i<HEIGHT; i++){
		if(!CheckToMove(f, currentBlock, oldRotate, oldY+i, oldX))
			break;
	}
	oldShadowY = oldY+i-1;
	for(i=0; i<BLOCK_HEIGHT; i++){
		for(j=0; j<BLOCK_WIDTH; j++){
			if(block[currentBlock][oldRotate][i][j] == 1 && i+oldY >= 0){
				move(i+oldY+1, j+oldX+1);
				printw(".");
				move(i+oldShadowY+1, j+oldX+1);
				printw(".");
			}
		}
	}
	DrawBlockWithFeatures(blockY, blockX, currentBlock, blockRotate);
}

void BlockDown(int sig){
	if(CheckToMove(field, nextBlock[0], blockRotate, blockY+1, blockX)){
		blockY++;
		DrawChange(field, KEY_DOWN, nextBlock[0], blockRotate, blockY, blockX);
		timed_out=0;
		return;
	}

	if(blockY==-1)
		gameOver = 1;
	
	score += AddBlockToField(field, nextBlock[0], blockRotate, blockY, blockX);
	score += DeleteLine(field);
	nextBlock[0] = nextBlock[1];
	nextBlock[1] = nextBlock[2];
	nextBlock[2] = rand() % 7;
	recRoot = (_RecNode*)malloc(sizeof(_RecNode));
	recRoot->lv = 0;
	recRoot->score = score;
	recRoot->parent = NULL;
	memcpy(recRoot->f, field, sizeof(field));
	//recommend(recRoot);
	modified_recommend(recRoot);
	freeAll(recRoot);
	blockRotate = 0;
	blockY = -1;
	blockX = WIDTH/2-2;
	timed_out=0;
	DrawNextBlock(nextBlock);
	PrintScore(score);
	DrawField();
}

int AddBlockToField(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){
	int i, j;
	int touched = 0;
	for(i=0; i<BLOCK_HEIGHT; i++){
		for(j=0; j<BLOCK_WIDTH; j++){
			if(block[currentBlock][blockRotate][i][j] == 1){
				if(f[i+blockY+1][j+blockX] == 1 || i+blockY+1 == HEIGHT) touched++;
				f[i+blockY][j+blockX] = 1;
			}
		}
	}

	return touched*10;
}

int DeleteLine(char f[HEIGHT][WIDTH]){
	int deletedLine = 0;
	int i, j, k, flag;
	for(i=0; i<HEIGHT; i++){
		flag = 1;
		for(j=0; j<WIDTH; j++){
			if(f[i][j] == 0 ){
				flag = 0;
				break;
			}
		}
		if(flag){
			deletedLine++;
			for(k=i-1; k>=0; k--){
				for(j=0; j<WIDTH; j++){
					f[k+1][j] = f[k][j];
				}
			}

			for(j=0; j<WIDTH; j++)
				f[0][j] = 0;
		}
	}

	return deletedLine * deletedLine * 100;
}

///////////////////////////////////////////////////////////////////////////

void DrawShadow(int y, int x, int blockID,int blockRotate){
	int i, j;
	int shadowY;
	for(i=1; i<HEIGHT; i++){
		if(!CheckToMove(field, blockID, blockRotate, y+i, x))
			break;
	}
	shadowY = y+i-1;
	DrawBlock(shadowY, x, blockID, blockRotate, "/");

}

void DrawBlockWithFeatures(int y, int x, int blockID, int blockRotate){
	DrawBlock(y, x, blockID, blockRotate, " ");
	DrawShadow(y, x, blockID, blockRotate);
	DrawBlock(recommendY, recommendX, blockID, recommendR, "R");
}

void createRankList(){
	FILE *fp;
	int i, j;
	char newName[NAMELEN];
	int newScore;
	
	fp = fopen("rank.txt", "r");

	if (fscanf(fp, "%d", &score_number) != EOF) {
		if(score_number > 0){
			fscanf(fp, "%s %d", newName, &newScore);
			strcpy(first->name, newName);
			first->score = newScore;
		}
		
		while(fscanf(fp, "%s %d", newName, &newScore) != EOF){
			insertNode(&first, newName, newScore);
		}
	}
	else{
		fclose(fp);
		return;
	}
	fclose(fp);
}

void insertNode(_Node** first, char* newName, int newScore){
	_Node *newNode = (_Node*)malloc(sizeof(_Node));
	strcpy(newNode->name, newName);
	newNode->score = newScore;
	newNode->link = NULL;

	if((*first)->score == -1){
		(*first) = newNode;
		return;
	}

	if((*first)->score < newNode->score){
		newNode->link = *first;
		*first = newNode;
	}
	else{
		_Node* current = *first;
		_Node* previous = NULL;
		while(current != NULL && current->score >= newNode->score){
			previous = current;
			current = current->link;
		}
		previous->link = newNode;
		newNode->link = current;
	}
}

void rank(){
	int X=1, Y=score_number, ch, i, j;
	_Node* current = first;
	clear();

	printw("1. list ranks from X to Y\n");
	printw("2. list ranks by a specific name\n");
	printw("3. delete a specific rank\n");

	ch = wgetch(stdscr);

	if (ch == '1') {
		echo();
		printw("X: ");
		scanw("%d", &X);
		printw("Y: ");
		scanw("%d", &Y);
		noecho();
		printw("          name          |  score	\n");
		printw("----------------------------------\n");

		if(X > Y){
			printw("search failure: no rank in the list\n");
			getch();
			return;
		}

		for(i=1; i<=Y; i++){
			if(current == NULL) break;
			if(i >= X)
				printw("%-24s| %d\n", current->name, current->score);
			current = current->link;
		}
	}

	else if ( ch == '2') {
		char str[NAMELEN+1];
		int check = 0;
		echo();
		printw("name: ");
		scanw("%s", str);
		noecho();
		printw("          name          |  score	\n");
		printw("----------------------------------\n");
		for(i=0; i<score_number; i++){
			if(!strcmp(str, current->name)){
				check++;
				printw("%-24s| %d\n", current->name, current->score);
			}
			current = current->link;
		}
		if(!check)
			printw("search failure: no name in the list\n");
	}

	else if ( ch == '3') {
		int num;
		_Node* previous = NULL;
		printw("input the rank: ");
		echo();
		scanw("%d", &num);
		noecho();
		printw("\n");
		if(num<=0 || num>score_number){
			printw("search failure: the rank not in the list\n");
			getch();
			return;
		}

		for(i=1; i<num; i++){
			previous = current;
			current = current->link;
		}
		if(previous)
			previous->link = current->link;
		else
			first = current->link;
		free(current);
		score_number--;
		writeRankFile();
		printw("result: the rank deleted\n");
	}
	getch();
}

void writeRankFile(){
	// 목적: 추가된 랭킹 정보가 있으면 새로운 정보를 "rank.txt"에 쓰고 없으면 종료
	int i;
	_Node* current = first;
	//1. "rank.txt" 연다
	FILE *fp = fopen("rank.txt", "wt");

	//2. 랭킹 정보들의 수를 "rank.txt"에 기록
	fprintf(fp, "%d\n", score_number);

	//3. 탐색할 노드가 더 있는지 체크하고 있으면 다음 노드로 이동, 없으면 종료
	while(current != NULL){
		fprintf(fp, "%s %d\n", current->name, current->score);
		current = current->link;
	}
	fclose(fp);
}

void newRank(int score){
	char str[NAMELEN+1];
	int i, j;
	clear();
	echo();
	printw("Your name: ");
	scanw("%s", str);
	noecho();
	
	score_number++;
	insertNode(&first, str, score);
	writeRankFile();
}

void DrawRecommend(int y, int x, int blockID,int blockRotate){
	DrawBlock(y, x, blockID, blockRotate, "R");
}

int recommend(_RecNode *root){
	int max=0;
	int i, j, rotateNum;
	int y = 0, childNum = 0, curScore=0;
	int id = nextBlock[root->lv];
	_RecNode *currentNode;
	if(id == 4) rotateNum = 1;
	else if(id == 0 || id == 5 || id == 6) rotateNum = 2;
	else rotateNum = 4;

	for(i=0; i<rotateNum; i++){
		for(j=0; j<WIDTH; j++){
			if(!CheckToMove(root->f, id, i, 0, j)) continue;
			for(y=0; y<HEIGHT; y++)
				if(!CheckToMove(root->f, id, i, y, j)) break;
			if(y==0) continue;
			root->c[childNum] = (_RecNode*)malloc(sizeof(_RecNode));
			currentNode = root->c[childNum];
			childNum++;
			currentNode->lv = root->lv + 1;
			currentNode->curblockID = id;
			currentNode->curR = i;
			currentNode->curX = j;
			currentNode->curY = y-1;
			currentNode->childnum = 0;
			memcpy(currentNode->f, root->f, sizeof(root->f));
			currentNode->score = root->score;
			currentNode->score += AddBlockToField(currentNode->f, id, i, y-1, j);
			currentNode->score += DeleteLine(currentNode->f);
			currentNode->parent = root;

			if(currentNode->lv < VISIBLE_BLOCKS){
				if(root->lv == 0){
					curScore = recommend(currentNode);
					if(curScore > max){
						recommendR = currentNode->curR;
						recommendX = currentNode->curX;
						recommendY = currentNode->curY;
						max = curScore;
					}
				}
				else max = MAX(max, recommend(currentNode));

			} 
			else if (currentNode->lv == VISIBLE_BLOCKS) {
				if(max < currentNode->score){
					max = currentNode->score;
				}
			}
			
		}

	}

	root->childnum = childNum;
	return max;
}

int modified_recommend(_RecNode *root){
	int max=0, localMax=0, localMaxIdx=0;
	int i, j, rotateNum;
	int y = 0, childNum = 0, curScore=0;
	int id = nextBlock[root->lv];
	_RecNode *currentNode;
	if(id == 4) rotateNum = 1;
	else if(id == 0 || id == 5 || id == 6) rotateNum = 2;
	else rotateNum = 4;

	for(i=0; i<rotateNum; i++){
		for(j=0; j<WIDTH; j++){
			if(!CheckToMove(root->f, id, i, 0, j)) continue;
			for(y=0; y<HEIGHT; y++)
				if(!CheckToMove(root->f, id, i, y, j)) break;
			if(y==0) continue;
			root->c[childNum] = (_RecNode*)malloc(sizeof(_RecNode));
			currentNode = root->c[childNum];
			childNum++;
			currentNode->lv = root->lv + 1;
			currentNode->curblockID = id;
			currentNode->curR = i;
			currentNode->curX = j;
			currentNode->curY = y-1;
			currentNode->childnum = 0;
			memcpy(currentNode->f, root->f, sizeof(root->f));
			currentNode->score = root->score;
			currentNode->score += AddBlockToField(currentNode->f, id, i, y-1, j);
			currentNode->score += DeleteLine(currentNode->f);
			currentNode->parent = root;
		}
	}

	for(i=0; i<childNum; i++){
		if(root->c[i]->score > localMax){
			localMax = root->c[i]->score;
			localMaxIdx = i;
		}
	}
	if(root->lv+1 < VISIBLE_BLOCKS){
		if(root->lv == 0){
			curScore = modified_recommend(root->c[localMaxIdx]);
			if(curScore > max){
				recommendR = root->c[localMaxIdx]->curR;
				recommendX = root->c[localMaxIdx]->curX;
				recommendY = root->c[localMaxIdx]->curY;
				max = curScore;
			}
		}
		else max = MAX(max, modified_recommend(root->c[localMaxIdx]));
	}

	else if (root->lv+1 == VISIBLE_BLOCKS) {
		max = root->c[localMaxIdx]->score;
	}
	
	return max;
}

void freeAll(_RecNode *node){
	int i;
	for(i=0; i<node->childnum; i++)
		freeAll(node->c[i]);
	free(node);
}



void recommendedPlay(){
	/*clear();
	InitTetris();
	do{
		blockRotate = recommendR;
		blockX = recommendX;
		blockY = recommendY;
		score += AddBlockToField(field, nextBlock[0], blockRotate, blockY, blockX);
		score += DeleteLine(field);
		nextBlock[0] = nextBlock[1];
		nextBlock[1] = nextBlock[2];
		nextBlock[2] = rand() % 7;
		recRoot = (_RecNode*)malloc(sizeof(_RecNode));
		recRoot->lv = 0;
		recRoot->score = score;
		recRoot->parent = NULL;
		memcpy(recRoot->f, field, sizeof(field));
		recommend(recRoot);
		freeAll(recRoot);
		DrawNextBlock(nextBlock);
		PrintScore(score);
		DrawField();
		sleep(1);
		if(blockY==-1) gameOver=1;
	}while(!gameOver);

	getch();
	DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
	move(HEIGHT/2,WIDTH/2-4);
	printw("GameOver!!");
	refresh();
	getch();*/
}
