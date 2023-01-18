#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

#include "create_prod.h"
#include "create_recipe.h"
#include "recipe.h"
#include "product.h"
#include "favfood.h"
#include "hatefood.h"
#include "adddish.h"

////STD INCLUDES////
#include <fstream>
#include <sstream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/// <summary>
/// Класс, экземпляр которого содержит в себе необходимую информацию о каком-либо товаре
/// </summary>
class User{
private:
    std::string name;
    int age;
    int height;
    int weight;
    bool gender;
    int goal;
    double AMR;
    int active;

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

    void addbd(std::string file_name);

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
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
    bool tmp_gender;
    int tmp_goal;
    int tmp_active;

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
    QSqlQuery *queryDBin;
    QSqlQuery *queryDBin1;

    int row;
    int row1;
    int row2;
    int row3;

    int Calories;
    double Carbohydrate;
    double Protein;
    double Fat;

};
#endif // MAINWINDOW_H
