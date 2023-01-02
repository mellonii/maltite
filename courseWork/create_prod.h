#ifndef CREATE_PROD_H
#define CREATE_PROD_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>

#include <QDialog>

namespace Ui {
class Create_prod;
}

class Create_prod : public QDialog
{
    Q_OBJECT

public:
    explicit Create_prod(QWidget *parent = nullptr);
    ~Create_prod();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Create_prod *ui;
    QSqlDatabase db;
    QSqlTableModel *modelProduct;

};

#endif // CREATE_PROD_H
