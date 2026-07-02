#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

HANDLE hand;

enum block_type{
	O,
	J,
	L,
	I,
	S,
	Z,
	T
};
int block_type_num = 7;

int cur_x=0, cur_y=0;
int score = 0;
#define HEIGHT 14
#define WIDTH 18
int surface[HEIGHT][WIDTH]={0}; 

#define block_h 4
#define block_w 4
int BlockO[block_h][block_w] = {
	{0,0,0,0},
	{0,1,1,0},
	{0,1,1,0},
	{0,0,0,0}
};

int BlockJ[block_h][block_w] = {
	{0,0,1,0},
	{0,0,1,0},
	{0,1,1,0},
	{0,0,0,0}
};
int BlockL[block_h][block_w] = {
	{0,1,0,0},
	{0,1,0,0},
	{0,1,1,0},
	{0,0,0,0}
};
int BlockI[block_h][block_w] = {
	{0,1,0,0},
	{0,1,0,0},
	{0,1,0,0},
	{0,1,0,0}
};
int BlockS[block_h][block_w] = {
	{0,0,0,0},
	{0,1,1,0},
	{1,1,0,0},
	{0,0,0,0}
};
int BlockZ[block_h][block_w] = {
	{0,0,0,0},
	{1,1,0,0},
	{0,1,1,0},
	{0,0,0,0}
};
int BlockT[block_h][block_w] = {
	{0,0,0,0},
	{1,1,1,0},
	{0,1,0,0},
	{0,0,0,0}
};


int block_cur[block_h][block_w]={0};

int isCollision(int x, int y);

void setCursorVisable(int v){
	CONSOLE_CURSOR_INFO cursor_info = {100, v};
	SetConsoleCursorInfo(hand, &cursor_info); 
}
void gotoxy(int x, int y){
	COORD loc;
	loc.X = x;
	loc.Y = y;
	SetConsoleCursorPosition(hand, loc);
}

void printxy(char *str, int x, int y){
	gotoxy(x,y);
	printf("%s",str);
}

void print_surface(){
	int x,y;
	for (x=0; x<WIDTH;x++){
		for (y=0;y<HEIGHT;y++) {
			int row = y;
			int col = x;
			if (surface[row][col]==0){
				printxy(" ",x,y);
			}else {
				printxy("O",x,y);
			}
		}
	}
}


void copy_block(int block_s[][block_w],int block_d[][block_w]){
	int w,h;
	for (w=0;w<block_w;w++){
		for (h=0;h<block_h;h++){
			block_d[h][w] = block_s[h][w];
		}
	} 	
}

void make_new_block(){
	enum block_type type = (int)(rand()%block_type_num);
	switch (type){
		case O:
			copy_block(BlockO,block_cur);
			break;
		case J:
			copy_block(BlockJ,block_cur);
			break;
		case L:
			copy_block(BlockL,block_cur);
			break;
		case I:
			copy_block(BlockI,block_cur);
			break;
		case S:
			copy_block(BlockS,block_cur);
			break;
		case Z:
			copy_block(BlockZ,block_cur);
			break;
		case T:
			copy_block(BlockT,block_cur);
			break;
		default:
			break;			
	}
	cur_x = (WIDTH-block_w)/2;
	cur_y = 0;
	
}

void rotate_block(){
	int temp[block_h][block_w] = {0};
	copy_block(block_cur, temp);
	int w,h;
	for (w=0;w<block_w;w++){
		for (h=0;h<block_h;h++){
			block_cur[h][w] = temp[block_w-1-w][h];
		}
	} 	
	
}

void land_block(){
	int w,h;
	for (w=0;w<block_w;w++){
		for (h=0;h<block_h;h++){
			if (block_cur[h][w]==1){
				surface[cur_y+h][cur_x+w]=1;
			}
		}
	}	
}

void print_block(int block[][block_w], int x, int y){
	int w,h;
	for (w=0;w<block_w;w++){
		for (h=0;h<block_h;h++){
			if (block[h][w]==1){
				printxy("O", x+w, y+h);
			}
		}
	} 
}
void erase_block(int block[][block_w], int x, int y){
	int w,h;
	for (w=0;w<block_w;w++){
		for (h=0;h<block_h;h++){
			if (block[h][w]==1){
				printxy(" ", x+w, y+h);
			}
		}
	}
} 

int get_drop_y(){
	int drop_y = cur_y;
	while (isCollision(cur_x,drop_y+1)==0){
		drop_y++;
	}
	return drop_y;
}

void print_drop_guide(){
	int w,h;
	int drop_y = get_drop_y();
	if (drop_y==cur_y){
		return;
		
	}
	for (w=0;w<block_w;w++){
		for (h=0;h<block_h;h++){
			if (block_cur[h][w]==1){
				int px = cur_x+w;
				int py = drop_y+h;
				if (px>=0 && px<WIDTH && py>=0 && py<HEIGHT && surface[py][px]==0){
					printxy(".",px,py);
				}
			}
		}
	}
}

