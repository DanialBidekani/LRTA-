// this program is written by danial bidekani
// and show you how LRTA* works
// it use a heuristic called Manhattan heuristic

#include <iostream>
#include <limits>
#include <cstdlib>
using namespace std;

void fillBoard(int**, int, int, int*, int*, int*, int*);
void printBoard(int**, int, int);
void LRTA(int**, int, int, int, int, int, int);

int main()
{
	bool cond = false;
	int **board; //board that robot live in it
	int columns, rows; // rows and columns of board
	int robotPositionX, robotPositionY; //position of robot
	int batteryPositionX, batteryPostionY; //position of battery

	// control user to enter the right info
	do
	{
		cond = true;
		cout<<"Enter Number Of Rows And Columns: \n";
		cin>>rows>>columns;

		if(cin.fail())
		{
			cin.clear();
			cin.ignore();
			cerr<<"ENTER AN INTEGER ONLY.\n";
			cond = false;
		}
	}while(!cond);



	//allocate the board
	board = new int* [rows];
	for(int row=0; row < rows; row++)
		board[row] = new int[columns];



	// call fillBoard Function
	fillBoard(board, rows, columns, &robotPositionX, &robotPositionY,
			&batteryPositionX, &batteryPostionY);

	// call printBoard Function Before LRTA Star
	printBoard(board, rows, columns);

	// call LRTA Function
	LRTA(board, robotPositionX, robotPositionY,
			batteryPositionX, batteryPostionY, rows, columns);

	// call printBoard After LRTA Star
	cout<<endl<<"- - - -\nAfter LRTA* ";
	printBoard(board, rows, columns);
}


//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--->>>FillBoard Method
void fillBoard(int **board, int rowSize, int columnSize, int *rx, int *ry,
		int *bx, int *by)
{
	char entity;
	cout<<"Enter B For Battery Situation\nR For Robot Situation\n"
			"O For Obstacle\nE For Empty Rooms"<<endl;
	for(int row=0; row < rowSize; row++)
		for(int col=0; col < columnSize; col++)
		{

			cout<<"Enter ["<<row<<"]"<<"["<<col<<"]: ";
			cin>>entity;

			if(entity == 'E')
			{
				board[row][col] = 0;
			}
			else if(entity == 'R')
			{
				board[row][col] = 0;
				*rx = row;
				*ry = col;
			}
			else if(entity == 'B')
			{
				board[row][col] = 0;
				*bx = row;
				*by = col;
			}
			else if(entity == 'O')
			{
				board[row][col] = -1;
			}
			else
			{
				cerr<<"YOU ENTER THE WRONG CHARACTER\n";
				exit(1);
			}
		}
}
//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--->>>Print Method
void printBoard(int **board, int rowSize, int columnSize)
{
	cout<<"Board Values:\n";
	for(int row=0; row < rowSize; row++)
	{
		for(int col=0; col<columnSize; col++)
		{
			if(board[row][col] == -1)
				cout<<"#"<<"\t";
			else
				cout<<board[row][col]<<"\t";
		}

		cout<<endl;
	}
}

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--->>>LRTA Method
void LRTA(int **board, int rpx, int rpy, int bpx, int bpy, int rows, int cols)
{
	int temp;

	int robotFirstX = rpx;
	int robotFirstY = rpy;

	int x_distance = abs(rpx-bpx);
	int y_distance = abs(rpy-bpy);

	char action; // it can be R-->Right, L-->Left, U-->Up, D-->Down
	cout<<endl<<"- - - -\n";
	cout<<"Path Solution Is: ";
	while(true)
	{
		temp = numeric_limits<int>::infinity();
		//------->>>move down
			rpx = rpx+1;
			if(rpx<rows && rpx <= robotFirstX + x_distance)
			{
				if(temp >= board[rpx][rpy] && board[rpx][rpy] != -1)
				{
					temp = board[rpx][rpy];
					action = 'D';
				}
			}
			rpx = rpx-1;

			//------->>>move up
			rpx = rpx-1;
			if(rpx>=0 && rpx >= robotFirstX - x_distance)
			{
				if(temp >= board[rpx][rpy] && board[rpx][rpy] != -1)
				{
					temp = board[rpx][rpy];
					action = 'U';
				}
			}
			rpx = rpx+1;

			//------->>>move to right

			rpy = rpy+1;
			if(rpy<cols && rpy <= robotFirstY + y_distance)
			{
				if(temp >= board[rpx][rpy] && board[rpx][rpy] != -1)
				{
					temp = board[rpx][rpy];
					action = 'R';
				}
			}
			rpy = rpy-1;



			//------->>>move to left
			rpy = rpy-1;
			if(rpy>=0 && rpy >= robotFirstY - y_distance)
			{
				if(temp >= board[rpx][rpy] && board[rpx][rpy] != -1)
				{
					temp = board[rpx][rpy];
					action = 'L';
				}
			}
			rpy = rpy+1;



			// move robot to new room
			if(action == 'R')
			{
				board[rpx][rpy] = temp+1;
				rpy = rpy+1;
				cout<<"R";
			}
			else if(action == 'L')
			{
				board[rpx][rpy] = temp+1;
				rpy = rpy-1;
				cout<<"L";
			}
			else if(action == 'U')
			{
				board[rpx][rpy] = temp+1;
				rpx = rpx-1;
				cout<<"U";
			}
			else if(action == 'D')
			{
				board[rpx][rpy] = temp+1;
				rpx = rpx+1;
				cout<<"D";
			}
			else
			{
				cout<<"NO SOLUTION!!!\n";
				break;
			}

			// if robot and battery are in the same room
			if(rpx == bpx && rpy == bpy)
			{
				break;
			}

	}//end while
}
