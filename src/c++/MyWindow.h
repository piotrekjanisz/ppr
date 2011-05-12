/*
 * MyWindow.h
 *
 *  Created on: May 12, 2011
 *      Author: piotrek
 */

#ifndef MYWINDOW_H_
#define MYWINDOW_H_

#include <eq/eq.h>
#include <iostream>

class MyWindow : public eq::Window
{
public:
	MyWindow(eq::Pipe* parent)
		: eq::Window(parent) {}

	virtual void drawFPS() const
	{
		std::cout << "FPS: " << getFPS() << std::endl;
	}
};

#endif /* MYWINDOW_H_ */
