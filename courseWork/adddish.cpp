#include "adddish.h"
#include "ui_adddish.h"

AddDish::AddDish(QWidget *parent, int row, QString date, QString time) :
    QDialog(parent),
    ui(new Ui::AddDish)
{
    ui->setupUi(this);

    this->row = row;
    this->date = date;
    this->time = time;
    tmp_count = -1;
    tmp_row = -1;
    tmp_name = "";

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./testDB.db");
    if(db.open()){
        qDebug("Open");
    }else{
        qDebug("No open");
    }

    model = new QSqlTableModel(this, db);
    model ->setTable("Recipes");
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Название"));
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);
    for(int i=2;i<=7;i++){
        ui->tableView->setColumnHidden(i, true);
    }
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

}

AddDish::~AddDish()
{
    delete ui;
}

void AddDish::on_tableView_clicked(const QModelIndex &index)
{
    tmp_row = index.row() + 1;

    QString tmp_query = "SELECT name FROM 'Recipes' WHERE id = " + QString::number(tmp_row) + ";";

    if(db.open()){
         qDebug("Open");
    }else{
         qDebug("No open");
    }
    query = new QSqlQuery(db);
    query->prepare(tmp_query);
    query->exec();

    if(query->first()){
    tmp_name = query->value(0).toString();}

}


void AddDish::on_pushButton_clicked()
{
    QString tmp_count_str = ui->textEdit->toPlainText();
    tmp_count = tmp_count_str.toInt();
    QString tmp_id = "SELECT seq FROM sqlite_sequence WHERE name = '" + time + "';";

    int id = 0;
    query = new QSqlQuery(db);
    query->prepare(tmp_id);
    if(query->next()){
    id = query->value(0).toInt();}
    id++;

    if(tmp_count>0 && tmp_row!=-1){

    QString tmp_query = "INSERT INTO tmp_" + time + " (dish_id, recipe_id, name, count) VALUES (:dish_id, :recipe_id, :name, :count);";
    if(db.open()){
         qDebug("Open");
    }else{
         qDebug("No open");
    }
    query = new QSqlQuery(db);
    query->prepare(tmp_query);
    query->bindValue(0, id);
    query->bindValue(1, tmp_row);
    query->bindValue(2, tmp_name);
    query->bindValue(3, tmp_count);
    query->exec();

    tmp_query = "INSERT INTO " + time + " (recipe_id, quantity, time) VALUES (:recipe_id, :quantity, :time);";
    if(db.open()){
         qDebug("Open");
    }else{
         qDebug("No open");
    }
    query = new QSqlQuery(db);
    query->prepare(tmp_query);
    query->bindValue(0, tmp_row);
    query->bindValue(1, tmp_count);
    query->bindValue(2, date);
    query->exec();

    AddDish::~AddDish();
    }
}

