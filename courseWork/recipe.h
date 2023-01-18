#ifndef RECIPE_H
#define RECIPE_H

////QT INCLUDES////
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QDialog>

namespace Ui {
class Recipe;
}

/// <summary>
/// Класс, отображающий графический интерфейс и содержащий в себе информацию о выбранном рецепте
/// </summary>
class Recipe : public QDialog
{
    Q_OBJECT

public:
    /// <summary>
    /// Конструктор класса Recipe. В аргументы конструктора можно передать указатель на родительский класс,
    /// что передаст управление памятью экземпляру родительского класса, и номер продукта,
    /// подробную информацию о котором хотят посмотреть
    /// </summary>
    /// <param name="parent">Указатель на родительский класс</param>
    /// <param name="row">Номер выбранного продукта</param>
    explicit Recipe(QWidget *parent = nullptr, int row = 0);
    /// <summary>
    /// Деструктор класса Recipe.
    /// </summary>
    ~Recipe();

private:
    /// <summary>
    /// Поле, хранящее указатель на экземпляр, отвечающий за графический интерфейс и его элементы
    /// </summary>
    Ui::Recipe *ui;
    /// <summary>
    /// Поле, хранящее в себе базу данных
    /// </summary>
    QSqlDatabase db;
    /// <summary>
    /// Поле, хранящее в себе указадель на модель с информацией о выбранном рецепте
    /// </summary>
    QSqlTableModel *model_recipes;
    /// <summary>
    /// Поле, хранящее в себе указатель на запрос, выводящий нужную строку о рецепте из таблицы
    /// </summary>
    QSqlQuery *query;

};

#endif // RECIPE_H
