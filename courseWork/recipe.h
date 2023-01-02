#ifndef RECIPE_H
#define RECIPE_H

#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>

#include <QDialog>

namespace Ui {
class Recipe;
}

class Recipe : public QDialog
{
    Q_OBJECT

public:
    explicit Recipe(QWidget *parent = nullptr, int row = 0);
    ~Recipe();

private:
    Ui::Recipe *ui;

    QSqlDatabase db;
    QSqlTableModel *model_recipes;
    QSqlQuery *query;

};

#endif // RECIPE_H
