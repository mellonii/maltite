#include "recipe.h"
#include "ui_recipe.h"

Recipe::Recipe(QWidget *parent, int row) :
    QDialog(parent),
    ui(new Ui::Recipe)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./testDB.db");
    if(db.open()){
        qDebug("Open");
    }else{
        qDebug("No open");
    }

    model_recipes = new QSqlTableModel(this, db);
    model_recipes ->setTable("Recipes");
    model_recipes->setHeaderData(1, Qt::Horizontal, QObject::tr("Название"));
    model_recipes->setHeaderData(4, Qt::Horizontal, QObject::tr("Калории"));
    model_recipes->setHeaderData(5, Qt::Horizontal, QObject::tr("Белки"));
    model_recipes->setHeaderData(6, Qt::Horizontal, QObject::tr("Жиры"));
    model_recipes->setHeaderData(7, Qt::Horizontal, QObject::tr("Углеводы"));
    model_recipes->select();
    ui->tableView->setModel(model_recipes);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->setColumnHidden(2, true);
    ui->tableView->setColumnHidden(3, true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    for(int i=0; i<model_recipes->rowCount(); ++i){
        ui->tableView->setRowHidden(i, true);
    }
    ui->tableView->setRowHidden(row, false);

    ui->textBrowser_2->clear();
    QString tmp = "SELECT recipe, ingredients FROM Recipes WHERE id = " + QString::number(row+1) + " ;";
    if(db.open()){
        qDebug("Open");
    }else{
        qDebug("No open");
    }
    QSqlQuery query(tmp);
    QString tmp_str;
    QString tmp_str1;
    while (query.next()) {
        tmp_str = "Рецепт: \n" + QString(query.value(0).toString());
        tmp_str1 = "Ингредиенты: \n" + QString(query.value(1).toString());}
    ui->textBrowser_2->insertPlainText(tmp_str);
    ui->textBrowser->insertPlainText(tmp_str1);

}

Recipe::~Recipe()
{
    delete ui;
}
