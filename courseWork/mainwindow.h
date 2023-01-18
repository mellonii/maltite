#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "create_prod.h"
#include "create_recipe.h"
#include "recipe.h"
#include "product.h"
#include "favfood.h"
#include "hatefood.h"
#include "adddish.h"

////QT INCLUDES////
#include <QMainWindow>
#include <QTableView>
#include <QTableWidget>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QDate>
#include <QSqlError>

////STD INCLUDES////
#include <fstream>
#include <sstream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/// <summary>
/// Класс с информацией о пользователе
/// </summary>
class User{
private:
    /// <summary>
    /// Значение отвечающее за имя пользователя
    /// </summary>
    std::string name;
    /// <summary>
    /// Значение отвечающее за возраст пользователя
    /// </summary>
    int age;
    /// <summary>
    /// Значение отвечающее за рост пользователя
    /// </summary>
    int height;
    /// <summary>
    /// Значение отвечающее за рост пользователя
    /// </summary>
    int weight;
    /// <summary>
    /// Значение отвечающее за пол пользователя :
    /// 0 - м, 1 - ж
    /// </summary>
    bool gender;
    /// <summary>
    /// Значение отвечающее за цель пользователя :
    /// 1 - сбросить, 2 - сохранить, 3 - набрать
    /// </summary>
    int goal;
    /// <summary>
    /// Значение отвечающее за суточную потребность в калориях
    /// </summary>
    double AMR;
    /// <summary>
    /// Значение отвечающее за уровень активности пользователя:
    /// 1 - маленькая, 2 - умеренная, 3 - средняя, 5 - большая, 6 - спортсмен
    /// </summary>
    int active;

public:
    /// <summary>
    /// Значение отвечающее за необходимое к употреблению количество калорий в день
    /// </summary>
    int daily_calorie_intake;
    /// <summary>
    /// Значение отвечающее за необходимое к употреблению количество белков в г
    /// </summary>
    double protein;
    /// <summary>
    /// Значение отвечающее за необходимое к употреблению количество жиров в г
    /// </summary>
    double fat;
    /// <summary>
    /// Значение отвечающее за необходимое к употреблению количество углеводов в г
    /// </summary>
    double carbs;
    /// <summary>
    /// Конструктор класса User, создает объект User и заполняет поле имя (из аргументов)
    /// </summary>
    /// <param name="name">Имя пользователя</param>
    User(std::string name);
    /// <summary>
    /// Метод, использующийся для заполнения информации о пользователе,
    /// так же заполняет поле суточной потребности в калориях,
    /// а так же вызывает метод подсчета ежедневной нормы калорий и метод подсчета ежедневной нормы бжу
    /// </summary>
    /// <param name="age">Возраст пользователя</param>
    /// <param name="height">Рост пользователя</param>
    /// <param name="weight">Вес пользователя</param>
    /// <param name="gender">Пол пользователя</param>
    /// <param name="active">Активность пользователя</param>
    /// <param name="goal">Цель пользователя</param>
    void info(int age, int height, int weight, bool gender, int active, int goal);
    /// <summary>
    /// Метод, использующийся для подсчета необходимого к употреблению количества калорий в день,
    /// заполняет поле, отвечающее за необходимое к употреблению количество калорий в день
    /// </summary>
    void daily_calorie();
    /// <summary>
    /// Метод, использующийся для подсчета необходимых к употреблению количества бжу в день,
    /// заполняет поля, отвечающие за необходимое к употреблению количество бжу в день
    /// </summary>
    void cbgu_norma();
};

/// <summary>
/// Главный класс, отображающий графический интерфейс и содержащий в себе обработчики пользовательского ввода и функционал работы с базой данных
/// </summary>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /// <summary>
    /// Конструктор класса MainWindow. В аргументы конструктора можно передать указатель на родительский класс,
    /// что передаст управление памятью экземпляру родительского класса. В конструкторе происходит создание баз данных,
    /// заполнение таблиц при первом запуске
    /// </summary>
    /// <param name="parent">Указатель на родительский класс</param>
    MainWindow(QWidget *parent = nullptr);
    /// <summary>
    /// Деструктор класса MainWindow. Удаляет динамически выделенную память.
    /// </summary>
    ~MainWindow();


