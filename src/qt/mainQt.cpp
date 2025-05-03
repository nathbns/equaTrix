#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // Set application information
    QApplication::setApplicationName("equaTrix");
    QApplication::setApplicationVersion("1.0");
    QApplication::setOrganizationName("equaTrix");
    
    // Set French locale for number formatting
    QLocale::setDefault(QLocale(QLocale::French, QLocale::France));
    
    MainWindow w;
    w.show();
    return a.exec();
}
