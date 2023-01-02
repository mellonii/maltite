#include "create_recipe.h"
#include "ui_create_recipe.h"
//#include <fstream>

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
        qDebug("No open");
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

    modelAllProduct = new QSqlTableModel(this, db);
    modelAllProduct ->setTable("Recipes");

    if(db.open()){
        qDebug("Open");
    }else{
        qDebug("No open");
    }

    modelProd = new QSqlTableModel(this, db);
    modelProd->setTable("Products");
    modelProd->setHeaderData(0, Qt::Horizontal, QObject::tr("Номер"));
    modelProd->setHeaderData(1, Qt::Horizontal, QObject::tr("Название"));
    modelProd->select();
    ui->tableView_2->setModel(modelProd);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    for(int i = 2; i<=5; ++i){
        ui->tableView_2->setColumnHidden(i, true);
    }

}

create_recipe::~create_recipe()
{
    db.close();
    delete ui;
}

#include <map>
#include <algorithm>
#include <vector>

struct Product {
    int id;
    int Calories;
    double Carbohydrate;
    double Protein;
    double Fat;
    Product() {
        this->id = 0;
        this->Calories = 0;
        this->Carbohydrate = 0.0;
        this->Protein = 0.0;
        this->Fat = 0.0;
    }
    Product(int id, int Calories, double Protein, double Fat, double Carbohydrate) {
        this->id = id;
        this->Calories = Calories;
        this->Carbohydrate = Carbohydrate;
        this->Protein = Protein;
        this->Fat = Fat;
    }
};
//Рецепты с продуктами и количеством продуктов
struct Dish {
    int id;
    QString name;
    QString recipe;
    int Calories;
    double Carbohydrate;
    double Protein;
    double Fat;
    std::map<double, Product> ingredient_list; //map для сохранения ингредиентов и количества
    Dish() {
        id = 0;
        name = "0";
        recipe = "0";
        Calories = 0;
        Carbohydrate = 0.0;
        Protein = 0.0;
        Fat = 0.0;
    }
    Dish(int id, QString name, QString recipe, std::map<double, Product> ingredient_list) {
        this->id = id;
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
    void addProduct(double count, Product product) {
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
    std::map<double, Product> ingredient_list;

    if(db.open()){
        qDebug("Open");
    }else{
        qDebug("No open");
    }
    QSqlQuery query_all("SELECT ProdInRec.Prod_id,  Products.calories , Products.protein , Products.fat , Products.carbohydrate, ProdInRec.count FROM ProdInRec, Products "
                    "WHERE ProdInRec.Prod_id = Products.id");
        while (query_all.next()) {
            Product tmp_Prod = Product(query_all.value(0).toInt(), query_all.value(1).toInt(), query_all.value(2).toDouble(),query_all.value(3).toDouble(),query_all.value(4).toDouble());
            ingredient_list.insert(std::make_pair(query_all.value(5).toDouble(), tmp_Prod));

            //std::ofstream fin;
                //fin.open("tmp.txt");
                //fin << query_all.value(0).toInt() << " " << query_all.value(1).toInt() << " " << query_all.value(2).toDouble() << " " << query_all.value(3).toDouble() << " " << query_all.value(4).toDouble();
                //fin.close();
        }
    Dish dish = Dish(modelAllProduct->rowCount()+1, name, recipe,ingredient_list);
    calories = dish.Calories;
    protein = dish.Protein;
    fat = dish.Fat;
    carbohydrate = dish.Carbohydrate;

    //std::ofstream fin;
    //fin.open("tmp.txt");
    //fin << modelAllProduct->rowCount()+1 << " " << dish.name.toStdString() << " " << dish.recipe.toStdString() << " " << calories << " " << protein << " " << fat << " " << carbohydrate;
    //fin.close();

    if(db.open()){
        qDebug("Open");
    }else{
        qDebug("No open");
    }
    query = new QSqlQuery(db);
    query->prepare("INSERT INTO Recipes (id, name, recipe, calories, protein, fat, carbohydrate) "
                  "VALUES (:id, :name, :recipe, :calories, :protein, :fat, :carbohydrate)");
    query->bindValue(0, modelAllProduct->rowCount()+1);
    query->bindValue(1, name);
    query->bindValue(2, recipe);
    query->bindValue(3, calories);
    query->bindValue(4, protein);
    query->bindValue(5, fat);
    query->bindValue(6, carbohydrate);
    query->exec();
}
