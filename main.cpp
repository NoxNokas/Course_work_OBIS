#include "mainwindow.h"
#include <QApplication>
#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "array.h"


#define max(a, b) ( ( (a) > (b) ) ? (a) : (b) )
#define min(a, b) ( ( (a) < (b) ) ? (a) : (b) )


#include "integrator.h"
#include "custom.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();



    return a.exec();
}
