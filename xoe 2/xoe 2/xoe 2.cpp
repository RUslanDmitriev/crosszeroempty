
#include <iostream>
#include <random>
#include <stdlib.h>
#include <chrono>
using namespace std;
string b,d;
//ENUMS=========================================================
enum Tcell :char


{
	Cross = 'x',
	Zero = '0',
	Empty = '_'


};



enum Tpreogress
{

	IN_game,
	WIN_AI,
	WIN_HuMAN,
	WIN_HUMAN2,
	DRAW


};

//STRUCTS=================================================================
struct TCORD
{
	size_t y{ 0U };
	size_t x{ 0U };

};
#pragma pack(push,1)
struct TGame
{
	Tcell** PPField{ nullptr };
	const size_t SIZE{ 3U };
	Tpreogress progress{ IN_game };
	Tcell human,human2, ai;
	size_t  turn{ 0U };
};
#pragma pack(pop) 
//random
int32_t getRandomNum(const int32_t min, const int32_t max)
{
	const static auto seed = chrono::system_clock::now().time_since_epoch().count();
	static mt19937_64 generator(seed);
	uniform_int_distribution<int32_t> dis(min, max);
	return dis(generator);
}
//function=====================================================





void initGamePvC(TGame& g)
{
	g.PPField = new Tcell * [g.SIZE];
	for (size_t i = 0U; i < g.SIZE; i++)
	{
		g.PPField[i] = new Tcell[g.SIZE];
	}
	for (size_t y = 0; y < g.SIZE; y++)
	{
		for (size_t x = 0; x < g.SIZE; x++)
		{
			g.PPField[y][x] = Empty;
		}

	}
	if (getRandomNum(0, 200) > 100)
	{
		g.human = Cross;
		g.ai = Zero;
		g.turn = 0;
	}
	else
	{
		g.human = Zero;
		g.ai = Cross;
		g.turn = 1;
	}
}


void initGamePvP(TGame& g)
{
	g.PPField = new Tcell * [g.SIZE];
	for (size_t i = 0U; i < g.SIZE; i++)
	{
		g.PPField[i] = new Tcell[g.SIZE];
	}
	for (size_t y = 0; y < g.SIZE; y++)
	{
		for (size_t x = 0; x < g.SIZE; x++)
		{
			g.PPField[y][x] = Empty;
		}

	}
	if (getRandomNum(0, 200) > 100)
	{
		g.human = Cross;
		g.human2 = Zero;
		g.turn = 0;
	}
	else
	{
		g.human = Zero;
		g.human2 = Cross;
		g.turn = 1;
	}
}


void deinitGame(TGame& g)
{
	for (size_t i = 0U; i < g.SIZE; i++)
	{
		delete[] g.PPField[i];
	}
	delete[] g.PPField;
	g.PPField = nullptr;

}


void printGamePvP(const TGame& g)
{
	cout << "     ";
	for (size_t x = 0; x < g.SIZE; x++)
	{
		cout << x + 1 << "   ";
	}
	cout << endl;
	for (size_t y = 0; y < g.SIZE; y++)
	{
		cout << "" << y + 1 << " | ";
		for (size_t x = 0; x < g.SIZE; x++)
		{
			cout << g.PPField[y][x] << " | ";
		}
		cout << endl;
	}
	cout << b << "  " << "player:=" << g.human << endl <<d<<"  " << "player2:=" << g.human2 << endl;
}


void printGamePvC(const TGame& g)
{
	cout << "     ";
	for (size_t x = 0; x < g.SIZE; x++)
	{
		cout << x + 1 << "   ";
	}
	cout << endl;
	for (size_t y = 0; y < g.SIZE; y++)
	{
		cout << "" << y + 1 << " | ";
		for (size_t x = 0; x < g.SIZE; x++)
		{
			cout << g.PPField[y][x] << " | ";
		}
		cout << endl;
	}
	cout << b << "  " << "human:=" << g.human << endl << "AI:=" << g.ai << endl;
}


