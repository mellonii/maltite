#include "create_recipe.h"
#include "ui_create_recipe.h"

create_recipe::create_recipe(QWidget *parent, int num) :
    QDialog(parent),
    ui(new Ui::create_recipe)
{
    ui->setupUi(this);
    this->num = num;
    bool a = 0;

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("testDB.db");
    if(db.open()){
        qDebug("Open");
    }else{
        qDebug("No open for create table ProdInRec: %s", qPrintable(db.lastError().text()));
    }
    queryDropProduct = new QSqlQuery(db);
    queryDropProduct -> exec("DROP TABLE IF EXISTS ProdInRec;");
    queryProduct = new QSqlQuery(db);
    queryProduct -> exec("CREATE TABLE ProdInRec(Prod_id INTEGER UNIQUE, count REAL NOT NULL);");
    modelProduct = new QSqlTableModel(this, db);
    modelProduct ->setTable("ProdInRec");
    modelProduct->setHeaderData(0, Qt::Horizontal, QObject::tr("Номер"));
    modelProduct->setHeaderData(1, Qt::Horizontal, QObject::tr("Количество"));
    ui->tableView->setModel(modelProduct);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    modelProd = new QSqlTableModel(this, db);
    modelProd->setTable("Products");
    modelProd->setHeaderData(1, Qt::Horizontal, QObject::tr("Название"));
    modelProd->select();
    ui->tableView_2->setModel(modelProd);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView_2->setColumnHidden(0, true);
    for(int i = 2; i<=5; ++i){
        ui->tableView_2->setColumnHidden(i, true);
    }

}

create_recipe::~create_recipe()
{
    delete ui;
}

#include <map>
#include <algorithm>
#include <vector>

struct Products {
    int id;
    QString name;
    int Calories;
    double Carbohydrate;
    double Protein;
    double Fat;
    Products() {
        this->id = 0;
        this->Calories = 0;
        this->Carbohydrate = 0.0;
        this->Protein = 0.0;
        this->Fat = 0.0;
        this->name = "";
    }
    Products(int id, int Calories, double Protein, double Fat, double Carbohydrate, QString name) {
        this->id = id;
        this->Calories = Calories;
        this->Carbohydrate = Carbohydrate;
        this->Protein = Protein;
        this->Fat = Fat;
        this->name = name;
    }
};
//Рецепты с продуктами и количеством продуктов
struct Dish {
    QString name;
    QString recipe;
    int Calories;
    double Carbohydrate;
    double Protein;
    double Fat;
    std::map<double, Products> ingredient_list; //map для сохранения ингредиентов и количества
    Dish() {
        name = "0";
        recipe = "0";
        Calories = 0;
        Carbohydrate = 0.0;
        Protein = 0.0;
        Fat = 0.0;
    }
    Dish(QString name, QString recipe, std::map<double, Products> ingredient_list) {
        this->name = name;
        this->recipe = recipe;
        Calories = 0;
        Carbohydrate = 0.0;
        Protein = 0.0;
        Fat = 0.0;
        for (auto pair : ingredient_list) {
            addProduct(std::get<0>(pair), std::get<1>(pair));
        }
    }
    void addProduct(double count, Products product) {
        ingredient_list.insert(std::make_pair(count, product));
        Calories = Calories + product.Calories * count;
        Carbohydrate = Carbohydrate + product.Carbohydrate * count;
        Protein = Protein + product.Protein * count;
        Fat = Fat + product.Fat * count;
    }
};


void create_recipe::on_pushButton_clicked()
{
    modelProduct->insertRow(modelProduct->rowCount());
}


void create_recipe::on_pushButton_2_clicked()
{

    QString name = ui->textEdit->toPlainText();
    QString recipe = ui->textEdit_2->toPlainText();
    int calories = 0;
    double protein = 0.0;
    double fat = 0.0;
    double carbohydrate = 0.0;
    std::map<double, Products> ingredient_list;

    if(db.open()){
        qDebug("Open");
    }else{
        qDebug("No open for select from ProdInRec, Products: %s", qPrintable(db.lastError().text()));
    }
    QSqlQuery query_all("SELECT ProdInRec.Prod_id,  Products.calories , Products.protein , Products.fat , Products.carbohydrate, ProdInRec.count, Products.name FROM ProdInRec, Products "
                    "WHERE ProdInRec.Prod_id = Products.id");
        while (query_all.next()) {
            Products tmp_Prod = Products(query_all.value(0).toInt(), query_all.value(1).toInt(), query_all.value(2).toDouble()/100.0,query_all.value(3).toDouble()/100.0,query_all.value(4).toDouble()/100.0, query_all.value(6).toString());
            ingredient_list.insert(std::make_pair(query_all.value(5).toDouble(), tmp_Prod));

        }
        modelAllProduct = new QSqlTableModel(this, db);
        modelAllProduct ->setTable("Recipes");

    Dish dish = Dish(name, recipe,ingredient_list);
    calories = dish.Calories;
    protein = dish.Protein;
    fat = dish.Fat;
    carbohydrate = dish.Carbohydrate;

    QString ingredients;
    int cou=0;
    for (auto pair : ingredient_list) {
        cou++;
        ingredients = ingredients + QString::number(cou) + ". " + std::get<1>(pair).name + " - " + QString::number(std::get<0>(pair)) + "г\n";
    }

    if(cou>0 && ingredients.size()>0 && recipe.size()>0 && name.size()>0){
    if(db.open()){
        qDebug("Open");
    }else{
        qDebug("No open for add info about recipe: %s", qPrintable(db.lastError().text()));
    }
    query = new QSqlQuery(db);
    query->prepare("INSERT INTO Recipes (name, recipe, ingredients, calories, protein, fat, carbohydrate) "
                  "VALUES (:name, :recipe, :ingredients, :calories, :protein, :fat, :carbohydrate)");
    query->bindValue(0, name);
    query->bindValue(1, recipe);
    query->bindValue(2, ingredients);
    query->bindValue(3, calories/100);
    query->bindValue(4, protein);
    query->bindValue(5, fat);
    query->bindValue(6, carbohydrate);
    query->exec();

    create_recipe::~create_recipe();
}
}
