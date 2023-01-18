#ifndef ADDDISH_H
#define ADDDISH_H

////QT INCLUDES////
#include <QMainWindow>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QDate>
#include <QDialog>

namespace Ui {
class AddDish;
}

/// <summary>
/// Класс, отображающий графический интерфейс и содержащий в себе функционал добавления принятой пищи
/// </summary>
class AddDish : public QDialog
{
    Q_OBJECT

public:
    /// <summary>
    /// Конструктор класса AddDish. В аргументы конструктора можно передать указатель на родительский класс,
    /// что передаст управление памятью экземпляру родительского класса
    /// </summary>
    /// <param name="parent">Указатель на родительский класс</param>
    /// <param name="row"></param>
    /// <param name="date"></param>
    /// <param name="time"></param>
    explicit AddDish(QWidget *parent = nullptr, int row = 0, QString date = "", QString time = "");
    /// <summary>
    /// Деструктор класса AddDish.
    /// </summary>
    ~AddDish();
    /// <summary>
    /// Поле, хранящее в себе id съеденного блюда
    /// </summary>
    int tmp_row;
    /// <summary>
    /// Поле, хранящее в себе количество съеденного блюда
    /// </summary>
    int tmp_count;
    /// <summary>
    /// Поле, хранящее в себе название съеденного блюда
    /// </summary>
    QString tmp_name;

private slots:
    /// <summary>
    /// Метод, использующийся для сохранения номера выбранного элемента в таблице
    /// </summary>
    /// <param name="index">Индекс выбранного элемента в таблице</param>
    void on_tableView_clicked(const QModelIndex &index);
    /// <summary>
    /// Метод, использующийся для сохранения данных о съеденном блюде в таблице
    /// </summary>
    void on_pushButton_clicked();

private:
    /// <summary>
    /// Поле, хранящее указатель на экземпляр, отвечающий за графический интерфейс и его элементы
    /// </summary>
    Ui::AddDish *ui;
    /// <summary>
    /// Поле, хранящее в себе базу данных
    /// </summary>
    QSqlDatabase db;
    QSqlTableModel *model;
    QSqlQuery *query;
    /// <summary>
    /// Поле, хранящее в себе номер выбранной строки в таблице
    /// </summary>
    int row;
    /// <summary>
    /// Поле, хранящее в себе дату, выбранную на календаре
    /// </summary>
    QString date;
    /// <summary>
    /// Поле, хранящее в себе момент приема пищи (breakfast, lunch, dinner, snack)
    /// </summary>
    QString time;

};

#endif // ADDDISH_H