private slots:
    /// <summary>
    /// Метод, использующийся для открытия окна для создания нового продукта
    /// </summary>
    void on_pushButton_3_clicked();
    /// <summary>
    /// Метод, использующийся для открытия окна для создания нового рецепта
    /// </summary>
    void on_pushButton_4_clicked();
    /// <summary>
    /// Метод, использующийся для открытия окна с дополнительной информацией о продукте
    /// </summary>
    /// <param name="index">Индекс продукта, информацию о котором мы хотим посмотреть</param>
    void on_prod_table_doubleClicked(const QModelIndex &index);
    /// <summary>
    /// Метод, использующийся для сохранения выбранного пола
    /// </summary>
    /// <param name="index">Индекс выбранного пола</param>
    void on_comboBox_currentIndexChanged(int index);
    /// <summary>
    /// Метод, использующийся для сохранения выбранного уровня физической активности
    /// </summary>
    /// <param name="index">Индекс выбранного уровня физической активности</param>
    void on_comboBox_2_currentIndexChanged(int index);
    /// <summary>
    /// Метод, использующийся для обновления данных о пользователе
    /// </summary>
    void on_pushButton_9_clicked();
    /// <summary>
    /// Метод, использующийся для открытия окна для изменения списка любимых продуктов
    /// </summary>
    void on_pushButton_10_clicked();
    /// <summary>
    /// Метод, использующийся для открытия окна для изменения списка нелюбимых продуктов
    /// </summary>
    void on_pushButton_11_clicked();
    /// <summary>
    /// Метод, использующийся для сохранения выбранной цели
    /// </summary>
    /// <param name="index">Индекс выбранной цели</param>
    void on_comboBox_3_currentIndexChanged(int index);
    /// <summary>
    /// Метод, использующийся для открытия окна с дополнительной информацией о рецепте
    /// </summary>
    /// <param name="index">Индекс рецепта, информацию о котором мы хотим посмотреть</param>
    void on_tableRecipes_doubleClicked(const QModelIndex &index);
    /// <summary>
    /// Метод, использующийся для обновления бд с принятыми продуктами на завтрак, обед, ужин или перекус в зависимости от выбранной даты
    /// </summary>
    /// <param name="dateString">Дата принятия пищи</param>
    /// <param name="time">Время принятия пищи</param>
    void table_update(QString dateString, QString time);
    /// <summary>
    /// Метод, использующийся для сохранения выбранной даты на календаре
    /// </summary>
    /// <param name="date"></param>
    void on_calendarWidget_activated(const QDate &date);
    /// <summary>
    /// Метод, использующийся для сохранения номера выбранного элемента в таблице завтрак
    /// </summary>
    /// <param name="index">Индекс выбранного приема пищи</param>
    void on_tableViewbreakfast_clicked(const QModelIndex &index);
    /// <summary>
    /// Метод, использующийся для сохранения номера выбранного элемента в таблице обед
    /// </summary>
    /// <param name="index">Индекс выбранного приема пищи</param>
    void on_tableViewlunch_clicked(const QModelIndex &index);
    /// <summary>
    /// Метод, использующийся для сохранения номера выбранного элемента в таблице ужин
    /// </summary>
    /// <param name="index">Индекс выбранного приема пищи</param>
    void on_tableViewdinner_clicked(const QModelIndex &index);
    /// <summary>
    /// Метод, использующийся для сохранения номера выбранного элемента в таблице перекус
    /// </summary>
    /// <param name="index">Индекс выбранного приема пищи</param>
    void on_tableViewsnack_clicked(const QModelIndex &index);
    /// <summary>
    /// Метод, использующийся для удаления принятой пищи на завтрак
    /// </summary>
    void on_pushButton_clicked();
    /// <summary>
    /// Метод, использующийся для удаления принятой пищи на обед
    /// </summary>
    void on_pushButton_2_clicked();
    /// <summary>
    /// Метод, использующийся для удаления принятой пищи на ужин
    /// </summary>
    void on_pushButton_12_clicked();
    /// <summary>
    /// Метод, использующийся для удаления принятой пищи на перекус
    /// </summary>
    void on_pushButton_13_clicked();
    /// <summary>
    /// Метод, использующийся для добавления принятой пищи на завтрак
    /// </summary>
    void on_pushButton_5_clicked();
    /// <summary>
    /// Метод, использующийся для добавления принятой пищи на обед
    /// </summary>
    void on_pushButton_6_clicked();
    /// <summary>
    /// Метод, использующийся для добавления принятой пищи на ужин
    /// </summary>
    void on_pushButton_7_clicked();
    /// <summary>
    /// Метод, использующийся для добавления принятой пищи на перекус
    /// </summary>
    void on_pushButton_8_clicked();
    /// <summary>
    /// Метод, использующийся для обновления показываемых таблиц в зависимости от нынешней даты
    /// </summary>
    void time_up();
    /// <summary>
    /// Метод, использующийся для реализации sql запроса из файла
    /// </summary>
    /// <param name="file_name">Имя файла</param>
    void addbd(std::string file_name);

