#include "create_prod.h"
#include "ui_create_prod.h"

Create_prod::Create_prod(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Create_prod)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("testDB.db");
    if(db.open()){
        qDebug("Open");
    }else{
        qDebug("No open");
    }

    modelProduct = new QSqlTableModel(this, db);
    modelProduct ->setTable("Products");
    modelProduct->setHeaderData(1, Qt::Horizontal, QObject::tr("Название"));
    modelProduct->setHeaderData(2, Qt::Horizontal, QObject::tr("Калории"));
    modelProduct->setHeaderData(3, Qt::Horizontal, QObject::tr("Белки"));
    modelProduct->setHeaderData(4, Qt::Horizontal, QObject::tr("Жиры"));
    modelProduct->setHeaderData(5, Qt::Horizontal, QObject::tr("Углеводы"));
    ui->tableView->setModel(modelProduct);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->setColumnHidden(0, true);

}

Create_prod::~Create_prod()
{
    delete ui;
}

void Create_prod::on_pushButton_clicked()
{
    modelProduct->insertRow(modelProduct->rowCount());
}

