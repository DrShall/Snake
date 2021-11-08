#include "SnakeUnit.h"
#include <iostream>
#include <vector>

using namespace std;

void SnakeUnit::DrawField()
		{
			for(auto dot: snakeBody)
				ppSnake[dot.nRow][dot.nCol] = '*';
			ppSnake[snakeBody[0].nRow][snakeBody[0].nCol] = '0';
			cout << "\033[2J\033[1;1H";   //очистить экран
			for(int row = 0; row <= MAX_ROW+1; ++row)
			{
				for(int col = 0; col <= MAX_COL+1; ++col)
					cout << ppSnake[row][col];
				cout << endl;
			}
			if(p)
				cout << "Нажата пауза" << endl;
		}

void SnakeUnit::EatApple()
		{
			snakeBody.insert(snakeBody.begin(), apple);
			bool notInBody;
			do
			{
				notInBody = true;
				apple.nRow = rand()%MAX_ROW + 1;
				apple.nCol = rand()%MAX_COL + 1;
				for(int d = 0; d <= snakeBody.size(); d++)
					if(snakeBody[d].nRow == apple.nRow && snakeBody[d].nCol == apple.nCol)
					{
						notInBody = false;
						break;
					}
			}
			while(!notInBody);
			ppSnake[apple.nRow][apple.nCol] = '@';
		}

void SnakeUnit::Step()
		{
			bool nextStepIsBody = false;
			switch (nextVec)
			{
			case RIGHT:
				for(int i = 3; i < snakeBody.size(); ++i)
					if(snakeBody[i].nRow == snakeBody[0].nRow && snakeBody[i].nCol == (snakeBody[0].nCol+1))
						nextStepIsBody = true;
				if(snakeBody[0].nCol == MAX_COL || nextStepIsBody)
					GameOver();
				else if(snakeBody[0].nRow == apple.nRow && snakeBody[0].nCol+1 == apple.nCol)
				{
					EatApple();
				}
				else
				{
					point temp, prev= {snakeBody[0].nRow, snakeBody[0].nCol};
					snakeBody[0].nCol++;
					for(int i = 1; i < snakeBody.size(); ++i)
					{
						temp = snakeBody[i];
						snakeBody[i].nRow = prev.nRow;
						snakeBody[i].nCol = prev.nCol;
						prev = temp;
						ppSnake[prev.nRow][prev.nCol] = ' ';
					}
				}
				break;
			case LEFT:
				for(int i = 3; i < snakeBody.size(); ++i)
					if(snakeBody[i].nRow == snakeBody[0].nRow && snakeBody[i].nCol == (snakeBody[0].nCol-1))
						nextStepIsBody = true;
				if(snakeBody[0].nCol == 1 || nextStepIsBody)
					GameOver();
				else if(snakeBody[0].nRow == apple.nRow && snakeBody[0].nCol-1 == apple.nCol)
				{
					EatApple();
				}
				else
				{
					point temp, prev= {snakeBody[0].nRow, snakeBody[0].nCol};
					snakeBody[0].nCol--;
					for(int i = 1; i < snakeBody.size(); ++i)
					{
						temp = snakeBody[i];
						snakeBody[i].nRow = prev.nRow;
						snakeBody[i].nCol = prev.nCol;
						prev = temp;
						ppSnake[prev.nRow][prev.nCol] = ' ';
					}
				}
				break;
			case UP:
				for(int i = 3; i < snakeBody.size(); ++i)
					if(snakeBody[i].nRow == snakeBody[0].nRow-1 && snakeBody[i].nCol == (snakeBody[0].nCol))
						nextStepIsBody = true;
				if(snakeBody[0].nRow == 1 || nextStepIsBody)
					GameOver();
				else if(snakeBody[0].nRow == apple.nRow && snakeBody[0].nCol-1 == apple.nCol)
				{
					EatApple();
				}
				else
				{
					point temp, prev= {snakeBody[0].nRow, snakeBody[0].nCol};
					snakeBody[0].nRow--;
					for(int i = 1; i < snakeBody.size(); ++i)
					{
						temp = snakeBody[i];
						snakeBody[i].nRow = prev.nRow;
						snakeBody[i].nCol = prev.nCol;
						prev = temp;
						ppSnake[prev.nRow][prev.nCol] = ' ';
					}
				}
				break;
			case DOWN:
				for(int i = 3; i < snakeBody.size(); ++i)
					if(snakeBody[i].nRow == snakeBody[0].nRow+1 && snakeBody[i].nCol == (snakeBody[0].nCol))
						nextStepIsBody = true;
				if(snakeBody[0].nRow == MAX_ROW || nextStepIsBody)
					GameOver();
				else if(snakeBody[0].nRow+1 == apple.nRow && snakeBody[0].nCol == apple.nCol)
				{
					EatApple();
				}
				else
				{
					point temp, prev= {snakeBody[0].nRow, snakeBody[0].nCol};
					snakeBody[0].nRow++;
					for(int i = 1; i < snakeBody.size(); ++i)
					{
						temp = snakeBody[i];
						snakeBody[i].nRow = prev.nRow;
						snakeBody[i].nCol = prev.nCol;
						prev = temp;
						ppSnake[prev.nRow][prev.nCol] = ' ';
					}
				}
				break;
			}
			DrawField();
			Vec = nextVec;
		}
