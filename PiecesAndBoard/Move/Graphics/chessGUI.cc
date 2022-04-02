#include <iostream>
#include "window.h"

using namespace std;

int main() {
	XWindow w;


	for (int i = 1; i <= 8; ++i) {
		for (int j = 1; j <= 8; ++j) {

			if ((i + j) % 2) {
				window->fillRectangle(50 * i, 50 * j, 50, 50, XWindow::Cyan);
			}
			else {

				window->fillRectangle(50 * i, 50 * j, 50, 50, XWindow::White);

			}

		}




	}

	window->drawLine(50, 50, 450, 50);
	window->drawLine(50, 50, 50, 450);
	window->drawLine(450, 450, 450, 50);
	window->drawLine(450, 450, 50, 450);



	window->drawString(72, 77, "r");
	window->drawString(122, 77, "n");
	window->drawString(172, 77, "b");
	window->drawString(222, 77, "q");
	window->drawString(272, 77, "k");
	window->drawString(322, 77, "b");
	window->drawString(372, 77, "n");
	window->drawString(422, 77, "r");

	for (int i = 1; i <= 8; ++i) {
		window->drawString(22 + (50 * i), 127, "p");
		string s{ 'a' + i - 1 };
		window->drawString(22 + (50 * i), 40, s);
	}

	for (int i = 1; i <= 8; ++i) {
		window->drawString(22 + (50 * i), 377, "P");
		string s{ 'a' + i - 1 };
		window->drawString(22 + (50 * i), 470, s);
	}

	for (int i = 1; i <= 8; ++i) {
		string s{ i + '0' };
		window->drawString(35, 27 + (50 * (9 - i)), s);
		window->drawString(460, 27 + (50 * (9 - i)), s);
	}


	window->drawString(72, 427, "R");
	window->drawString(122, 427, "N");
	window->drawString(172, 427, "B");
	window->drawString(222, 427, "Q");
	window->drawString(272, 427, "K");
	window->drawString(322, 427, "B");
	window->drawString(372, 427, "N");
	window->drawString(422, 427, "R");




	char c;
	cin >> c;
}