void erase_drop_guide(){
	int w,h;
	int drop_y = get_drop_y();
	if (drop_y==cur_y){
		return;
	}
	for (w=0;w<block_w;w++){
		for (h=0;h<block_h;h++){
			if (block_cur[h][w]==1){
				int px = cur_x+w;
				int py = drop_y+h;
				if (px>=0 && px<WIDTH && py>=0 && py<HEIGHT && surface[py][px]==0){
					printxy(" ",px,py);
				}
			}
		}
	}
}
void for_sleep(int max){
	int i = 0;
	for (i=0;i<max;i++){
	}
}

int isCollision(int x, int y){
	int w, h;
	for (h = 0; h < block_h; h++){
		for (w = 0; w < block_w; w++){
			if (block_cur[h][w] == 1){
				int cx = x + w;
				int cy = y + h;
				if (cx < 0 || cx >= WIDTH)  return 1;  // hit left or right wall
				if (cy < 0 || cy >= HEIGHT) return 1;  // hit top or bottom wall
				if (surface[cy][cx] == 1)   return 1;  // hit landed block
			}
		}
	}
	return 0;
}

int tm = 800; // falling interval in milliseconds
UINT_PTR timerId;

static void set_timer(int t) {
	KillTimer(NULL, timerId);
	timerId = SetTimer(NULL,0,t,NULL);
}
static void close_timer(){
	KillTimer(NULL, timerId);
}


int is_line_fill(int h){
	int w;
	for (w=0;w<WIDTH;w++) {
		if (surface[h][w]==0) {
			return 0;
		}
	}
	return 1;	
}

void clear_one_line(int h){
	int w, row;
	for (row = h ;row >1 ;row--){
		for (w=0;w<WIDTH;w++){
			surface[row][w]=surface[row-1][w];
		}
	}
	for (w=0;w<WIDTH;w++){
		surface[0][w]=0;
	}
}

void check_line(){
	int total_line = 0;
	int h;
	for (h = cur_y; h < HEIGHT; h++){
		if (is_line_fill(h)==1){
			clear_one_line(h);
			print_surface();
			total_line ++;
		}
	}
	
	score += total_line;
}
void move_block_down(){
	if (isCollision(cur_x,cur_y+1)==0){
		erase_drop_guide();
		erase_block(block_cur,cur_x,cur_y);
		cur_y++;
		print_drop_guide();
		print_block(block_cur,cur_x,cur_y);
	}
	else {
		erase_drop_guide();
		land_block();
		check_line();
		make_new_block();
		if (isCollision(cur_x,cur_y)==1){
			printf("score %d",score);
			close_timer();
		}
		print_drop_guide();
		print_block(block_cur,cur_x,cur_y);
	}

}

void hard_drop(){
	erase_drop_guide();
	erase_block(block_cur,cur_x,cur_y);

	while (isCollision(cur_x,cur_y+1)==0){
		cur_y++;
	}

	print_block(block_cur,cur_x,cur_y);
	land_block();
	check_line();
	make_new_block();
	if (isCollision(cur_x,cur_y)==1){
		printf("score %d",score);
		close_timer();
	}
	print_drop_guide();
	print_block(block_cur,cur_x,cur_y);
}

void key_control(){
	int ch;
	MSG msg;
	while(1){
		if (PeekMessage(&msg,NULL,WM_TIMER,WM_TIMER,PM_REMOVE)!=0){
			move_block_down();
		}
		
		if (kbhit()!=0){
			ch = getch();
			switch (ch){
				case 72: //up
						erase_drop_guide();
						erase_block(block_cur,cur_x,cur_y);
						rotate_block();
						if (isCollision(cur_x,cur_y)==1){
							rotate_block();
							rotate_block();
							rotate_block();
						}
						print_drop_guide();
						print_block(block_cur,cur_x,cur_y);
					break;
				case 80: //down
					if (isCollision(cur_x,cur_y+1)==0){
						erase_drop_guide();
						erase_block(block_cur,cur_x,cur_y);
						cur_y++;
						print_drop_guide();
						print_block(block_cur,cur_x,cur_y);
					}
					break;
				case 75: //left
					if (isCollision(cur_x-1,cur_y)==0){
						erase_drop_guide();
						erase_block(block_cur,cur_x,cur_y);
						cur_x--;
						print_drop_guide();
						print_block(block_cur,cur_x,cur_y);
					}
					break;
				case 77: //right
					if (isCollision(cur_x+1,cur_y)==0){
						erase_drop_guide();
						erase_block(block_cur,cur_x,cur_y);
						cur_x++;
						print_drop_guide();
						print_block(block_cur,cur_x,cur_y);
					}
					break;
				case 13: //enter
					hard_drop();
					break;
				case 113://q
					//printf("%d\n",ch);
					return;
					break;
				default:
					//printf("%d else\n",ch);
					break;
			}
		}
	}
}

int main()
{
	hand = GetStdHandle(STD_OUTPUT_HANDLE);
	setCursorVisable(0);
	//gotoxy(10,10);
	//printxy("O",10,10);
	
	srand(time(NULL));
	//copy_block(BlockJ,block_cur);
	print_surface();
	//print_block(BlockO, 0, 0);
	//for_sleep(INT_MAX);
	//Sleep(2000);
	//erase_block(BlockO, 0, 0);
	make_new_block();
	print_drop_guide();
	print_block(block_cur, cur_x, cur_y);
	set_timer(tm);
	key_control();
	system("pause");
	return 0;
}
