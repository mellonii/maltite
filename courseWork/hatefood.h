#ifndef HATEFOOD_H
#define HATEFOOD_H

#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>

#include <QDialog>

namespace Ui {
class HateFood;
}

class HateFood : public QDialog
{
    Q_OBJECT

public:
    explicit HateFood(QWidget *parent = nullptr);
    ~HateFood();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::HateFood *ui;

    QSqlDatabase db;
    QSqlTableModel *model;
    QSqlTableModel *modelProd;

    int row;
};

#endif // HATEFOOD_H
