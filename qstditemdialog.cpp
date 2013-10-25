#include "qstditemdialog.h"
#include "ui_qstditemdialog.h"

QstdItemDialog::QstdItemDialog(QWidget *parent) : QDialog(parent), ui(new Ui::QstdItemDialog)
{
    ui->setupUi(this);

    StdModel = new QStandardItemModel(this);

    QStandardItem *item = StdModel->invisibleRootItem();
    QStandardItem *tmp3, *tmp4;

    tmp3 = new QStandardItem("test1");
    tmp4 = new QStandardItem("Test2");
    item->appendRow(tmp3);
    tmp3->appendRow(tmp4);


    ui->treeView->setModel(StdModel);
    ui->treeView->expandAll();
}

QstdItemDialog::~QstdItemDialog()
{
    delete ui;
}
