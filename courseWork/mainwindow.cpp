#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tmp_name = "Name";
    tmp_age = 21;
    tmp_height = 160;
    tmp_weight = 65;
    tmp_gender = 1; //0 - мужской пол, 1 - женский пол
    tmp_goal = 2; //1 - сбросить, 2 - сохранить, 3 - набрать
    tmp_active = 2;
    //1 - Сидячий образ жизни, 2 - Умеренная активность, 3 - Средняя(занятия 3 - 5 раз в неделю), 4 - Активные люди(интенсивные нагрузки), 5 - Спортсмены(6 - 7 раз в неделю)

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./testDB.db");
    if(db.open()){
        qDebug("Open");
    }else{
        qDebug("No open");
    }
    query_recipes = new QSqlQuery(db);
    query_recipes -> exec("CREATE TABLE Recipes(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, recipe TEXT, calories INT, protein REAL, fat REAL, carbohydrate REAL);");
    queryProd = new QSqlQuery(db);
    queryProd -> exec("CREATE TABLE Products(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, calories INT, protein REAL, fat REAL, carbohydrate REAL);");
    queryFavFood = new QSqlQuery(db);
    queryFavFood -> exec("CREATE TABLE FavFood(id INTEGER PRIMARY KEY AUTOINCREMENT, product_id INTEGER, name TEXT);");
    queryHateFood = new QSqlQuery(db);
    queryHateFood -> exec("CREATE TABLE HateFood(id INTEGER PRIMARY KEY AUTOINCREMENT, product_id INTEGER, name TEXT);");
    queryUser = new QSqlQuery(db);
    queryUser -> exec("CREATE TABLE User(name TEXT, age INTEGER, height REAL, weight INTEGER, gender INTEGER, goal INTEGER, active INTEGER, daily_calorie_intake INTEGER, protein REAL, fat REAL, carbs REAL);");


    model_recipes = new QSqlTableModel(this, db);
    model_recipes ->setTable("Recipes");
    model_recipes->setHeaderData(1, Qt::Horizontal, QObject::tr("Название"));
    model_recipes->setHeaderData(2, Qt::Horizontal, QObject::tr("Рецепт"));
    model_recipes->setHeaderData(3, Qt::Horizontal, QObject::tr("Калории"));
    model_recipes->setHeaderData(4, Qt::Horizontal, QObject::tr("Белки"));
    model_recipes->setHeaderData(5, Qt::Horizontal, QObject::tr("Жиры"));
    model_recipes->setHeaderData(6, Qt::Horizontal, QObject::tr("Углеводы"));
    model_recipes->select();
    ui->tableRecipes->setModel(model_recipes);
    ui->tableRecipes->setColumnHidden(0, true);
    ui->tableRecipes->setColumnHidden(2, true);
    ui->tableRecipes->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    modelProd = new QSqlTableModel(this, db);
    modelProd->setTable("Products");
    modelProd->setHeaderData(1, Qt::Horizontal, QObject::tr("Название"));
    modelProd->select();
    ui->prod_table->setModel(modelProd);
    ui->prod_table->setColumnHidden(0, true);
    for(int i = 2; i<=5; ++i){
        ui->prod_table->setColumnHidden(i, true);
    }

    modelFavFood = new QSqlTableModel(this, db);
    modelFavFood ->setTable("FavFood");
    modelFavFood->setHeaderData(2, Qt::Horizontal, QObject::tr("Название"));
    modelFavFood->select();
    ui->tableView_3->setModel(modelFavFood);
    ui->tableView_3->setColumnHidden(0, true);
    ui->tableView_3->setColumnHidden(1, true);
    ui->tableView_3->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    modelFavFood = new QSqlTableModel(this, db);
    modelFavFood ->setTable("HateFood");
    modelFavFood->setHeaderData(2, Qt::Horizontal, QObject::tr("Название"));
    modelFavFood->select();
    ui->tableView_4->setModel(modelFavFood);
    ui->tableView_4->setColumnHidden(0, true);
    ui->tableView_4->setColumnHidden(1, true);
    ui->tableView_4->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    if(db.open()){
        qDebug("Open");
    }else{
        qDebug("No open");
    }
    QSqlQuery queryUser1("SELECT name, age, height, weight, gender, goal, active, daily_calorie_intake, protein, fat, carbs FROM User;");
    while (queryUser1.next()) {
        ui->textEdit->clear();
        ui->textEdit_4->clear();
        ui->textEdit_3->clear();
        ui->textEdit_2->clear();
        ui->textEdit_4->clear();
        ui->textBrowser_13->clear();
        ui->textBrowser_14->clear();
        QString tmp_str;
        tmp_str = QString(queryUser1.value(0).toString());
        ui->textEdit->setText(tmp_str);
        tmp_str = QString(queryUser1.value(1).toString());
        ui->textEdit_4->insertPlainText(tmp_str);
        tmp_str = QString(queryUser1.value(2).toString());
        ui->textEdit_3->insertPlainText(tmp_str);
        tmp_str = QString(queryUser1.value(3).toString());
        ui->textEdit_2->insertPlainText(tmp_str);
        ui->comboBox->setCurrentIndex(queryUser1.value(4).toInt());
        ui->comboBox_3->setCurrentIndex(queryUser1.value(5).toInt());
        ui->comboBox_2->setCurrentIndex(queryUser1.value(6).toInt());
        tmp_str = "Твоя норма калорий в день :  " + QString::number(queryUser1.value(7).toDouble());
        ui->textBrowser_13->insertPlainText(tmp_str);
        tmp_str = "Необходимое бжу на день : белки - " + QString::number(queryUser1.value(8).toDouble()) + " г, жиры - " + QString::number(queryUser1.value(9).toDouble()) + " г, углеводы - " + QString::number(queryUser1.value(10).toDouble()) + " г";
        ui->textBrowser_14->insertPlainText(tmp_str);

    }

    w = new Create_prod(this);
    wFF = new FavFood(this);
    wHF = new HateFood(this);

    if (db.open()) {
        qDebug("Database opened successfully");
    } else {
        qDebug("Failed to open database");
    }
    breakfastTableQuery = new QSqlQuery(db);
    breakfastTableQuery->exec("CREATE TABLE breakfast (recipe_id INTEGER, quantity INTEGER, time DATETIME);");
    lunchTableQuery = new QSqlQuery(db);
    lunchTableQuery->exec("CREATE TABLE lunch (recipe_id INTEGER, quantity INTEGER, time DATETIME);");
    dinnerTableQuery = new QSqlQuery(db);
    dinnerTableQuery->exec("CREATE TABLE dinner (recipe_id INTEGER, quantity INTEGER, time DATETIME);");
    snackTableQuery = new QSqlQuery(db);
    snackTableQuery->exec("CREATE TABLE snack (recipe_id INTEGER, quantity INTEGER, time DATETIME);");

    todays_date = QDate::currentDate();
    MainWindow::on_calendarWidget_activated(todays_date);

    row = -1;
    row1 = -1;
    row2 = -1;
    row3 = -1;
}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}

