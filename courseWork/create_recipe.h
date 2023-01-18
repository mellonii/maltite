#ifndef CREATE_RECIPE_H
#define CREATE_RECIPE_H

////QT INCLUDES////
#include <QMainWindow>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlError>
#include <QDialog>

////STD INCLUDES////
#include <map>
#include <algorithm>
#include <vector>

namespace Ui {
class create_recipe;
}

/// <summary>
/// Структура с информацией о продукте
/// </summary>
struct Products {
    /// <summary>
    /// Поле, хранящее в себе id продукта в таблице
    /// </summary>
    int id;
    /// <summary>
    /// Поле, хранящее в себе название продукта
    /// </summary>
    QString name;
    /// <summary>
    /// Поле, хранящее в себе содержание калорий в продукте в 100 г
    /// </summary>
    int Calories;
    /// <summary>
    /// Поле, хранящее в себе содержание углеводов в продукте в 100 г
    /// </summary>
    double Carbohydrate;
    /// <summary>
    /// Поле, хранящее в себе содержание белков в продукте в 100 г
    /// </summary>
    double Protein;
    /// <summary>
    /// Поле, хранящее в себе содержание жиров в продукте в 100 г
    /// </summary>
    double Fat;
    /// <summary>
    /// Конструктор структуры Products.
    /// </summary>
    Products();
    /// <summary>
    /// Конструктор структуры Products. В аргументы конструктора можно передать номер продукта,
    /// количество кбжу в 100 граммах этого продукта
    /// </summary>
    /// <param name="id">Номер продукта</param>
    /// <param name="Calories">Количество калорий в 100 г этого продукта</param>
    /// <param name="Protein">Количество белков в 100 г этого продукта</param>
    /// <param name="Fat">Количество жиров в 100 г этого продукта</param>
    /// <param name="Carbohydrate">Количество углеводов в 100 г этого продукта</param>
    /// <param name="name">Название продукта</param>
    Products(int id, int Calories, double Protein, double Fat, double Carbohydrate, QString name);
};
/// <summary>
/// Структура с информацией о рецепте
/// </summary>
struct Dish {
    /// <summary>
    /// Поле, хранящее в себе название блюда
    /// </summary>
    QString name;
    /// <summary>
    /// Поле, хранящее в себе сам рецепт блюда
    /// </summary>
    QString recipe;
    /// <summary>
    /// Поле, хранящее в себе содержание калорий в блюде в 100 г
    /// </summary>
    int Calories;
    /// <summary>
    /// Поле, хранящее в себе содержание углеводов в блюде в 100 г
    /// </summary>
    double Carbohydrate;
    /// <summary>
    /// Поле, хранящее в себе содержание белков в блюде в 100 г
    /// </summary>
    double Protein;
    /// <summary>
    /// Поле, хранящее в себе содержание жиров блюде в 100 г
    /// </summary>
    double Fat;
    /// <summary>
    /// Значение, хранящее в себе входящие в блюдо ингредиенты и их количество в г
    /// </summary>
    std::map<double, Products> ingredient_list;
    /// <summary>
    /// Конструктор структуры Dish.
    /// </summary>
    Dish();
    /// <summary>
    /// Конструктор структуры Dish. В аргументы конструктора можно передать название блюда,
    /// его рецепт, и контейнер map с входящими ингредиентами в виде: количество в г, экземпляр структуры продуктов
    /// </summary>
    /// <param name="name">Название блюда</param>
    /// <param name="recipe">Рецепт</param>
    /// <param name="ingredient_list">Ингредиенты</param>
    Dish(QString name, QString recipe, std::map<double, Products> ingredient_list);
    /// <summary>
    /// Метод, отвечающий за добавление в ingredient_list продукта
    /// </summary>
    /// <param name="count">Количество продукта в г</param>
    /// <param name="product">Экземпляр структуры продукта</param>
    void addProduct(double count, Products product);
};

/// <summary>
/// Класс, отображающий графический интерфейс и содержащий в себе функционал создания рецепта
/// </summary>
class create_recipe : public QDialog
{
    Q_OBJECT

public:
    /// <summary>
    /// Конструктор класса create_recipe. В аргументы конструктора можно передать указатель на родительский класс,
    /// что передаст управление памятью экземпляру родительского класса, и нынешнее количество рецептов в таблице
    /// </summary>
    /// <param name="parent">Указатель на родительский класс</param>
    /// <param name="num">Номер создаваемого рецепта</param>
    explicit create_recipe(QWidget *parent = nullptr, int num = 0);
    /// <summary>
    /// Деструктор класса create_recipe.
    /// </summary>
    ~create_recipe();

private slots:
    /// <summary>
    /// Метод, использующийся для добавления нового ингредиента
    /// </summary>
    void on_pushButton_clicked();
    /// <summary>
    /// Метод, использующийся для открытия окна для сохранения данных о записанном рецепте в таблице
    /// </summary>
    void on_pushButton_2_clicked();

private:
    /// <summary>
    /// Поле, хранящее указатель на экземпляр, отвечающий за графический интерфейс и его элементы
    /// </summary>
    Ui::create_recipe *ui;
    /// <summary>
    /// Поле, хранящее в себе базу данных
    /// </summary>
    QSqlDatabase db;
    /// <summary>
    /// Поле, хранящее в себе указатель на
    /// </summary>
    QSqlTableModel *modelProduct;
    QSqlTableModel *modelAllProduct;
    QSqlTableModel *modelProd;
    QSqlQuery *queryProduct;
    QSqlQuery *queryDropProduct;
    QSqlQuery *query_all;
    QSqlQuery *query;
    /// <summary>
    /// Поле, хранящее в себе количество рецептов в таблице
    /// </summary>
    int num;
};

#endif // CREATE_RECIPE_H
