#ifndef FAVFOOD_H
#define FAVFOOD_H

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>

#include <QDialog>

namespace Ui {
class FavFood;
}

class FavFood : public QDialog
{
    Q_OBJECT

public:
    explicit FavFood(QWidget *parent = nullptr);
    ~FavFood();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::FavFood *ui;

    QSqlDatabase db;
    QSqlTableModel *model;
    QSqlTableModel *modelProd;

    int row;
};

#endif // FAVFOOD_H
