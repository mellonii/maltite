#ifndef ADDDISH_H
#define ADDDISH_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QDate>

#include <QDialog>

namespace Ui {
class AddDish;
class MainWindow;
}

class AddDish : public QDialog
{
    Q_OBJECT

public:
    explicit AddDish(QWidget *parent = nullptr, int row = 0, QString date = "", QString time = "");
    ~AddDish();

    int tmp_row;
    int tmp_count;
    QString tmp_name;

private slots:

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

private:
    Ui::AddDish *ui;
    Ui::MainWindow *MWui;

    QSqlDatabase db;
    QSqlTableModel *model;
    QSqlQuery *query;
    int row;
    QString date;
    QString time;

};

#endif // ADDDISH_H
