#include <string>
#include <iostream>
#include <vector>
#include <windows.h>


using namespace std; 

enum class Color { WHITE, BLACK };

struct Square {
	int y;
	int x;
	
};

class Figure {

private:
	bool onBaseline = true; 
	Color color;		
	char type;		
	int id;					//Rook1/2, Queen, King, Bishop1/2, Night1/2, pawn1-8
	float prob = 1;
	Square placedOn;				//feld auf dem die Figur sitzt
	vector<Figure*> correlations;	//verschränkung  


public:

	Figure(Color col, char t, Square s, int i) {
		color = col;
		type = t;
		placedOn = s;
		id = i; 
	}
	Color getColor() {
		return color;
	}
	char getType() {
		return type;
	}
	float getProb() {
		return prob;
	}
	
	void makeMove(Figure * field[8][8], Square s2) {

		//Todo wahrscheinlichkeiten bei superposition/verschränkungen 
		// 
		//oder 2 moegl. 
		//field[sq.x][sq.y] = ; //abfrage nob move gemacht werden kann --> move im feld eintragen 

	}
		
	/*vector<Square> getPosibleMoves(Board& board) {

		vector<Square>posMoves;
		Square pos; 

		int dirs[4][2] = {
			{1,0},{-1,0},
			{0,1},{0,-1} };

		switch (type) {
		case 'p':
			
			int dir = (color == Color::WHITE ? -1 : 1 ); //Richtungsangabe: Weis nach oben, Schwarz nach unten
			int x = placedOn.x;
			int y = placedOn.y; 

			Square s;	//{y,x}
			
			if (onBaseline) {
				s = { placedOn.y + dir, placedOn.x };
				if (board.getXY(s.x, s.y) == nullptr) {
					posMoves.push_back(s);
				}
				s = { placedOn.y + (2*dir), placedOn.x };
				if (board.getXY(s.x, s.y) == nullptr) {
					posMoves.push_back(s);
				}
				
			}
			else {
				s = { placedOn.y + dir, placedOn.x };
				if (board.isInside(s.y, s.x) && board.getXY(s.x, s.y) == nullptr) {
					posMoves.push_back(s);
				}




			}break; 
		case 'r':

			
		}
		return posMoves; 
	}*/

	void merge(Figure * fig2) {

	}

	void split() {
		

		

	}
	
};

class Board {
private:
	Figure* grid[8][8];

public:
	Board() {
		// Alles mit nullptr initialisieren
		for (int i = 0; i < 8; ++i)
			for (int j = 0; j < 8; ++j)
				grid[i][j] = nullptr;
	}

	~Board() {
		// Figuren löschen
		for (int i = 0; i < 8; ++i)
			for (int j = 0; j < 8; ++j)
				grid[i][j] = nullptr;
	}

	Figure* getXY(int x, int y) {
		return grid[y][x];
	}
	void setXY(int x, int y, Figure* f) {
		grid[y][x] = f;
	}
	void print() {
		cout << endl;
		for (int y = 0; y < 8; y++) {
			cout << 8 - y << " | ";
			for (int x = 0; x < 8; x++) {
				if (grid[y][x]) {
					cout << grid[y][x]->getType();
				}
				else {
					cout << ".";
				}
				cout << "|";

			}cout << endl;
		}
	}
	void init() {
		Square s;
		//Place Ponds 
		int y = 6;
		for (int x = 0; x < 8; x++) {
			s = { y,x }; 				//Aktueller square auf dem die figur sitzt wird figur selbst übergeben
			grid[y][x] = new Figure(Color::WHITE, 'p', s, x);//id 1->8
			s = { y - 5,x };
			grid[y-5][x] = new Figure(Color::BLACK, 'p', s, x);
		}
		//Place Rooks
		s = { 7,0 };
		grid[s.y][s.x] = new Figure(Color::WHITE, 'r', s, 1);
		s = { 7,7 };
		grid[s.y][s.x] = new Figure(Color::WHITE, 'r', s, 2);
		s = { 0,0 };
		grid[s.y][s.x] = new Figure(Color::BLACK, 'r', s, 1);
		s = { 0,7 };
		grid[s.y][s.x] = new Figure(Color::BLACK, 'r', s, 1);

		//Place Knights
		s = { 7,1 };
		grid[s.y][s.x] = new Figure(Color::WHITE, 'n', s, 1);
		s = { 7,6 };
		grid[s.y][s.x] = new Figure(Color::WHITE, 'n', s, 2);
		s = { 0,1 };
		grid[s.y][s.x] = new Figure(Color::BLACK, 'n', s, 1);
		s = { 0,6 };
		grid[s.y][s.x] = new Figure(Color::BLACK, 'n', s, 2);
	

	//Place Bishops, Queens, Kings can be added similarly
		s = { 7,2 };
		grid[s.y][s.x] = new Figure(Color::WHITE, 'b', s, 1);
		s = { 7,5 };
		grid[s.y][s.x] = new Figure(Color::WHITE, 'b', s, 2);
		s = { 0,2 };
		grid[s.y][s.x] = new Figure(Color::BLACK, 'b', s, 1);
		s = { 0,5 };
		grid[s.y][s.x] = new Figure(Color::BLACK, 'b', s, 2);

		s = { 7,3 };
		grid[s.y][s.x] = new Figure(Color::WHITE, 'q', s, 1);
		s = { 0,3 };
		grid[s.y][s.x] = new Figure(Color::BLACK, 'q', s, 1);

		s = { 7,4 };
		grid[s.y][s.x] = new Figure(Color::WHITE, 'k', s, 1);
		s = { 0,4 };
		grid[s.y][s.x] = new Figure(Color::BLACK, 'k', s, 1);


	}
	bool isInside(int y, int x) {
		return(y >= 0 && y < 8 && x >= 0 && x < 8);		//prüft ob koordinaten auf Feld liegen
	}
};



 

int main() {
	Board GameBoard; 

	GameBoard.init();
	GameBoard.print();
	
	return 0; 
}









