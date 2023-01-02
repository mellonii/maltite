#ifndef PRODUCT_H
#define PRODUCT_H

#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>

#include <QDialog>
#include <vector>


namespace Ui {
class Product;
}

class Product : public QDialog
{
    Q_OBJECT

public:
    explicit Product(QWidget *parent = nullptr, int row_1 = 0);
    ~Product();


private:
    Ui::Product *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    QSqlTableModel *modelProduct;
};

#endif // PRODUCT_H
