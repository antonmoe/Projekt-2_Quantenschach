#include <string>
#include <iostream>
#include <vector>
#include <windows.h>


figure field[8][8];

struct square {
	int y, x;
};



class figure {

private:
	int tmp;
	string name;
	float prob;
	square sq;



public:

	void makeMove(figure fig, square s1, square s2) {
		//Todo wahrscheinlichkeiten bei superposition/verschränkungen 


		//bisher nur bewegung der figur fig von einem feld f1 nach f2
		fig.sq = s2;	
		//oder 2 moegl. 
		field[sq.x][sq.y] = fig; //abfrage nob move gemacht werden kann --> move im feld eintragen 

		//habe das gefühl es macht mehr sinn diese funktionen in des klasse figure aufzurufen als im feld 


	}

	void



};






