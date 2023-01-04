#include "mainwindow.h"
#include "create_prod.h"
#include "create_recipe.h"
#include "recipe.h"
#include "product.h"
#include "adddish.h"
#include <fstream>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
