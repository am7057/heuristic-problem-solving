#include <iostream>
#include <utility>
#include <vector>
using namespace std;

#define NUM_POSITIONS 51
#define F1 (-3+25)
#define F2 (-1+25)
#define MAX_WEIGHT 15
#define MIN_WEIGHT 1

class solution {
private:
	bool alreadyput[MAX_WEIGHT+MIN_WEIGHT];//indicates whether weights MIN_WEIGHT to MAX_WEIGHT have been played

public:
	solution() {
		for (int w = MIN_WEIGHT; w <= MAX_WEIGHT; ++w)
			alreadyput[w] = false;
	}

	//returns pair<int,int>(w,position), where w is to be placed at board[position]
	virtual pair<int,int> putphaseMove(int* board) = 0;
	
	//returns 
	virtual int takephaseMove(int* board) = 0;
	
	bool isTipped(int*board) {
		int torque1 = 9;//needs to be negative for tipping
		int torque2 = 3;//needs to be positive for tipping
		for (int i = 0; i < NUM_POSITIONS; ++i) {
			torque1 += board[i] * (i - F1);
			torque2 += board[i] * (i - F2);
		}
		return torque1 < 0 || torque2 > 0;
	}

	void put(int w) { alreadyput[w] = true; }

	bool alreadyPut(int w) { return alreadyput[w]; }
};

class firstfit_strategy : solution {
public:
	firstfit_strategy() : solution() {}
	pair<int,int> putphaseMove(int* board) {
		//find valid move that won't lose immediately
		pair<int, int> backupMove;
		for (int p = 0; p < NUM_POSITIONS; ++p) {
			if (board[p] == 0) {
				for (int w = MIN_WEIGHT; w <= MAX_WEIGHT; ++w) {
					if (!alreadyPut(w)) {
						backupMove.first = w;
						backupMove.second = p;
						board[p] = w;
						if (!isTipped(board)) {
							put(w);
							return pair<int, int>(w, p);
						}
						board[p] = 0;
					}
				}
			}
		}
		//can't find one, so you lose; just return a valid move
		return backupMove;
	}

	int takephaseMove(int* board) {
		int backupPosition;
		//search for valid move that won't immediately lose
		for (int p = 0; p < NUM_POSITIONS; ++p)
			if (board[p] > 0) {
				backupPosition = p;
				int temp = board[p];
				board[p] = 0;
				if (!isTipped(board))
					return p;
				board[p] = temp;
			}
		//can't find one, so you lose; return a valid move
		return backupPosition;
	}
};

int main() {
	int putphaseInt;
	int gameoverInt;
	int board[NUM_POSITIONS];

	//connect to server

	while (true) {
		while (true/*waiting for data*/)
			/*get data*/;
		//set putphaseInt, gameoverInt, board
		bool putphase = putphaseInt == 1;
		bool gameover = gameoverInt;
		
		
	}
}
