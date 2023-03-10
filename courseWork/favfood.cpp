#include "favfood.h"
#include "ui_favfood.h"

FavFood::FavFood(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::FavFood)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("testDB.db");
    if (db.open()) {
        qDebug("Open");
    }
    else {
        qDebug("No open");
    }

    model = new QSqlTableModel(this, db);
    model->setTable("FavFood");
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Номер"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Название"));
    model->select();
    ui->tableView->setModel(model);
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    modelProd = new QSqlTableModel(this, db);
    modelProd->setTable("Products");
    modelProd->setHeaderData(0, Qt::Horizontal, QObject::tr("Номер"));
    modelProd->setHeaderData(1, Qt::Horizontal, QObject::tr("Название"));
    modelProd->select();
    ui->tableView_2->setModel(modelProd);
    ui->tableView_2->setColumnHidden(0, true);
    ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    for (int i = 2; i <= 5; ++i) {
        ui->tableView_2->setColumnHidden(i, true);
    }
}

FavFood::~FavFood()
{
    delete ui;
}

void FavFood::on_pushButton_clicked()
{
    model->insertRow(model->rowCount());
}

void FavFood::on_pushButton_2_clicked()
{
    model->removeRow(row);
}

void FavFood::on_tableView_clicked(const QModelIndex& index)
{
    row = index.row();
}

