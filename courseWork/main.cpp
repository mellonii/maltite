#include "mainwindow.h"
#include "create_prod.h"
#include "create_recipe.h"
#include "recipe.h"
#include "product.h"
#include "adddish.h"

#include <QApplication>
#include <QSqlDatabase>

void create_prod(){
    /*
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./testDB.db");
    //db.setDatabaseName("./");
    if(db.open()){
        qDebug("Open");
    }else{
        qDebug("No open");
    }
    query_recipes = new QSqlQuery(db);
    */
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
