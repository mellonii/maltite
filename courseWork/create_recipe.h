#ifndef CREATE_RECIPE_H
#define CREATE_RECIPE_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>

#include <QDialog>

namespace Ui {
class create_recipe;
}

struct Product;
struct Dish;

class create_recipe : public QDialog
{
    Q_OBJECT

public:
    explicit create_recipe(QWidget *parent = nullptr, int num = 0);
    ~create_recipe();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::create_recipe *ui;
    QSqlDatabase db;
    QSqlTableModel *modelProduct;
    QSqlTableModel *modelAllProduct;
    QSqlTableModel *modelProd;
    QSqlQuery *queryProduct;
    QSqlQuery *queryDropProduct;
    QSqlQuery *query_all;
    QSqlQuery *query;
    int num;
    bool a;
};

#endif // CREATE_RECIPE_H
