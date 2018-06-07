#include <iostream> // подключаем все необходимые инклюды.
#include <vector>
#include<time.h>

using namespace std;

#define N 5

struct point{
	int x; int y;
	point(int x, int y){
		this->x = x;
		this->y = y;
	}
};

class Matrix{
	char matrix[25][80];
public:
	Matrix(){
		for (int i = 0; i < 25; i++){
			for (int j = 0; j < 80; j++){
				matrix[i][j] = ' ';
			}
		}
	}

	char get_pixel(point p){
		return matrix[p.x][p.y];
	}
	void set_pixel(char c, point p){
		matrix[p.x][p.y] = c;
	}
	void cls(){
		for (int i = 0; i < 25; i++){
			for (int j = 0; j < 80; j++){
				matrix[i][j] = ' ';
			}
		}
		system("cls");
	}
	void print_matrix(){
		for (int i = 0; i < 12; i++){
			for (int j = 0; j < 80; j++){
				cout << matrix[i][j];
			}
			cout << endl;
		}
	}
};

class Card{
public:
	int value;
	bool is_showed_up;	
	static const int size_x = 4,size_y = 3;
	Card(){
		
		this->value = rand()%100;
		is_showed_up = false;
	}

};

class Game{
public:
	Matrix m;
	int money;
	static const int start_cost = 40;
	Card cards[N];
	void draw_card(point sp, Card c){
		m.set_pixel('+', point(sp.y, sp.x)); 
		m.set_pixel('+', point(sp.y + Card::size_y, sp.x)); 
		m.set_pixel('+', point(sp.y, sp.x + Card::size_x)); 
		m.set_pixel('+', point(sp.y + Card::size_y, sp.x + Card::size_x)); 

		m.set_pixel('|',  point(sp.y + 1, sp.x)); m.set_pixel('|',  point(sp.y + 2, sp.x));
		m.set_pixel('|',  point(sp.y + 1, sp.x + Card::size_x));m.set_pixel('|',  point(sp.y + 2, sp.x + Card::size_x));

		m.set_pixel('-',  point(sp.y, sp.x + 1)); m.set_pixel('-',  point(sp.y, sp.x + 2));
		m.set_pixel('-',  point(sp.y + Card::size_y, sp.x + 1)); m.set_pixel('-',  point(sp.y + Card::size_y, sp.x +2));
		
		if(c.is_showed_up){
			if (c.value / 10 == 0){
				m.set_pixel(c.value + '0', point(sp.y + 2, sp.x + 2));
			}
			else{
				m.set_pixel(c.value%10 + '0', point(sp.y + 2, sp.x + 2));
				m.set_pixel(c.value/10 + '0', point(sp.y + 1, sp.x + 2));
			}
		}
	}

	void gen_cards(){
		for (int i = 0; i < N; i++){
			cards[i] = Card();
		}
	}

	Game(){
		srand(time(NULL));
		money = 200;
		m = Matrix();
		gen_cards();
	}
	void draw_cards(){
		for (int i = 0; i < N; i++){
			draw_card(point(5 + i*8, 3), cards[i]);
		}
	}
};

int main(int argc, char **argv) // Главная функция
{
	Game gggame;
	while(true){
		gggame.gen_cards();
		for (int i = 0; i < N; i++){
			gggame.m.cls();
			gggame.draw_cards();
			gggame.m.print_matrix();
			char c;
			int cost = (i)*10 + Game::start_cost;
			cout << "Balance:\t" << gggame.money << endl;
			if (gggame.money < cost){
				cout << "Out of money";
				system("pause");
				return 0;
			}
			cout << "Choose card to open(cost:" << cost << "):\t";
			cin >> c;
			if (c == 'r')
				break;
			gggame.cards[c - 1].is_showed_up = true;
			gggame.money += gggame.cards[c - 1].value;
		}
	}
  return 0;
}
