#include <iostream>
#include "window.h"

using namespace std;

int main() {
	XWindow w;


	for (int i = 1; i <= 8; ++i) {
		for (int j = 1; j <= 8; ++j) {

			if ((i + j) % 2) {
				w.fillRectangle(50 * i, 50 * j, 50, 50, XWindow::Cyan);
			}
			else {

				w.fillRectangle(50 * i, 50 * j, 50, 50, XWindow::White);

			}

		}




	}

	w.drawLine(50, 50, 450, 50);
	w.drawLine(50, 50, 50, 450);
	w.drawLine(450, 450, 450, 50);
	w.drawLine(450, 450, 50, 450);



	w.drawString(72, 77, "r");
	w.drawString(122, 77, "n");
	w.drawString(172, 77, "b");
	w.drawString(222, 77, "q");
	w.drawString(272, 77, "k");
	w.drawString(322, 77, "b");
	w.drawString(372, 77, "n");
	w.drawString(422, 77, "r");

	for (int i = 1; i <= 8; ++i) {
		w.drawString(22 + (50 * i), 127, "p");
		string s{ 'a' + i - 1 };
		w.drawString(22 + (50 * i), 40, s);
	}

	for (int i = 1; i <= 8; ++i) {
		w.drawString(22 + (50 * i), 377, "P");
		string s{ 'a' + i - 1 };
		w.drawString(22 + (50 * i), 470, s);
	}

	for (int i = 1; i <= 8; ++i) {
		string s{ i + '0' };
		w.drawString(35, 27 + (50 * (9 - i)), s);
		w.drawString(460, 27 + (50 * (9 - i)), s);
	}


	w.drawString(72, 427, "R");
	w.drawString(122, 427, "N");
	w.drawString(172, 427, "B");
	w.drawString(222, 427, "Q");
	w.drawString(272, 427, "K");
	w.drawString(322, 427, "B");
	w.drawString(372, 427, "N");
	w.drawString(422, 427, "R");




	char c;
	cin >> c;
}