User::User(std::string name) {
    this->name = name;
    this->age = 21;
    this->height = 160;
    this->weight = 65;
    this->gender = 1; //Девушка
    this->goal = 2;
    this->active = 2;
    daily_calorie();
    cbgu_norma();
}

void User::info(int age, int height, int weight, bool gender, int active, int goal) {
    this->age = age;
    this->height = height;
    this->weight = weight;
    this->gender = gender;
    this->goal = goal;
    //AMR подсчет в зависимости от активности
    if (1) {
        if (active == 0) {
            AMR = 0.8; //для худеющих
        }
        else if (active == 1) {
            AMR = 1.2; //Сидячий образ жизни
        }
        else if (active == 2) {
            AMR = 1.375; //Умеренная активность
        }
        else if (active == 3) {
            AMR = 1.55; //Средняя(занятия 3 - 5 раз в неделю)
        }
        else if (active == 4) {
            AMR = 1.725; //Активные люди(интенсивные нагрузки)
        }
        else if (active == 5) {
            AMR = 1.9; //Спортсмены(6 - 7 раз в неделю)
        }
    }
    daily_calorie();
    cbgu_norma();
}

void User::daily_calorie() { //Формула Харриса-Беннедикта
    double BMR = 0.0;
    if (gender == 1) {
        BMR = 447.593 + (9.247 * weight) + (3.098 * height) - (4.330 * age);
    }
    else {
        BMR = 88.362 + (13.397 * weight) + (4.799 * height) - (5.677 * age);
    }
    daily_calorie_intake = BMR * AMR;
    if (1) {
        if (goal == 1) {
            daily_calorie_intake = daily_calorie_intake * 0.85;
        }
        if (goal == 3) {
            daily_calorie_intake = daily_calorie_intake * 1.15;
        }
    }
}

