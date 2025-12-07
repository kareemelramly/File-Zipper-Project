#include "mainwindow.h"

#include <QApplication>

// Entry point - starts the Qt application
 int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;  // Create main window
    w.show();      // Display it
    return a.exec();  // Run event loop
}

