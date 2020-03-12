/*!
    \file    main.cpp
    \author  Vinu Raja Kumar C <VinuRajaKumar@gmail.com>
    \date    07:45:35 PM IST 02/03/2020 
*/

#include <QApplication>
#include "QHexWindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QHexWindow* HexWindow = new QHexWindow;
    HexWindow->show();

    return app.exec();
}
