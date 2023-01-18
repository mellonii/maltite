#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <fstream>
#include <sstream>

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
        qDebug("No open: %s", qPrintable(db.lastError().text()));
    }
    query_recipes = new QSqlQuery(db);
    query_recipes -> exec("CREATE TABLE IF NOT EXISTS Recipes(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, recipe TEXT, ingredients TEXT, calories INT, protein REAL, fat REAL, carbohydrate REAL);");
    queryProd = new QSqlQuery(db);
    queryProd -> exec("CREATE TABLE IF NOT EXISTS Products(id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, calories INT, protein REAL, fat REAL, carbohydrate REAL);");
    queryFavFood = new QSqlQuery(db);
    queryFavFood -> exec("CREATE TABLE IF NOT EXISTS FavFood(id INTEGER PRIMARY KEY AUTOINCREMENT, product_id INTEGER, name TEXT);");
    queryHateFood = new QSqlQuery(db);
    queryHateFood -> exec("CREATE TABLE IF NOT EXISTS HateFood(id INTEGER PRIMARY KEY AUTOINCREMENT, product_id INTEGER, name TEXT);");
    queryUser = new QSqlQuery(db);
    queryUser -> exec("CREATE TABLE IF NOT EXISTS User(name TEXT, age INTEGER, height REAL, weight INTEGER, gender INTEGER, goal INTEGER, active INTEGER, daily_calorie_intake INTEGER, protein REAL, fat REAL, carbs REAL);");

    query_recipes = new QSqlQuery(db);
    query_recipes -> exec("SELECT id FROM Products;");
    if(query_recipes->next()){
    }else{
        std::string file_name = "products.txt";
        addbd(file_name);
        file_name = "recipes.txt";
        addbd(file_name);
    }

    model_recipes = new QSqlTableModel(this, db);
    model_recipes ->setTable("Recipes");
    model_recipes->setHeaderData(1, Qt::Horizontal, QObject::tr("Название"));
    model_recipes->setHeaderData(2, Qt::Horizontal, QObject::tr("Рецепт"));
    model_recipes->setHeaderData(4, Qt::Horizontal, QObject::tr("Калории"));
    model_recipes->setHeaderData(5, Qt::Horizontal, QObject::tr("Белки"));
    model_recipes->setHeaderData(6, Qt::Horizontal, QObject::tr("Жиры"));
    model_recipes->setHeaderData(7, Qt::Horizontal, QObject::tr("Углеводы"));
    model_recipes->select();
    ui->tableRecipes->setModel(model_recipes);
    ui->tableRecipes->setColumnHidden(0, true);
    ui->tableRecipes->setColumnHidden(2, true);
    ui->tableRecipes->setColumnHidden(3, true);
    ui->tableRecipes->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);


    modelProd = new QSqlTableModel(this, db);
    modelProd->setTable("Products");
    modelProd->setHeaderData(1, Qt::Horizontal, QObject::tr("Название"));
    modelProd->select();
    ui->prod_table->setModel(modelProd);
    ui->prod_table->setColumnHidden(0, true);
    ui->prod_table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
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
        qDebug("No open: %s", qPrintable(db.lastError().text()));
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
        qDebug("Failed to open database: %s", qPrintable(db.lastError().text()));
    }
    breakfastTableQuery = new QSqlQuery(db);
    breakfastTableQuery->exec("CREATE TABLE IF NOT EXISTS breakfast (id INTEGER PRIMARY KEY AUTOINCREMENT, recipe_id INTEGER, quantity INTEGER, time DATETIME);");
    lunchTableQuery = new QSqlQuery(db);
    lunchTableQuery->exec("CREATE TABLE IF NOT EXISTS lunch (id INTEGER PRIMARY KEY AUTOINCREMENT, recipe_id INTEGER, quantity INTEGER, time DATETIME);");
    dinnerTableQuery = new QSqlQuery(db);
    dinnerTableQuery->exec("CREATE TABLE IF NOT EXISTS dinner (id INTEGER PRIMARY KEY AUTOINCREMENT, recipe_id INTEGER, quantity INTEGER, time DATETIME);");
    snackTableQuery = new QSqlQuery(db);
    snackTableQuery->exec("CREATE TABLE IF NOT EXISTS snack (id INTEGER PRIMARY KEY AUTOINCREMENT, recipe_id INTEGER, quantity INTEGER, time DATETIME);");

    row = -1;
    row1 = -1;
    row2 = -1;
    row3 = -1;

    todays_date = QDate::currentDate();
    MainWindow::on_calendarWidget_activated(todays_date);


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

