#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

char checkwinner(vector<vector<char> > &board){
	for(int i = 0; i < board.size(); i++){
		if(board[i][0] != ' ' && (board[i][0] ==  board[i][1] && board[i][1] ==  board[i][2] ) ){
			if(board[i][0] == 'O'){
				return 'O';
			}
			else{
				return 'X';
			}
		}
		if(board[0][i] != ' ' && (board[0][i] == board[1][i] && board[1][i] ==  board[2][i])){
			if(board[0][i] == 'O'){
				return 'O';
			}
			else{
				return 'X';
			}
		}
	
		
	}
		if(board[0][0] != ' ' && (board[0][0] ==  board[1][1]  && board[1][1] ==  board[2][2] )){
			if(board[0][0] == 'O') return 'O';
			else return 'X';
		}
		
		if(board[0][2] != ' ' && (board[0][2] ==   board[1][1] && board[1][1]  ==  board[2][0] )){
			if(board[0][2] == 'O') return 'O';
			else return 'X';
		}
		return ' ';
}

bool checkgameover(vector<vector<char> >&board){
	for(int i = 0; i < board.size(); i++){
		for(int j = 0; j < board.size(); j++){
			if(board[i][j] == ' ') return false;
		
		}
	}
	return true;
}

int minimax(vector<vector<char> > &board,bool ismaximizing,int alpha, int beta,int depth){
	char winner = checkwinner(board);
	if(winner == 'O') return 10 - depth;
	if(winner == 'X') return depth - 10;
	if(checkgameover(board)) return 0;
	
	
	if(ismaximizing){
	int maxi = -9999999;
	for(int i = 0; i < board.size(); i++){
		for(int j = 0; j < board.size(); j++){
			if(board[i][j] == ' '){
				board[i][j] = 'O';
				int max_score = minimax(board,false,alpha,beta,depth+1);
				board[i][j] = ' ';
				if(max_score > maxi){
					maxi = max_score;
				}
                alpha = max(alpha,maxi);
                if(alpha >= beta) return maxi;
                
			}
		}
	}
	return maxi;
}
else{
	int mini = 9999999;
	for(int i = 0; i < board.size(); i++){
		for(int j = 0; j < board.size(); j++){
			if(board[i][j] == ' '){
				board[i][j] = 'X';
				int mini_score = minimax(board,true,alpha,beta,depth+1);
				board[i][j] = ' ';
				if(mini_score < mini){
					mini = mini_score;
				}
                beta = min(beta,mini);
                if(alpha >= beta) return mini;
                
			}
		}
	}
	return mini;
}
	
	
}

void printBoard(vector<vector<char> > &board){
	for(int i = 0; i < board.size(); i++){
		for(int j = 0; j < board.size(); j++){
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

pair<int,int> bestmove(vector<vector<char> > &board){
	pair<int,int> currbestmove = {-1,-1};
	int score = -9999999;
	for(int i = 0; i < board.size(); i++ ){
		for(int j = 0; j < board.size(); j++){
			if(board[i][j] == ' '){
				board[i][j] = 'O';
				int curr_score = minimax(board,false,-9999999,9999999,0);
				board[i][j] = ' ';
				if(curr_score > score){
					score = curr_score;
					currbestmove = {i,j};
				}
			}
		}
	}
	return currbestmove;
}

int main(){
	vector<vector<char> > board(3,vector<char>(3,' '));
	cout << " AI = O " << endl;
	cout << "Player = X" << endl;
	while(!checkgameover(board) && checkwinner(board) == ' '){
		cout << "AI turn" << endl;
		pair<int,int> ai_move = bestmove(board);
		board[ai_move.first][ai_move.second] = 'O';
		printBoard(board);
        if(checkwinner(board) != ' ' || checkgameover(board)) break;
		cout << "Player's turn " << endl;
		int x, y;
		cin >> x >> y;
		board[x][y] = 'X';
		printBoard(board);
		
		 
	}
	cout << "Game over!" << endl;
	char winner = checkwinner(board);
	if(winner == 'X'){
		cout << "Player wins!" << endl;
	}
	else if(winner == 'O'){
		cout << "AI wins!" << endl;
	}
	else{
		cout << "Draw!" << endl;
	}
}
