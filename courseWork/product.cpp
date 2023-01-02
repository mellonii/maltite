#include "product.h"
#include "ui_product.h"

Product::Product(QWidget *parent,int row_1) :
    QDialog(parent),
    ui(new Ui::Product)
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
    modelProduct->select();

    ui->tableView->setModel(modelProduct);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->setColumnHidden(0, true);
    for(int i=0; i<modelProduct->rowCount(); ++i){
        ui->tableView->setRowHidden(i, true);
    }
    ui->tableView->setRowHidden(row_1, false);

}

Product::~Product()
{
    delete ui;
}
