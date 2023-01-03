#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QDate>
#include <QSqlError>

#include "create_prod.h"
#include "create_recipe.h"
#include "recipe.h"
#include "product.h"
#include "favfood.h"
#include "hatefood.h"
#include "adddish.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class User{
private:
    std::string name;
    int age;
    int height;
    int weight;
    bool gender; //0 - мужской пол, 1 - женский пол
    int goal; //1 - сбросить, 2 - сохранить, 3 - набрать
    double AMR;
    int active;
    //1 - Сидячий образ жизни, 2 - Умеренная активность, 3 - Средняя(занятия 3 - 5 раз в неделю), 5 - Активные люди(интенсивные нагрузки), 6 - Спортсмены(6 - 7 раз в неделю)

public:
    int daily_calorie_intake;
    double protein;
    double fat;
    double carbs;

    User(std::string name);

    void info(int age, int height, int weight, bool gender, int active, int goal);
    void daily_calorie();
    void cbgu_norma();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSqlDatabase db;

private slots:

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_prod_table_doubleClicked(const QModelIndex &index);

    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_2_currentIndexChanged(int index);

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_comboBox_3_currentIndexChanged(int index);

    void on_tableRecipes_doubleClicked(const QModelIndex &index);

    void table_update(QString dateString, QString time);

    void on_calendarWidget_activated(const QDate &date);

    void on_tableViewbreakfast_clicked(const QModelIndex &index);

    void on_tableViewlunch_clicked(const QModelIndex &index);

    void on_tableViewdinner_clicked(const QModelIndex &index);

    void on_tableViewsnack_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void time_up();

private:
    Ui::MainWindow *ui;
    QDate todays_date;

    QSqlQuery *queryProd;
    QSqlTableModel *modelProd;
    QSqlQuery *query_recipes;
    QSqlTableModel *model_recipes;
    Create_prod *w;
    create_recipe *w1;
    Recipe *w2;
    Product *w3;
    FavFood *wFF;
    HateFood *wHF;
    AddDish *wAdd;

    QSqlQuery *queryFavFood;
    QSqlTableModel *modelFavFood;
    QSqlQuery *queryHateFood;
    QSqlTableModel *modelHateFood;

    QSqlQuery *queryUser;
    QSqlQuery *queryUserDrop;
    QSqlQuery *queryUserIn;
    QSqlQuery *queryUser1;

    std::string tmp_name;
    int tmp_age;
    int tmp_height;
    int tmp_weight;
    bool tmp_gender; //0 - мужской пол, 1 - женский
    int tmp_goal; //1 - сбросить, 2 - сохранить, 3 - набрать
    int tmp_active; //1 - Сидячий образ жизни, 2 - Умеренная активность, 3 - Средняя(занятия 3 - 5 раз в неделю), 4 - Активные люди(интенсивные нагрузки), 5 - Спортсмены(6 - 7 раз в неделю)

    QSqlQuery *breakfastTableQuery;
    QSqlQuery *lunchTableQuery;
    QSqlQuery *dinnerTableQuery;
    QSqlQuery *snackTableQuery;

    QSqlTableModel *modelbreakfast;
    QSqlTableModel *modellunch;
    QSqlTableModel *modeldinner;
    QSqlTableModel *modelsnack;

    QSqlQuery *query;
    QSqlQuery *queryadd;

    int row;
    int row1;
    int row2;
    int row3;
};
#endif // MAINWINDOW_H