void MainWindow::on_pushButton_9_clicked()
{
    QString name = ui->textEdit->toPlainText();
    tmp_name = name.toStdString();
    User user = User(tmp_name);
    tmp_age = ui->textEdit_4->toPlainText().toInt();
    tmp_weight = ui->textEdit_2->toPlainText().toInt();
    tmp_height = ui->textEdit_3->toPlainText().toInt();
    user.info(tmp_age, tmp_height, tmp_weight, tmp_gender, tmp_active, tmp_goal);

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

void MainWindow::table_update(QString dateString, QString time){

    QString tmp_query = "SELECT " + time + ".id, " + time + ".recipe_id, Recipes.name, " + time + ".quantity FROM Recipes, " + time + " WHERE (Recipes.id = " + time + ".recipe_id AND " + time + ".time = '" + dateString + "');";
    QString tmp_drop = "DROP TABLE IF EXISTS tmp_" + time + ";";
    QString tmp_create = "CREATE TABLE tmp_" + time + " (dish_id INTEGER, id INTEGER PRIMARY KEY AUTOINCREMENT, recipe_id INTEGER, name TEXT, count INTEGER);";

    if(db.open()){
         qDebug("Open");
    }else{
         qDebug("No open");
    }
    query = new QSqlQuery(db);
    query->exec(tmp_drop);
    query ->clear();
    query->exec(tmp_create);
    query ->clear();
    query->prepare(tmp_query);
    query->exec();
    while(query->next()){
          tmp_query = "INSERT INTO tmp_" + time + " (dish_id, recipe_id, name, count) VALUES (:dish_id, :recipe_id, :name, :count)";
          if(db.open()){
               qDebug("Open");
          }else{
               qDebug("No open");
          }
          queryadd = new QSqlQuery(db);
          queryadd->prepare(tmp_query);
          queryadd->bindValue(0, query->value(0).toInt());
          queryadd->bindValue(1, query->value(1).toInt());
          queryadd->bindValue(2, query->value(2).toString());
          queryadd->bindValue(3, query->value(3).toInt());
          queryadd->exec();
}

    time_up();
}

void MainWindow::on_calendarWidget_activated(const QDate &date)
{

    QString dateString = date.toString("yyyy-MM-dd");
    todays_date = date;

    table_update(dateString, "breakfast");
    table_update(dateString, "lunch");
    table_update(dateString, "dinner");
    table_update(dateString, "snack");
}

void MainWindow::on_tableViewbreakfast_clicked(const QModelIndex &index)
{
    row = index.row();
}


void MainWindow::on_tableViewlunch_clicked(const QModelIndex &index)
{
    row1 = index.row();
}


void MainWindow::on_tableViewdinner_clicked(const QModelIndex &index)
{
    row2 = index.row();
}


void MainWindow::on_tableViewsnack_clicked(const QModelIndex &index)
{
    row3 = index.row();
}


void MainWindow::on_pushButton_clicked()
{
    if(row!=-1){
    modelbreakfast->removeRow(row);

    QString tmp_delete = "SELECT dish_id FROM tmp_breakfast WHERE id = " + QString::number(row + 1) + ";";
    query ->clear();
    query = new QSqlQuery(db);
    query->exec(tmp_delete);
    int dish_id = query->value(0).toInt();

    std::ofstream out;
        out.open("tmp.txt");
        if (out.is_open())
        {
           out << query->value(0).toInt();
        }
    out.close();

    tmp_delete = "DELETE FROM breakfast WHERE id = " + QString::number(dish_id) + ";";
    query ->clear();
    query = new QSqlQuery(db);
    query->exec(tmp_delete);

    }
    row = -1;

}


void MainWindow::on_pushButton_2_clicked()
{
    if(row1!=-1){
    modellunch->removeRow(row);}
    row1 = -1;
}


void MainWindow::on_pushButton_12_clicked()
{
    if(row2!=-1){
    modeldinner->removeRow(row);}
    row2 = -1;
}


void MainWindow::on_pushButton_13_clicked()
{
    if(row3!=-1){
    modelsnack->removeRow(row);}
    row3 = -1;
}

void MainWindow::on_pushButton_5_clicked()
{
    QString dateString = todays_date.toString("yyyy-MM-dd");
    QString time = "breakfast";
    wAdd = new AddDish(this, modelbreakfast->rowCount(), dateString, time);
    wAdd->show();
}

void MainWindow::on_pushButton_6_clicked()
{
    QString dateString = todays_date.toString("yyyy-MM-dd");
    QString time = "lunch";
    wAdd = new AddDish(this, modellunch->rowCount(), dateString, time);
    wAdd->show();
}


void MainWindow::on_pushButton_7_clicked()
{
    QString dateString = todays_date.toString("yyyy-MM-dd");
    QString time = "dinner";
    wAdd = new AddDish(this, modeldinner->rowCount(), dateString, time);
    wAdd->show();
}


void MainWindow::on_pushButton_8_clicked()
{
    QString dateString = todays_date.toString("yyyy-MM-dd");
    QString time = "snack";
    wAdd = new AddDish(this, modelsnack->rowCount(), dateString, time);
    wAdd->show();
}

void MainWindow::time_up(){
    if(db.open()){
          qDebug("Open");
    }else{
          qDebug("No open for bdls tableView: %s", qPrintable(db.lastError().text()));
    }

    modelbreakfast = new QSqlTableModel(this, db);
    modelbreakfast ->setTable("tmp_breakfast");
    modelbreakfast->setHeaderData(3, Qt::Horizontal, QObject::tr("Блюдо"));
    modelbreakfast->setHeaderData(4, Qt::Horizontal, QObject::tr("Количество (в г)"));
    modelbreakfast->select();
    ui->tableViewbreakfast->setModel(modelbreakfast);
    ui->tableViewbreakfast->setColumnHidden(0, true);
    ui->tableViewbreakfast->setColumnHidden(1, true);
    ui->tableViewbreakfast->setColumnHidden(2, true);
    ui->tableViewbreakfast->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    modellunch = new QSqlTableModel(this, db);
    modellunch ->setTable("tmp_lunch");
    modellunch->setHeaderData(3, Qt::Horizontal, QObject::tr("Блюдо"));
    modellunch->setHeaderData(4, Qt::Horizontal, QObject::tr("Количество (в г)"));
    modellunch->select();
    ui->tableViewlunch->setModel(modellunch);
    ui->tableViewlunch->setColumnHidden(0, true);
    ui->tableViewlunch->setColumnHidden(1, true);
    ui->tableViewlunch->setColumnHidden(2, true);
    ui->tableViewlunch->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    modeldinner = new QSqlTableModel(this, db);
    modeldinner ->setTable("tmp_dinner");
    modeldinner->setHeaderData(3, Qt::Horizontal, QObject::tr("Блюдо"));
    modeldinner->setHeaderData(4, Qt::Horizontal, QObject::tr("Количество (в г)"));
    modeldinner->select();
    ui->tableViewdinner->setModel(modeldinner);
    ui->tableViewdinner->setColumnHidden(0, true);
    ui->tableViewdinner->setColumnHidden(1, true);
    ui->tableViewdinner->setColumnHidden(2, true);
    ui->tableViewdinner->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    modelsnack = new QSqlTableModel(this, db);
    modelsnack ->setTable("tmp_snack");
    modelsnack->setHeaderData(3, Qt::Horizontal, QObject::tr("Блюдо"));
    modelsnack->setHeaderData(4, Qt::Horizontal, QObject::tr("Количество (в г)"));
    modelsnack->select();
    ui->tableViewsnack->setModel(modelsnack);
    ui->tableViewsnack->setColumnHidden(0, true);
    ui->tableViewsnack->setColumnHidden(1, true);
    ui->tableViewsnack->setColumnHidden(2, true);
    ui->tableViewsnack->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}


void MainWindow::addbd(std::string file_name)
{
    QString products;

    std::string product;
    std::ifstream fin(file_name);
        if (fin.is_open())
        {
            std::stringstream buffer;
            buffer << fin.rdbuf();
            product = buffer.str();
        }
        fin.close();

    products = QString::fromStdString(product);

    queryDBin = new QSqlQuery(db);
    queryDBin -> exec(products);
}


