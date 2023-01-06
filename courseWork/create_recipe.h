#ifndef CREATE_RECIPE_H
#define CREATE_RECIPE_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlError>

#include <QDialog>

namespace Ui {
class create_recipe;
}

struct Products {
    int id;
    QString name;
    int Calories;
    double Carbohydrate;
    double Protein;
    double Fat;
    Products();
    Products(int id, int Calories, double Protein, double Fat, double Carbohydrate, QString name);
};
struct Dish {
    QString name;
    QString recipe;
    int Calories;
    double Carbohydrate;
    double Protein;
    double Fat;
    std::map<double, Products> ingredient_list; //map для сохранения ингредиентов и количества
    Dish();
    Dish(QString name, QString recipe, std::map<double, Products> ingredient_list);
    void addProduct(double count, Products product);
};

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
};

#endif // CREATE_RECIPE_H
