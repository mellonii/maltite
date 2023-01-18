#ifndef FAVFOOD_H
#define FAVFOOD_H

////QT INCLUDES////
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QDialog>

namespace Ui {
class FavFood;
}

/// <summary>
/// Класс, отображающий графический интерфейс и содержащий в себе функционал добавления любимых продуктов
/// </summary>
class FavFood : public QDialog
{
    Q_OBJECT

public:
    /// <summary>
    /// Конструктор класса FavFood. В аргументы конструктора можно передать указатель на родительский класс,
    /// что передаст управление памятью экземпляру родительского класса
    /// </summary>
    /// <param name="parent">Указатель на родительский класс</param>
    explicit FavFood(QWidget *parent = nullptr);
    /// <summary>
    /// Деструктор класса FavFood.
    /// </summary>
    ~FavFood();

private slots:
    /// <summary>
    /// Метод для добавления нового элемента в таблицу
    /// </summary>
    void on_pushButton_clicked();
    /// <summary>
    /// Метод для удаления элемента в таблице
    /// </summary>
    void on_pushButton_2_clicked();
    /// <summary>
    /// Метод для сохранения номера выбранного элемента в таблице
    /// </summary>
    /// <param name="index">Номер выбранного элемента</param>
    void on_tableView_clicked(const QModelIndex &index);

private:
    /// <summary>
    /// Поле, хранящее указатель на экземпляр, отвечающий за графический интерфейс и его элементы
    /// </summary>
    Ui::FavFood *ui;
    /// <summary>
    /// Поле, хранящее в себе базу данных
    /// </summary>
    QSqlDatabase db;
    QSqlTableModel *model;
    QSqlTableModel *modelProd;
    /// <summary>
    /// Поле, хранящее в себе номер выбранной строки в таблице
    /// </summary>
    int row;
};

#endif // FAVFOOD_H
