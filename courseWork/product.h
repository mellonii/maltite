#ifndef PRODUCT_H
#define PRODUCT_H

////QT INCLUDES////
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QDialog>

////STD INCLUDES////
#include <vector>

namespace Ui {
class Product;
}

/// <summary>
/// Класс, отображающий графический интерфейс и содержащий в себе информацию о выбранном продукте
/// </summary>
class Product : public QDialog
{
    Q_OBJECT

public:
    /// <summary>
    /// Конструктор класса Product. В аргументы конструктора можно передать указатель на родительский класс,
    /// что передаст управление памятью экземпляру родительского класса, и номер продукта,
    /// подробную информацию о котором хотят посмотреть
    /// </summary>
    /// <param name="parent">Указатель на родительский класс</param>
    /// <param name="row_1">Номер выбранного продукта</param>
    explicit Product(QWidget *parent = nullptr, int row_1 = 0);
    /// <summary>
    /// Деструктор класса Product.
    /// </summary>
    ~Product();


private:
    /// <summary>
    /// Поле, хранящее указатель на экземпляр, отвечающий за графический интерфейс и его элементы
    /// </summary>
    Ui::Product *ui;
    /// <summary>
    /// Поле, хранящее в себе базу данных
    /// </summary>
    QSqlDatabase db;
    /// <summary>
    /// Поле, хранящее в себе указатель на запрос, выводящий нужную строку о продукте из таблицы
    /// </summary>
    QSqlQuery *query;
    /// <summary>
    /// Поле, хранящее в себе указадель на модель с информацией о выбранном продукте
    /// </summary>
    QSqlTableModel *modelProduct;
};

#endif // PRODUCT_H