private:
    /// <summary>
    /// Поле, хранящее указатель на экземпляр, отвечающий за графический интерфейс и его элементы
    /// </summary>
    Ui::MainWindow *ui;
    /// <summary>
    /// Поле, хранящее в себе базу данных
    /// </summary>
    QSqlDatabase db;
    /// <summary>
    /// Поле, хранящее в себе выбранную в календаре дату
    /// </summary>
    QDate todays_date;
    /// <summary>
    /// Поле, хранящее в себе указатель на запрос создания таблицы продуктов
    /// </summary>
    QSqlQuery *queryProd;
    /// <summary>
    /// Поле, хранящее в себе указатель на модель таблицы продуктов
    /// </summary>
    QSqlTableModel *modelProd;
    /// <summary>
    /// Поле, хранящее в себе указатель на запрос создания таблицы рецептов
    /// </summary>
    QSqlQuery *query_recipes;
    /// <summary>
    /// Поле, хранящее в себе указатель на модель таблицы рецептов
    /// </summary>
    QSqlTableModel *model_recipes;
    /// <summary>
    /// Поле, хранящее в себе указатель на окно, создания продукта
    /// </summary>
    Create_prod *w;
    /// <summary>
    /// Поле, хранящее в себе указатель на окно, создания рецепта
    /// </summary>
    create_recipe *w1;
    /// <summary>
    /// Поле, хранящее в себе указатель на окно подробной информации о рецепте
    /// </summary>
    Recipe *w2;
    /// <summary>
    /// Поле, хранящее в себе указатель на окно подробной информации о продукте
    /// </summary>
    Product *w3;
    /// <summary>
    /// Поле, хранящее в себе указатель на окно редактирования любимых продуктов
    /// </summary>
    FavFood *wFF;
    /// <summary>
    /// Поле, хранящее в себе указатель на окно редактирования нелюбимых продуктов
    /// </summary>
    HateFood *wHF;
    /// <summary>
    /// Поле, хранящее в себе указатель на окно добавления съеденной пищи
    /// </summary>
    AddDish *wAdd;
    /// <summary>
    /// Поле, хранящее в себе указатель на запрос создания таблицы с любимыми продуктами
    /// </summary>
    QSqlQuery *queryFavFood;
    /// <summary>
    /// Поле, хранящее в себе указатель на модель с любимыми продуктами
    /// </summary>
    QSqlTableModel *modelFavFood;
    /// <summary>
    /// Поле, хранящее в себе указатель на запрос создания таблицы с ненавистными продуктами
    /// </summary>
    QSqlQuery *queryHateFood;
    /// <summary>
    /// Поле, хранящее в себе указатель на модель с ненавистными продуктами
    /// </summary>
    QSqlTableModel *modelHateFood;
    QSqlQuery *queryUser;
    QSqlQuery *queryUserDrop;
    QSqlQuery *queryUserIn;
    QSqlQuery *queryUser1;
    /// <summary>
    /// Поле, хранящее в себе указанное пользователем имя
    /// </summary>
    std::string tmp_name;
    /// <summary>
    /// Поле, хранящее в себе указанный пользователем возраст
    /// </summary>
    int tmp_age;
    /// <summary>
    /// Поле, хранящее в себе указанный пользователем рост
    /// </summary>
    int tmp_height;
    /// <summary>
    /// Поле, хранящее в себе указанный пользователем вес
    /// </summary>
    int tmp_weight;
    /// <summary>
    /// Поле, хранящее в себе указанный пользователем пол
    /// </summary>
    bool tmp_gender;
    /// <summary>
    /// Поле, хранящее в себе указанную пользователем цель
    /// </summary>
    int tmp_goal;
    /// <summary>
    /// Поле, хранящее в себе указанную пользователем активность
    /// </summary>
    int tmp_active;
    /// <summary>
    /// Поле, хранящее в себе указатель на запрос создания таблицы с завтраками
    /// </summary>
    QSqlQuery *breakfastTableQuery;
    /// <summary>
    /// Поле, хранящее в себе указатель на запрос создания таблицы с обедами
    /// </summary>
    QSqlQuery *lunchTableQuery;
    /// <summary>
    /// Поле, хранящее в себе указатель на запрос создания таблицы с ужинами
    /// </summary>
    QSqlQuery *dinnerTableQuery;
    /// <summary>
    /// Поле, хранящее в себе указатель на запрос создания таблицы с перекусами
    /// </summary>
    QSqlQuery *snackTableQuery;
    /// <summary>
    /// Поле, хранящее в себе указатель на модель таблицы с завтраками
    /// </summary>
    QSqlTableModel *modelbreakfast;
    /// <summary>
    /// Поле, хранящее в себе указатель на модель таблицы с обедами
    /// </summary>
    QSqlTableModel *modellunch;
    /// <summary>
    /// Поле, хранящее в себе указатель на модель таблицы с ужинами
    /// </summary>
    QSqlTableModel *modeldinner;
    /// <summary>
    /// Поле, хранящее в себе указатель на модель таблицы с перекусами
    /// </summary>
    QSqlTableModel *modelsnack;
    QSqlQuery *query;
    QSqlQuery *queryadd;
    QSqlQuery *queryDBin;
    QSqlQuery *queryDBin1;
    /// <summary>
    /// Поле, хранящее в себе номер выбранной строки в таблице завтрак
    /// </summary>
    int row;
    /// <summary>
    /// Поле, хранящее в себе номер выбранной строки в таблице обед
    /// </summary>
    int row1;
    /// <summary>
    /// Поле, хранящее в себе номер выбранной строки в таблице ужин
    /// </summary>
    int row2;
    /// <summary>
    /// Поле, хранящее в себе номер выбранной строки в таблице перекус
    /// </summary>
    int row3;
    /// <summary>
    /// Поле, хранящее в себе съеденные калории за день в г
    /// </summary>
    int Calories;
    /// <summary>
    /// Поле, хранящее в себе съеденные углеводы за день в г
    /// </summary>
    double Carbohydrate;
    /// <summary>
    /// Поле, хранящее в себе съеденные белки за день в г
    /// </summary>
    double Protein;
    /// <summary>
    /// Поле, хранящее в себе съеденные жиры за день в г
    /// </summary>
    double Fat;

};
#endif // MAINWINDOW_H
