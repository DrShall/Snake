#pragma once
#include <iostream>
#include <vector>

class SnakeUnit
{
	public:
		enum VectorOfSnake { UP, DOWN, LEFT, RIGHT};
		bool p{false};  //флаг паузы
	private:
		int MAX_ROW, MAX_COL;
		char **ppSnake = nullptr;
		typedef struct
		{
				int nRow;
				int nCol;
		}point;
		std::vector<point> snakeBody;  //координаты тела змеи, первый элемент - голова
		point apple;

	public:
		SnakeUnit(int max_r = 25, int max_c = 50)
		{
			MAX_ROW = max_r;
					   MAX_COL = max_c;
					   ppSnake = new char*[MAX_ROW+2];
					   for(int i = 0; i <= MAX_ROW+1; ++i)
					   {
						   ppSnake[i] = new char[MAX_COL+2];
					   }
					   for(int row = 0; row <= MAX_ROW+1; ++row)   //инициализация пустого поля
						   for(int col = 0; col <= MAX_COL+1; ++col)
							   if(col == 0 || col == MAX_COL+1 || row == 0 || row == MAX_ROW+1)
								   ppSnake[row][col] = '+';
							   else
								   ppSnake[row][col] = ' ';
					   snakeBody = {{1, 2},{ 1, 1} };   //помещаем змею длинной 2 в левый верхний угол
					   apple.nRow = rand()%MAX_ROW + 1;
					   apple.nCol = rand()%MAX_COL + 1;
					   ppSnake[apple.nRow][apple.nCol] = '@';
		}

		void DrawField();

		void GameOver()
		{
//			cout << "\033[2J\033[1;1H";   //очистить экран
			std::cout << "Игра закончилась." << std::endl << "Вы успели вырастить змею до " << snakeBody.size() << std::endl;
//			sleep(5000);
		}

		VectorOfSnake nextVec = RIGHT;
		VectorOfSnake Vec = RIGHT;

		void EatApple();

		void Step();

		~SnakeUnit()
		{
			for(int row = 0; row < MAX_ROW+2; ++row)
				delete [] ppSnake[row];
			delete ppSnake;
			ppSnake = nullptr;
		}

};
