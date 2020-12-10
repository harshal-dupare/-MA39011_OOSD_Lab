/*
Name : Harshal Bharat Dupare
Roll Number : 18MA20015
Class : 3
Date : 18-9-2020
Topic : Tic Tac Toe
Specifications : The game must conclude when a player wins, or all the cells are filled if it is a draw. 
After the conclusion of a game the program should ask the user whether he wants to play another game or not, and proceed accordingly.

Note: The code handels all the edge cases of users inputs, even if user gives wrong input the code handels it by asking user to give the correct input
*/

#define N 3

#include <iostream>

using namespace std;

// a global 2D-array as board
int board[N][N];

/***Start of Utility functions***/

// function to display the board
void show_board()
{
	cout<<"Game State Is:"<<endl;
	// goes through cell and prints it accordingly
	for(int i=0;i<N;i++)
	{
		cout<<"-------\n";
		for(int j=0;j<N;j++)
		{
			cout<<"|";
			if(board[i][j]==1) cout<<"O";// 1 is 2nd player so print O
			else if (board[i][j]==0) cout<<"X";// 0 is 1st player so print X
			else cout<<" ";// if none then print empty cell
		}
		cout<<"|"<<endl;
	}
	cout<<"-------\n";
}

// Asks human player for his preference and returns it
int get_player_preference()
{
	int which_player=0;
	cout<<"Which player you want to play as?\n| 0 : 1st Player | 1 : 2nd Player | "<<endl;

	// loops till the player gives right preference
	while(true)
	{
		cin>>which_player;
		// if correct input is given just returns the input
		if(which_player==0||which_player==1) return which_player;

		// if player makes error then it informs the player and ask to give input again
		cout<<"Give correct input, either 0 or 1"<<endl;
	}
}

/***End of Utility functions***/

// checks if the 'tplayer' has won the game or not in the given position of the board a[N][N]
// returns 1 if player has won else 0
int do_i_won(int tplayer,int a[N][N])
{
	// loop to check along each row if all the cells are filled by the player or not, if yes then the player has won
	// if the player has won then it returns 1
	for(int i=0;i<N;i++)
	{
		int can=1;
		for(int j=0;j<N;j++)
		{
			if(a[i][j]!=tplayer)
			{
				can=0;
				break;
			}
		}

		if(can==1) return 1;
	}

	// loop to check along each column if all the cells are filled by the player or not, if yes then the player has won
	for(int i=0;i<N;i++)
	{
		int can=1;
		for(int j=0;j<N;j++)
		{
			if(a[j][i]!=tplayer)
			{
				can=0;
				break;
			}
		}

		if(can==1) return 1;
	}

	// loop which checks if the player has won on any diagonal
	bool diag1=1,diag2=1; // start with assuming that the player has won
	for(int i=0;i<N;i++)
	{
		// if on any diagonal cell there isnt the tplayers move then he cant win on that diagonal hence make that diag to 0
		if(a[i][i]!=tplayer) diag1=0;
		if(a[i][N-1-i]!=tplayer) diag2=0;
	}

	// returns the max of diag1 and diag2 as if player has won on any of the diagonal then he won
	return max(diag1,diag2);
}

// returns 1 if tplayer can win, -1 if tplayer always looses, 0 if tplayer can draw form the board position a[][]
int can_win(int tplayer,int a[N][N])
{

	if(do_i_won(1-tplayer,a)) return -1; // if other player has already won then we have lost, hence return -1
	if(do_i_won(tplayer,a)) return 1;    // if we have already won then return 1

	// to store the count of movie types, draw stores count of drawing moves and same goes for win
	// count stores the total number of moves that we can make
	int draw=0,win=0,count=0;
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			if(a[i][j]!=1 && a[i][j]!=0)
			{
				a[i][j]=tplayer;

				// checks if we play this move [i][j] then can the other palyer win or not
				int k=can_win(1-tplayer,a);

				// undo the move as to not affect the original board
				a[i][j]=-1;

				// increment the move types count accordingly 
				if(k==0) draw++;

				if(k==1) win++;

				count++;

				// if other player loses by playing this then we can win by this move, hence return 1 
				if(k==-1) return 1;
			}
		}
	}

	// if there are no moves to play then its draw, hence return 0
	if(count==0)return 0;

	// if whatever we play the other player can win then we have lost
	if(win==count)return -1;

	// if none of the above then it is a draw
	return 0;
}