void endgamePvP(const TGame& g)
{

	if (g.progress == WIN_HuMAN)
		cout << b << "   " << "you win" << endl;
	else if (g.progress == WIN_AI)
		cout << b << "   " << "you loose,try again" << endl;
	if (g.progress == DRAW)
		cout << "draw,try again" << endl;

}

void endgamePvC(const TGame& g)
{

	if (g.progress == WIN_HuMAN)
		cout << b << "   " << "you win" << endl;
	else if (g.progress == WIN_AI)
		cout << b << "   " << "you loose,try again" << endl;
	if (g.progress == DRAW)
		cout << "draw,try again" << endl;

}


Tpreogress getWon(const TGame& g)
{


	//строки
	for (size_t y = 0; y < g.SIZE; y++)
	{
		if (g.PPField[y][0] == g.PPField[y][1] && g.PPField[y][0] == g.PPField[y][2])
		{
			if (g.PPField[y][0] == g.human)
				return WIN_HuMAN;
			if (g.PPField[y][0] == g.ai)
				return WIN_AI;
		}

	}
	//столбы


	for (size_t x = 0; x < g.SIZE; x++)
	{
		if (g.PPField[0][x] == g.PPField[1][x] && g.PPField[0][x] == g.PPField[2][x])
		{
			if (g.PPField[0][x] == g.human)
				return WIN_HuMAN;
			if (g.PPField[0][x] == g.ai)
				return WIN_AI;
		}

	}
	// diagonaly
	if (g.PPField[0][0] == g.PPField[1][1] && g.PPField[0][0] == g.PPField[2][2])
	{
		if (g.PPField[1][1] == g.human)
			return WIN_HuMAN;
		if (g.PPField[1][1] == g.ai)
			return WIN_AI;
	}
	if (g.PPField[0][2] == g.PPField[1][1] && g.PPField[2][0] == g.PPField[1][1])
	{
		if (g.PPField[1][1] == g.human)
			return WIN_HuMAN;
		if (g.PPField[1][1] == g.ai)
			return WIN_AI;
	}
	//draw
	bool draw{ true };
	for (size_t y = 0; y < g.SIZE; y++)
	{
		for (size_t x = 0; x < g.SIZE; x++)
		{
			if (g.PPField[y][x] == Empty)
			{
				draw = false;
				break;
			}
		}
		if (!draw)
			break;
	}
	if (draw)
		return DRAW;

	return IN_game;
}




TCORD getHumancoord(const TGame& g)

{
	TCORD  c;
	do {

		cout << "ENter X:";
		cin >> c.x;
		cout << "ENter Y:";
		cin >> c.y;
		c.x--;
		c.y--;

	} while (c.x > 2 || c.y > 2 || g.PPField[c.y][c.x] != Empty);
	return c;
}



TCORD	getAIcoordeasy(TGame& g)
{
	if (g.PPField[1][1] == Empty)

	{
		return{ 1,1 };
	}
	TCORD arr[4];
	size_t numb{ 0U };
	if (g.PPField[0][0] == Empty)
	{
		arr[numb] = { 0,0 };
		numb++;
	}
	if (g.PPField[2][0] == Empty)
	{
		arr[numb] = { 2,0 };
		numb++;
	}
	if (g.PPField[0][2] == Empty)
	{
		arr[numb] = { 0,2 };
		numb++;
	}
	if (g.PPField[2][2] == Empty)
	{
		arr[numb] = { 2,2 };
		numb++;
	}
	if (numb > 0)
	{
		const size_t ind = getRandomNum(0, 200) % numb;
		return arr[ind];
	}
	if (g.PPField[1][0] == Empty)
	{
		arr[numb] = { 1,0 };
		numb++;
	}
	if (g.PPField[0][1] == Empty)
	{
		arr[numb] = { 0,1 };
		numb++;
	}
	if (g.PPField[1][2] == Empty)
	{
		arr[numb] = { 1,2 };
		numb++;
	}
	if (g.PPField[2][1] == Empty)
	{
		arr[numb] = { 2,1 };
		numb++;
	}
	if (numb > 0)
	{
		const size_t ind = getRandomNum(0, 200) % numb;
		return arr[ind];
	}
	return{ 0,0 };


}




