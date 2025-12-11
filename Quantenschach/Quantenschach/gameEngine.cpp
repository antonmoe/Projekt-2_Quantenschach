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
	
};



vector<Square> getPossibleMoves(Board& board, Square sq) {

	vector<Square>posMoves;

	Figure* fig = board.getXY(sq.x, sq.y);					//ausgewählte figur welche den zug macht

	auto inside = [&](int x, int y) {						//Lambda ausdrücke ...
		return (x >= 0 && x < 8 && y >= 0 && y < 8);
		};

	auto empty = [&](int x, int y) {
		return inside(x, y) &&
			board.getXY(x, y) == nullptr;
		};

	auto enemySquare = [&](int x, int y) {
		return inside(x, y) &&									
			board.getXY(x, y) != nullptr &&						
			board.getXY(x, y)->getColor() != fig->getColor();	
		};

	int dir = (fig->getColor() == Color::WHITE ? -1 : 1); //Richtungsangabe: Weis nach oben, Schwarz nach unten

	switch (fig->getType()) {
	case 'p':
	{
		Square s;	//{y,x}
		int dirs[4][2] = {	//{y,x}
			{dir,0},{2 * dir,0},	//vor, vor2
			{dir,-1},{dir,1}	//schlag links, schlag rechts
		};
		int ny = sq.y;
		int nx = sq.x;

		//Auf Grundlinie
		if ((fig->getColor() == Color::WHITE && sq.y == 6) ||
			(fig->getColor() == Color::BLACK && sq.y == 1)) {//eig nicht richtig, änderungsbedarf, sobald bauer auf grundlinie steht

			nx = sq.x + dirs[0][1]; //vor
			ny = sq.y + dirs[0][0];
			if (inside(nx, ny) && board.getXY(nx, ny) == nullptr)
				posMoves.push_back({ ny,nx });

			nx = sq.x + dirs[1][1];	//vor2
			ny = sq.y + dirs[1][0];
			if (inside(nx, ny) && board.getXY(nx, ny) == nullptr)
				posMoves.push_back({ ny,nx });

		}
		else {
			nx = sq.x + dirs[0][1]; //vor
			ny = sq.y + dirs[0][0];
			if (inside(nx, ny) && board.getXY(nx, ny) == nullptr)
				posMoves.push_back({ ny,nx });
		}

		//wenn bauer schlagen kann, bisher ohne en passat
		if (board.getXY(sq.x + 1, sq.y + dir) != nullptr
			&& board.getXY(sq.x + 1, sq.y + dir)->getColor() != fig->getColor()) {
			nx = sq.x + dirs[3][1];	//rechts Schlagen
			ny = sq.y + dirs[3][0];
			if (inside(nx, ny) && board.getXY(nx, ny) == nullptr)
				posMoves.push_back({ ny,nx });
		}
		if (board.getXY(sq.x - 1, sq.y + dir) != nullptr
			&& board.getXY(sq.x - 1, sq.y + dir)->getColor() != fig->getColor())
		{
			nx = sq.x + dirs[2][1];	//rechts Schlagen
			ny = sq.y + dirs[2][0];
			if (inside(nx, ny))
				posMoves.push_back({ ny,nx });
		}
		break;
	}

	case 'r':
	{
		int dirs[4][2] = {	//{y,x}
			{-1,0},{1,0},
			{0,-1},{0,1}
		};

		for (auto& d : dirs) {
			int ny = sq.y + d[0];
			int nx = sq.x + d[1];
			while (inside(nx, ny)) {
				cout << "ny: " << ny << " nx: " << nx << endl;
				if (empty(nx, ny)) posMoves.push_back({ ny,nx });
				else if (enemySquare(nx, ny)) {
					posMoves.push_back({ ny,nx });
					break;
				}
				else break;
				ny += d[0];
				nx += d[1];
			}

		}
		break;
	}

	
	case 'b':
	{
		int dirs[4][2] = {	//{y,x}
			{-1,-1},{-1,1},
			{1,-1},{1,1}
		};


		for (auto& d : dirs) {
			int ny = sq.y + d[0];
			int nx = sq.x + d[1];

			while (inside(nx, ny)) {
				if (empty(nx, ny)) posMoves.push_back({ ny,nx });	//Feld frei
				else if (enemySquare(nx, ny)) {						//Feld = Gegner(kann geschlagen werden)
					posMoves.push_back({ ny, nx });
					break;
				}
				else break;											//Feld = eigene Figur
				ny += d[0];
				nx += d[1];
			}
		}
		break;
	}
	
	case 'n':{
		int dirs[8][2] = {	//{y,x}
			{2,1}, {2,-1},
			{-2,1},{-2,-1},
			{1,2}, {1,-2},
			{-1,2},{-1,-2}
		};

		for (auto& d : dirs) {
			int ny = sq.y + d[0];
			int nx = sq.x + d[1]; 

			if (inside(nx, ny) && (empty(nx, ny) || enemySquare(nx, ny))) {
				posMoves.push_back({ny,nx});
			}
		}	

		break;
	}

	case 'q': {
		
		int dirs[8][2] = {
			{-1,-1},{-1,0},	{-1,1},
			{0,-1},			{0,1},
			{1,-1},	{1,0},	{1,-1}
		};

		for (auto& d : dirs) {
			int ny = sq.y + d[0];
			int nx = sq.x + d[1];

			while (inside(nx, ny)) {
				if (empty(nx, ny))
					posMoves.push_back({ ny,nx });
				else if (enemySquare(nx, ny)) {
					posMoves.push_back({ ny,nx });
					break;
				}
				else break; 
				ny += d[0];
				nx += d[1];

			}
		}

		break; 
	}

	case 'k': {

		int dirs [8][2] = {
			{-1,-1},{-1,0},{-1,1},
			{0,-1}, {0,1},
			{1,-1}, {1,0},{1,1}
		};

		for (auto& d : dirs) {
			int ny = sq.y + d[0];
			int nx = sq.x + d[1];

			if(inside(nx,ny) && (empty(nx,ny) || enemySquare(nx,ny))){
				posMoves.push_back({ ny,nx });
			}
		}

		break;
	}
	
	default: 
		break;
}
	
	return posMoves;
}

int main() {
	Board GameBoard; 

	GameBoard.init();

	GameBoard.setXY(3, 3, new Figure(Color::WHITE, 'b', { 3,3 }, 3));
	GameBoard.setXY(5, 3, new Figure(Color::WHITE, 'q', { 3,5 }, 3));
	GameBoard.print();
	vector<Square> moves;
	moves = getPossibleMoves(GameBoard, { 6,0 });
	cout << "Possible Moves for Pawn at a2: " << endl;
	for (auto& m : moves) {
		cout << char('a' + m.x) << (8 - m.y) << " ";
	}
	moves = getPossibleMoves(GameBoard, { 3,3 });	//Struct = {y,x} 
	cout << endl << "Possible Moves for "<< GameBoard.getXY(3,3)->getType()<<" at: "<< char('a'+3) << (8-3) << endl;
	for (auto& m :moves ) {
		cout << char('a' + m.x) << (8 - m.y) << " ";
	}

	moves = getPossibleMoves(GameBoard, { 3,5 });	
	cout << endl << "Possible Moves for " << GameBoard.getXY(5, 3)->getType() << " at: " << char('a' + 3) << (8 - 5) << endl;
	for (auto& m : moves) {
		cout << char('a' + m.x) << (8 - m.y) << " ";
	}

	
	return 0; 
}