void human_move(int hplayer)
{
	// askes for human player's input
	cout<<"Enter the cell number where you want to play your next move \nRange 1-"<<N*N<<" and cannot place move on already filled cell\n";
	int temp;

	// takes input till proper input is given
	while(true)
	{
		cin>>temp;

		// if input is not in the range of cells inform so
		if(temp>N*N || temp<=0)
		{
			cout<<"Please enter a valid input in the proper range 1-"<<N*N<<endl;
			continue;
		}

		// converting the input number to the cell index [i][j]
		temp--;
		int i=temp/N;
		int j=temp%N;

		// checks if the move is already done or not, if done then inform so ans ask for other number move
		if(board[i][j]==0||board[i][j]==1)
		{
			cout<<"Please enter a valid input which is not already used"<<endl;
			continue;
		}

		// update the board accordingly
		board[i][j]=hplayer;
		return;
	}
}

/*

Logic  Used : We check for all moves that we can make and see if we can win ( or draw atleast ) by making any move
			  if such move is found then we play that move. 
			  For each checking each move, we make that move and look ahead all the moves that can be played and see if we win or loose
			  if we win then we play that move else we find for draw moves

Note : if there is a situations where any move leads to winning of the computer, then it plays the move that maximizes the ways to win the game.
		Meaning if there is a next move which make the computer win and there is a move which makes the computer win in more ways then it plays the 2nd move
		i.e. this algorithm is NOT a greedy algorithm, it is FORWARD LOOKING algorithm and checks all possible games and chooses the one which maximizes the ways to win

*/
// computer move
void computer_move(int cplayer)
{

	// to store a move which leads to winning or drawing
	int winis=-1,drawis=-1;

	// to store the count of movie types, draw stores count of drawing moves and same goes for win
	// count stores the total number of moves that we can make
	int winct=0,drawct=0,count=0;

	// loop which goes through the board and find an empty position and checks if we can win by that more or not
	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			if(board[i][j]!=1 && board[i][j]!=0)
			{
				// play the move and check if opponent can win or not
				board[i][j]=cplayer;
				int k=can_win(1-cplayer,board);

				// undo the move
				board[i][j]=-1;

				// if opponent looses by playing this move then play this move
				if(k==-1)
				{
					board[i][j]=cplayer;
					return;
				}

				// store the location of draw and win and its count
				if(k==0){drawis=N*i+j;drawct++;}
				if(k==1){winis=N*i+j;winct++;}

				// add 1 to the total moves count
				count++;
			}
		}
	}

	// if opponent always wins the game then we can never win the game, hence play the last checked move / or any move
	if(winct==count)
	{
		int i=winis/N;
		int j=winis%N;
		board[i][j]=cplayer;
		return;
	}

	// if there is a way to draw then play that move
	int i=drawis/N;
	int j=drawis%N;
	board[i][j]=cplayer;
	//update_winnning_moves(cplayer,move);
	return;

}


int main()
{

// loop for playing more than 1 game
while(true)
{
	// filling the board array with -1 to represent empty location
	for(int i=0;i<N;i++)for(int j=0;j<N;j++) board[i][j]=-1;

	// which player does the human wants to play as , 0 meaning 1st player ('X') 1 meaning 2nd player ('O')
	int which_player=0;

	// how many moves have completed
	int move_count=0;

	// default players numbers as in default human goes 1st so hplayer = 0, which stands for human player, hence cplayer=1
	int hplayer=0, cplayer=1;

	// get the preference of the human player
	which_player=get_player_preference();

	// if human chooses player other than default palyer
	if(which_player==1)
	{
		// changing the values accordingly
		hplayer=1;
		cplayer=0;

		// as now computer is the 1st player, it plays the move
		computer_move(cplayer);
		// as one move is played count is increased
		move_count++;
	}

	// prints the board
	show_board();

	// main loop runs till no move can be played or someone wins
	while(move_count<N*N)
	{
		// if the next trun is of human player or of computer
		if(move_count%2 == which_player) human_move(hplayer); // ask for the human to play move
		else computer_move(cplayer); 						  // computer plays its move

		// prints the board
		show_board();

		// to check if any of human or computer has won and if yes then print so and exit the game
		if(do_i_won(hplayer,board))
		{
			if(hplayer==0) cout<<"Human Player 'X' has won the game"<<endl; 

			if(hplayer==1)cout<<"Human Player 'O' has won the game"<<endl; 

			break;
		}
		if(do_i_won(cplayer,board))
		{
			if(cplayer==0)cout<<"Computer Player 'X' has won the game"<<endl; 

			if(cplayer==1) cout<<"Computer Player 'O' has won the game"<<endl; 

			break;
		}

		// as move is played count is increased
		move_count++;

	}

	// if nobody won the game then all cells are full and so prints that it was a draw
	if(move_count==N*N) cout<<"It was a draw game"<<endl; 

	// asks player if want to play another game if yes then starts again else
	while(true)
	{
		// asks player if want to play again 
		cout<<"Do you want to play another game? ( 1: Yes , 0: NO ) : ";
		int temp;
		cin>>temp;
		if(temp==0)return 0;

		if(temp==1)break;

		cout<<"Please give proper input!"<<endl;
	}
}

return 0;
}
