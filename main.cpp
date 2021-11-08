
/*Игра змейка Snake
 *     ***0   @
*/

//Управление кнопками wasd, для выхода - q, пробел - пауза

#include <iostream>
#include <vector>
#include <unistd.h>   //для sleep
#include <sys/ioctl.h>  //для функции kbhit
#include <termios.h>    //для функции kbhit
//#include <conio.h>    //для kbhit под windows

int kbhit()   //переопределяем функцию, т.к. из библиотеки не работает можно убрать и вернуть библиотеку conio.h
{
	termios term;
	tcgetattr(0, &term);

	termios term2 = term;
	term2.c_lflag &= ~ICANON;
	tcsetattr(0, TCSANOW, &term2);

	int byteswaiting;
	ioctl(0, FIONREAD, &byteswaiting);

	tcsetattr(0, TCSANOW, &term);

	return byteswaiting;
}

void enable_raw_mode()   //функция убирающая отображение нажатой клавиши в консоли
{
	termios term;
	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON | ECHO); // Disable echo as well
	tcsetattr(0, TCSANOW, &term);
}
//void disable_raw_mode()
//{
//	termios term;
//	tcgetattr(0, &term);
//	term.c_lflag |= ICANON | ECHO;
//	tcsetattr(0, TCSANOW, &term);
//}
using namespace std;

#include "SnakeUnit.h"

int main()
{
	SnakeUnit snake;
	clock_t TimerKey; //объявляем таймер для клавиатуры
	clock_t TimerStep;   //таймер для шага
	TimerKey= TimerStep = clock(); //записываем текущее значение
	double timeKey = 0.1;  //шаг опроса клавиатуры
	double timeStep = 0.5;   //таймер перемещения

	enable_raw_mode();
	snake.DrawField();

	while(1)
	{
		if((clock()-TimerKey)/(double)CLOCKS_PER_SEC >= timeKey) //если прошло timeKey с момента последней итерации, то выполняем очередную
		{
			if(kbhit())
			{
//				int k;
				switch (int k = getchar())
				{
				case 119:   //w - вверх
					if(snake.Vec != snake.DOWN)
						snake.nextVec = snake.UP;
					break;
				case 97:   //a - влево
					if(snake.Vec != snake.RIGHT)
						snake.nextVec = snake.LEFT;
					break;
				case 100:   //d - вправо
					if(snake.Vec != snake.LEFT)
						snake.nextVec = snake.RIGHT;
					break;
				case 115:   //s - вниз
					if(snake.Vec != snake.UP)
						snake.nextVec = snake.DOWN;
					break;
//				case 112:   //p - пауза
				case 32:   //пробел - пауза
					snake.p =!snake.p;
					snake.DrawField();
					break;
				case 113:   //q - выход
					snake.GameOver();
					return 0;;
				}
				if(!snake.p)
				{
					snake.Step();
					snake.DrawField();
				}
//				cout << k << endl;
			}
			TimerKey = clock(); //сброс таймера

		}
		if((clock()-TimerStep)/(double)CLOCKS_PER_SEC >= timeStep && !snake.p)
		{
			snake.Step();
			TimerStep = clock();
		}
	}
	return 0;
}