TCORD	getAIcoordmedium(TGame& g)
{



	for (size_t y = 0; y < g.SIZE; y++)
	{
		for (size_t x = 0; x < g.SIZE; x++)
		{
			if (g.PPField[y][x] == Empty)
			{
				g.PPField[y][x] = g.ai;
				if (getWon(g) == WIN_AI)
				{
					g.PPField[y][x] = Empty;
					return{ y,x };
				}
				g.PPField[y][x] = Empty;
			}
		}

	}

	if (g.PPField[1][1] == Empty)
	{
		return{ 1,1 };
	}
	TCORD arr[4];
	size_t numb{ 0U };
	if (g.PPField[0][0] == Empty)
	{
		arr[numb] = { 0,0 };
		numb++;
	}
	if (g.PPField[2][0] == Empty)
	{
		arr[numb] = { 2,0 };
		numb++;
	}
	if (g.PPField[0][2] == Empty)
	{
		arr[numb] = { 0,2 };
		numb++;
	}
	if (g.PPField[2][2] == Empty)
	{
		arr[numb] = { 2,2 };
		numb++;
	}
	if (numb > 0)
	{
		const size_t ind = getRandomNum(0, 200) % numb;
		return arr[ind];
	}
	if (g.PPField[1][0] == Empty)
	{
		arr[numb] = { 1,0 };
		numb++;
	}
	if (g.PPField[0][1] == Empty)
	{
		arr[numb] = { 0,1 };
		numb++;
	}
	if (g.PPField[1][2] == Empty)
	{
		arr[numb] = { 1,2 };
		numb++;
	}
	if (g.PPField[2][1] == Empty)
	{
		arr[numb] = { 2,1 };
		numb++;
	}
	if (numb > 0)
	{
		const size_t ind = getRandomNum(0, 200) % numb;
		return arr[ind];
	}
	return{ 0,0 };

}




TCORD	getAIcoordhard(TGame& g)
{
	for (size_t y = 0; y < g.SIZE; y++)
	{
		for (size_t x = 0; x < g.SIZE; x++)
		{
			if (g.PPField[y][x] == Empty)
			{
				g.PPField[y][x] = g.human;
				if (getWon(g) == WIN_HuMAN)
				{
					g.PPField[y][x] = Empty;
					return{ y,x };
				}
				g.PPField[y][x] = Empty;
			}
		}

	}
	for (size_t y = 0; y < g.SIZE; y++)
	{
		for (size_t x = 0; x < g.SIZE; x++)
		{
			if (g.PPField[y][x] == Empty)
			{
				g.PPField[y][x] = g.ai;
				if (getWon(g) == WIN_AI)
				{
					g.PPField[y][x] = Empty;
					return{ y,x };
				}
				g.PPField[y][x] = Empty;
			}
		}

	}

	if (g.PPField[1][1] == Empty)
	{
		return{ 1,1 };
	}
	TCORD arr[4];
	size_t numb{ 0U };
	if (g.PPField[0][0] == Empty)
	{
		arr[numb] = { 0,0 };
		numb++;
	}
	if (g.PPField[2][0] == Empty)
	{
		arr[numb] = { 2,0 };
		numb++;
	}
	if (g.PPField[0][2] == Empty)
	{
		arr[numb] = { 0,2 };
		numb++;
	}
	if (g.PPField[2][2] == Empty)
	{
		arr[numb] = { 2,2 };
		numb++;
	}
	if (numb > 0)
	{
		const size_t ind = getRandomNum(0, 200) % numb;
		return arr[ind];
	}
	if (g.PPField[1][0] == Empty)
	{
		arr[numb] = { 1,0 };
		numb++;
	}
	if (g.PPField[0][1] == Empty)
	{
		arr[numb] = { 0,1 };
		numb++;
	}
	if (g.PPField[1][2] == Empty)
	{
		arr[numb] = { 1,2 };
		numb++;
	}
	if (g.PPField[2][1] == Empty)
	{
		arr[numb] = { 2,1 };
		numb++;
	}
	if (numb > 0)
	{
		const size_t ind = getRandomNum(0, 200) % numb;
		return arr[ind];
	}
	return{ 0,0 };

}







