#include <string>
#include <iostream>
#include <vector>
#include <windows.h>


using namespace std; 

class square {
private:
	int x, y;
public: 
	void setYX(int ykoord, int xkoord) {
		y = ykoord;
		x = xkoord;
	}
	int get_X() {
		return x;
	}
	int get_Y() {
		return y;
	}
};


class figure {

private:
	bool onBaseline = true; 
	int colour;		//0 oder 1 weiﬂ oder schwarz
	char type;		//Rook1/2, Queen, King, Bishop1/2, Night1/2, pawn1-8
	int id; 
	float prob = 1;
	square sq;		//feld auf dem die Figur sitzt
	vector<figure*>crossing; //verschr‰nk. 


public:

	figure(int col, char t, square s, int i) {
		colour = col;
		type = t;
		sq = s;
		id = i; 
	}
	int getColour() {
		return colour;
	}
	char getType() {
		return type;
	}
	float getProb() {
		return prob;
	}
	
	void makeMove(figure * field[8][8], square s2) {

		//Todo wahrscheinlichkeiten bei superposition/verschr‰nkungen 


		vector<square> moves = getPosibleMoves();
		//bisher nur bewegung der figur fig von einem feld f1 nach f2
		sq = s2;

		//oder 2 moegl. 
		//field[sq.x][sq.y] = ; //abfrage nob move gemacht werden kann --> move im feld eintragen 

	}

	vector<square> getPosibleMoves() {

		vector<square>posMoves;
		switch (type) {
		
		case 'p':
			square s;
			if (onBaseline) {

				s.setYX(sq.get_Y()+1, sq.get_X());
				posMoves.push_back(s);
				s.setYX(sq.get_Y()+2, sq.get_X());
				posMoves.push_back(s);
			}
			else {
				s.setYX(sq.get_Y()+1, sq.get_X());
			}break; 
		}


		return posMoves; 
	}

	void merge(figure * fig2) {

	}

	void split(figure* field[8][8], square sq2_1, square sq2_2) {
		prob = prob / 2;	//halbiert die wahrscheinlichkeit der aktuellen figur
		figure newFig = *this;	//kopiere die aktuelle figur
		figure newFig_2 = *this;	//kopiere die aktuelle figur
		newFig.makeMove(field, sq2_1);	//bewege die neue figur auf das erste ziel
		newFig_2.makeMove(field, sq2_2);	//bewege die neue figur auf das zweite ziel


		field[sq2_1.get_Y()][sq2_1.get_X()] = &newFig; 
		field[sq2_2.get_Y()][sq2_2.get_X()] = &newFig_2;

	}
	
};

  
figure * field[8][8];	//2D-Array an pointern auf figuren


void initField() {

	square sq; 

	//Place white
	//Place Ponds
	for (int i = 0; i < 8; i++) {		
		sq.setYX(1,i);
		figure fig(0, 'p', sq, i);
		field[sq.get_Y()][sq.get_X()] = &fig;
	}
	//Place Rooks
	sq.setYX(0, 0);
	figure fig(0, 'r', sq, 0);
	field[sq.get_Y()][sq.get_X()];
	sq.setYX(0, 7);
	figure fig = figure(0, 'r', sq, 1);
	field[sq.get_Y()][sq.get_X()];

	//Place Knights
	sq.setYX(0, 1);
	figure fig(0, 'k', sq, 0);
	field[sq.get_Y()][sq.get_X()];
	sq.setYX(0, 6);
	figure fig(0, 'k', sq, 1);
	field[sq.get_Y()][sq.get_X()];

	//Place Bishops
	sq.setYX(0, 2);
	figure fig(0, 'b', sq, 0);
	field[sq.get_Y()][sq.get_X()];
	sq.setYX(0, 5);
	figure fig(0, 'b', sq, 1);
	field[sq.get_Y()][sq.get_X()];

	//Place king and queen
	sq.setYX(0, 4);
	figure fig(0, 'K', sq, 0);
	field[sq.get_Y()][sq.get_X()];
	sq.setYX(0, 3);
	figure fig(0, 'Q', sq, 0);
	field[sq.get_Y()][sq.get_X()];

	//--------

	//place black
	//Place Ponds
	for (int i = 0; i < 8; i++) {
		sq.setYX(6, i);
		figure fig(1, 'p', sq, i);
		field[sq.get_Y()][sq.get_X()] = &fig;
	}

	//Place Rooks
	sq.setYX(7, 0);
	figure fig(1, 'r', sq, 0);
	field[sq.get_Y()][sq.get_X()];
	sq.setYX(7, 7);
	figure fig(1, 'r', sq, 1);
	field[sq.get_Y()][sq.get_X()];

	//Place Knights
	sq.setYX(7, 1);
	figure fig(1, 'k', sq, 0);
	field[sq.get_Y()][sq.get_X()];
	sq.setYX(7, 6);
	figure fig(1, 'k', sq, 1);
	field[sq.get_Y()][sq.get_X()];

	//Place Bishops 
	sq.setYX(7, 2);
	figure fig(1, 'b', sq, 0);
	field[sq.get_Y()][sq.get_X()];
	sq.setYX(7, 5);
	figure fig(1, 'b', sq, 1);
	field[sq.get_Y()][sq.get_X()];

	//Place king and queen  
	sq.setYX(7, 4);
	figure fig(1, 'K', sq, 0);
	field[sq.get_Y()][sq.get_X()];
	sq.setYX(7, 3);
	figure fig(1, 'Q', sq, 1);
	field[sq.get_Y()][sq.get_X()];
	
}

int main() {
	initField();
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			cout << " | " << field[r][c] << endl;
		}

	}
	
}









