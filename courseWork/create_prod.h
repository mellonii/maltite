#ifndef CREATE_PROD_H
#define CREATE_PROD_H

////QT INCLUDES////
#include <QMainWindow>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QDialog>

namespace Ui {
class Create_prod;
}

/// <summary>
/// Класс, отображающий графический интерфейс и содержащий в себе функционал создания продукта
/// </summary>
class Create_prod : public QDialog
{
    Q_OBJECT

public:
    /// <summary>
    /// Конструктор класса Create_prod. В аргументы конструктора можно передать указатель на родительский класс,
    /// что передаст управление памятью экземпляру родительского класса
    /// </summary>
    /// <param name="parent">Указатель на родительский класс</param>
    explicit Create_prod(QWidget *parent = nullptr);
    /// <summary>
    /// Деструктор класса Create_prod.
    /// </summary>
    ~Create_prod();

private slots:
    /// <summary>
    /// Метод для создания нового продукта
    /// </summary>
    void on_pushButton_clicked();

private:
    /// <summary>
    /// Поле, хранящее указатель на экземпляр, отвечающий за графический интерфейс и его элементы
    /// </summary>
    Ui::Create_prod *ui;
    /// <summary>
    /// Поле, хранящее в себе базу данных
    /// </summary>
    QSqlDatabase db;
    QSqlTableModel *modelProduct;

};

#endif // CREATE_PROD_H
