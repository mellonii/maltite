#ifndef HATEFOOD_H
#define HATEFOOD_H

////QT INCLUDES////
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QDialog>

namespace Ui {
class HateFood;
}

/// <summary>
/// Класс, отображающий графический интерфейс и содержащий в себе функционал добавления ненавистных продуктов
/// </summary>
class HateFood : public QDialog
{
    Q_OBJECT

public:
    /// <summary>
    /// Конструктор класса HateFood. В аргументы конструктора можно передать указатель на родительский класс,
    /// что передаст управление памятью экземпляру родительского класса
    /// </summary>
    /// <param name="parent">Указатель на родительский класс</param>
    explicit HateFood(QWidget *parent = nullptr);
    /// <summary>
    /// Деструктор класса HateFood.
    /// </summary>
    ~HateFood();

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
    void on_tableView_clicked(const QModelIndex& index);

private:
    /// <summary>
    /// Поле, хранящее указатель на экземпляр, отвечающий за графический интерфейс и его элементы
    /// </summary>
    Ui::HateFood *ui;
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

#endif // HATEFOOD_H