void User::cbgu_norma() {
    double TDEE = daily_calorie_intake;
    // Расчет рекомендуемого соотношения белков, жиров и углеводов в граммах
    if (goal == 2) {
        protein = TDEE * 0.15;
        fat = TDEE * 0.25;
        carbs = TDEE * 0.6;
    }
    else if (goal == 1) {
        protein = TDEE * 0.2;
        fat = TDEE * 0.25;
        carbs = TDEE * 0.55;
    }
    else if (goal == 3) {
        protein = TDEE * 0.3;
        fat = TDEE * 0.2;
        carbs = TDEE * 0.5;
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    w->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    w1 = new create_recipe(this, modelProd->rowCount());
    w1->show();
}

void MainWindow::on_prod_table_doubleClicked(const QModelIndex &index)
{
    w3 = new Product(this, index.row());
    w3->show();
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    index--;
    tmp_gender = index;
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    tmp_active = index;
}

void MainWindow::on_pushButton_9_clicked() //update
{
    QString name = ui->textEdit->toPlainText();
    tmp_name = name.toStdString();
    User user = User(tmp_name);
    tmp_age = ui->textEdit_4->toPlainText().toInt();
    tmp_weight = ui->textEdit_2->toPlainText().toInt();
    tmp_height = ui->textEdit_3->toPlainText().toInt();
    user.info(tmp_age, tmp_height, tmp_weight, tmp_gender, tmp_active, tmp_goal); // tmp_gender ++

    ui->textBrowser_13->clear();
    QString tmp_browser = "Твоя норма калорий в день :  " + QString::number(user.daily_calorie_intake);
    ui->textBrowser_13->insertPlainText(tmp_browser);

    ui->textBrowser_14->clear();
    QString tmp1_browser = "Необходимое бжу на день : белки - " + QString::number(user.protein) + " г, жиры - " + QString::number(user.fat) + " г, углеводы - " + QString::number(user.carbs) + " г";
    ui->textBrowser_14->insertPlainText(tmp1_browser);

    if(db.open()){
        qDebug("Open");
    }else{
        qDebug("No open");
    }
    queryUserDrop = new QSqlQuery(db);
    queryUserDrop -> exec("DROP TABLE IF EXISTS User;");
    queryUser = new QSqlQuery(db);
    queryUser -> exec("CREATE TABLE User(name TEXT, age INTEGER, height REAL, weight INTEGER, gender INTEGER, goal INTEGER, active INTEGER, daily_calorie_intake INTEGER, protein REAL, fat REAL, carbs REAL);");
    queryUserIn = new QSqlQuery(db);
    queryUserIn->prepare("INSERT INTO User(name, age, height, weight, gender, goal, active, daily_calorie_intake, protein, fat, carbs) "
                  "VALUES (:name, :age, :height, :weight, :gender, :goal, :active, :daily_calorie_intake, :protein, :fat, :carbs)");
    queryUserIn->bindValue(0, name);
    queryUserIn->bindValue(1, tmp_age);
    queryUserIn->bindValue(2, tmp_height);
    queryUserIn->bindValue(3, tmp_weight);
    queryUserIn->bindValue(4, tmp_gender+1);
    queryUserIn->bindValue(5, tmp_goal);
    queryUserIn->bindValue(6, tmp_active);
    queryUserIn->bindValue(7, user.daily_calorie_intake);
    queryUserIn->bindValue(8, user.protein);
    queryUserIn->bindValue(9, user.fat);
    queryUserIn->bindValue(10, user.carbs);
    queryUserIn->exec();

    /*
    std::ofstream fin;
    fin.open("tmp.txt");
    fin <<  ;
    fin.close();
    */


}

void MainWindow::on_pushButton_10_clicked()
{
    wFF->show();
}

void MainWindow::on_pushButton_11_clicked()
{
    wHF->show();
}

void MainWindow::on_comboBox_3_currentIndexChanged(int index)
{
    tmp_goal = index;
}

void MainWindow::on_tableRecipes_doubleClicked(const QModelIndex &index)
{
    w2 = new Recipe(this, index.row());
    w2->show();

}

void MainWindow::on_calendarWidget_activated(const QDate &date)
{
    QString dateString = date.toString("yyyy-MM-dd");
    QString tmp_query = "SELECT breakfast.recipe_id, Recipes.name, breakfast.count FROM Recipes, breakfast WHERE (Recipes.id = breakfast.recipe_id AND breakfast.time = '" + dateString + "');";

    if(db.open()){
        qDebug("Open");
    }else{
        qDebug("No open");
    }
    queryDate = new QSqlQuery(db);
    queryDate->exec(tmp_query);
    queryDate1 = new QSqlQuery(db);
    queryDate1 -> exec("DROP TABLE IF EXISTS tmp_breakfast;");
    queryDate1->clear();
    queryDate1 -> exec("CREATE TABLE tmp_breakfast (id INTEGER PRIMARY KEY AUTOINCREMENT, recipe_id INTEGER, name TEXT, count INTEGER);");

    while (queryDate->next()) {
        QString tmp = QString(queryDate->value(1).toString());

        if(db.open()){
            qDebug("Open");
        }else{
            qDebug("No open");
        }
        queryDate1->clear();
        queryDate1->prepare("INSERT INTO tmp_breakfast (recipe_id, name, count) "
                      "VALUES (:id, :name, :count)");
        queryDate1->bindValue(0, queryDate->value(0).toInt());
        queryDate1->bindValue(1, tmp);
        queryDate1->bindValue(2, queryDate->value(2).toInt());
        queryDate1->exec();
    }

    modelDate = new QSqlTableModel(this, db);
    modelDate ->setTable("tmp_breakfast");  //dinner, snack
    ui->tableView->setModel(modelDate);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->setColumnHidden(1, true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->update();
    // recipe_id INTEGER, quantity INTEGER, time DATETIME

    tmp_query = "SELECT lunch.recipe_id, Recipes.name, lunch.count FROM Recipes, lunch WHERE (Recipes.id = lunch.recipe_id AND lunch.time = '" + dateString + "');";

    if(db.open()){
        qDebug("Open");
    }else{
        qDebug("No open");
    }
    queryDate->clear();
    queryDate->exec(tmp_query);
    queryDate1->clear();
    queryDate1 -> exec("DROP TABLE IF EXISTS tmp_lunch;");
    queryDate1->clear();
    queryDate1 -> exec("CREATE TABLE tmp_lunch (id INTEGER PRIMARY KEY AUTOINCREMENT, recipe_id INTEGER, name TEXT, count INTEGER);");

    while (queryDate->next()) {
        QString tmp = QString(queryDate->value(1).toString());

        if(db.open()){
            qDebug("Open");
        }else{
            qDebug("No open");
        }
        queryDate1->clear();
        queryDate1->prepare("INSERT INTO tmp_lunch (recipe_id, name, count) "
                      "VALUES (:id, :name, :count)");
        queryDate1->bindValue(0, queryDate->value(0).toInt());
        queryDate1->bindValue(1, tmp);
        queryDate1->bindValue(2, queryDate->value(2).toInt());
        queryDate1->exec();
    }

    modelDate1 = new QSqlTableModel(this, db);
    modelDate1 ->setTable("tmp_lunch");  //dinner, snack
    ui->tableView_2->setModel(modelDate1);
    ui->tableView_2->setColumnHidden(0, true);
    ui->tableView_2->setColumnHidden(1, true);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView_2->update();

    tmp_query = "SELECT dinner.recipe_id, Recipes.name, dinner.count FROM Recipes, dinner WHERE (Recipes.id = dinner.recipe_id AND dinner.time = '" + dateString + "');";

    if(db.open()){
        qDebug("Open");
    }else{
        qDebug("No open");
    }
    queryDate->clear();
    queryDate->exec(tmp_query);
    queryDate1->clear();
    queryDate1 -> exec("DROP TABLE IF EXISTS tmp_dinner;");
    queryDate1->clear();
    queryDate1 -> exec("CREATE TABLE tmp_dinner (id INTEGER PRIMARY KEY AUTOINCREMENT, recipe_id INTEGER, name TEXT, count INTEGER);");

    while (queryDate->next()) {
        QString tmp = QString(queryDate->value(1).toString());

        if(db.open()){
            qDebug("Open");
        }else{
            qDebug("No open");
        }
        queryDate1->clear();
        queryDate1->prepare("INSERT INTO tmp_dinner (recipe_id, name, count) "
                      "VALUES (:id, :name, :count)");
        queryDate1->bindValue(0, queryDate->value(0).toInt());
        queryDate1->bindValue(1, tmp);
        queryDate1->bindValue(2, queryDate->value(2).toInt());
        queryDate1->exec();
    }

    modelDate2 = new QSqlTableModel(this, db);
    modelDate2 ->setTable("tmp_dinner");  //dinner, snack
    ui->tableView_5->setModel(modelDate2);
    ui->tableView_5->setColumnHidden(0, true);
    ui->tableView_5->setColumnHidden(1, true);
    ui->tableView_5->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView_5->update();

    tmp_query = "SELECT snack.recipe_id, Recipes.name, snack.count FROM Recipes, snack WHERE (Recipes.id = snack.recipe_id AND snack.time = '" + dateString + "');";

    if(db.open()){
        qDebug("Open");
    }else{
        qDebug("No open");
    }
    queryDate->clear();
    queryDate->exec(tmp_query);
    queryDate1->clear();
    queryDate1 -> exec("DROP TABLE IF EXISTS tmp_snack;");
    queryDate1->clear();
    queryDate1 -> exec("CREATE TABLE tmp_snack (id INTEGER PRIMARY KEY AUTOINCREMENT, recipe_id INTEGER, name TEXT, count INTEGER);");

    while (queryDate->next()) {
        QString tmp = QString(queryDate->value(1).toString());

        if(db.open()){
            qDebug("Open");
        }else{
            qDebug("No open");
        }
        queryDate1->clear();
        queryDate1->prepare("INSERT INTO tmp_snack (recipe_id, name, count) "
                      "VALUES (:id, :name, :count)");
        queryDate1->bindValue(0, queryDate->value(0).toInt());
        queryDate1->bindValue(1, tmp);
        queryDate1->bindValue(2, queryDate->value(2).toInt());
        queryDate1->exec();
    }

    modelDate3 = new QSqlTableModel(this, db);
    modelDate3 ->setTable("tmp_snack");  //dinner, snack
    ui->tableView_6->setModel(modelDate3);
    ui->tableView_6->setColumnHidden(0, true);
    ui->tableView_6->setColumnHidden(1, true);
    ui->tableView_6->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView_6->update();
}


void MainWindow::on_pushButton_5_clicked()
{
    QString dateString = todays_date.toString("yyyy-MM-dd");
    QString time = "breakfast";
    wAdd = new AddDish(this, ui, modelDate->rowCount(), dateString, time);
    wAdd->show();
    //modelDate->insertRow(modelDate->rowCount());
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}


void MainWindow::on_tableView_2_clicked(const QModelIndex &index)
{
    row1 = index.row();
}


void MainWindow::on_tableView_5_clicked(const QModelIndex &index)
{
    row2 = index.row();
}


void MainWindow::on_tableView_6_clicked(const QModelIndex &index)
{
    row3 = index.row();
}


void MainWindow::on_pushButton_clicked()
{
    if(row!=-1){
    modelDate->removeRow(row);
    ui->tableView->update();}
}


void MainWindow::on_pushButton_2_clicked()
{
    if(row1!=-1){
    modelDate1->removeRow(row1);
    ui->tableView_2->update();}
}


void MainWindow::on_pushButton_12_clicked()
{
    if(row2!=-1){
    modelDate2->removeRow(row2);
    ui->tableView_5->update();}
}


void MainWindow::on_pushButton_13_clicked()
{
    if(row3!=-1){
    modelDate3->removeRow(row3);
    ui->tableView_6->update();}
}