//=======================================================================================


int main()
{
	int mod;
	cout << "chose mode game" << endl << "1 = player vs player" << endl\
		<< "2 = player vs computer(easy)" << endl << "3 = player vs computer(medium)" << endl\
		<< "4 = player vs computer(hard)" << endl;
	cin >> mod;
	if (mod == 1)
	{
		cout << "Enter player 1 name" << endl;
		cin >> b;
		cout << endl;
		cout << "Enter player 2 name" << endl;
		cin >> d;
		cout << endl;
		TGame g;
		initGamePvP(g);
		system("cls");
		printGamePvP(g);

		do
		{
			if (g.turn % 2 == 0)
			{
				const TCORD  c = getHumancoord(g);
				g.PPField[c.y][c.x] = g.human;
			}
			else
			{
				const TCORD  c = getHumancoord(g);
				g.PPField[c.y][c.x] = g.human2;
			}
			system("cls");
			printGamePvP(g);
			g.turn++;
			g.progress = getWon(g);
		} while (g.progress == IN_game);


		endgamePvC(g);
		deinitGame(g);
	}
	else if (mod == 2)
	{
		cout << "Enter your name" << endl;
		cin >> b;
		cout << endl;
		TGame g;
		initGamePvC(g);
		system("cls");
		printGamePvC(g);

		do
		{
			if (g.turn % 2 == 0)
			{
				const TCORD  c = getHumancoord(g);
				g.PPField[c.y][c.x] = g.human;
			}
			else
			{
				const TCORD  c = getAIcoordeasy(g);
				g.PPField[c.y][c.x] = g.ai;
			}
			system("cls");
			printGamePvC(g);
			g.turn++;
			g.progress = getWon(g);
		} while (g.progress == IN_game);


		endgamePvC(g);
		deinitGame(g);
	}
	else if (mod == 3)
	{
		cout << "Enter your name" << endl;
		cin >> b;
		cout << endl;
		TGame g;
		initGamePvC(g);
		system("cls");
		printGamePvC(g);

		do
		{
			if (g.turn % 2 == 0)
			{
				const TCORD  c = getHumancoord(g);
				g.PPField[c.y][c.x] = g.human;
			}
			else
			{
				const TCORD  c = getAIcoordmedium(g);
				g.PPField[c.y][c.x] = g.ai;
			}
			system("cls");
			printGamePvC(g);
			g.turn++;
			g.progress = getWon(g);
		} while (g.progress == IN_game);


		endgamePvC(g);
		deinitGame(g);
	}
	else if (mod == 4)
	{
		cout << "Enter your name" << endl;
		cin >> b;
		cout << endl;
		TGame g;
		initGamePvC(g);
		system("cls");
		printGamePvC(g);

		do
		{
			if (g.turn % 2 == 0)
			{
				const TCORD  c = getHumancoord(g);
				g.PPField[c.y][c.x] = g.human;
			}
			else
			{
				const TCORD  c = getAIcoordhard(g);
				g.PPField[c.y][c.x] = g.ai;
			}
			system("cls");
			printGamePvC(g);
			g.turn++;
			g.progress = getWon(g);
		} while (g.progress == IN_game);


		endgamePvC(g);
		deinitGame(g);
	}


	return (0);
}

