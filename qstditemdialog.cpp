#include "qstditemdialog.h"
#include "ui_qstditemdialog.h"


const QString DirTagName = "dir";
const QString DirAttrName = "name";


QstdItemDialog::QstdItemDialog(QWidget *parent) : QDialog(parent), ui(new Ui::QstdItemDialog)
{
    ui->setupUi(this);

    StdModel = new QStandardItemModel(this);

//    QStandardItem *item = StdModel->invisibleRootItem();
//    QStandardItem *tmp3, *tmp4;

//    tmp3 = new QStandardItem("test1");
//    tmp4 = new QStandardItem("Test2");
//    item->appendRow(tmp3);
//    tmp3->appendRow(tmp4);


    ui->treeView->setModel(StdModel);
    ui->treeView->expandAll();

    ui->textEdit->setText("C:/Users/dmmacs/Documents/Qt Projects/QFileSystemModel/tmp.xml");
}

QstdItemDialog::~QstdItemDialog()
{
    delete ui;
}

void QstdItemDialog::on_pushButton_clicked()
{
    if (ui->textEdit->toPlainText() != "")
    {
        // Clear the Tree
        StdModel->clear();

        ParseXMLFile("C:/Users/dmmacs/Documents/Qt Projects/QFileSystemModel/tmp.xml", &xmldoc);

        // Get Root of Tree and XML
        QStandardItem *Node = StdModel->invisibleRootItem();
        QDomElement root = xmldoc.firstChildElement(DirTagName);

        // Add the Root node
        qDebug() << root.attribute(DirAttrName);

        // Add the node
        QStandardItem *tmpNode;
        tmpNode = new QStandardItem(root.attribute(DirAttrName));
        Node->appendRow(tmpNode);

        root = root.firstChildElement(DirTagName);

        ProcessXMLData(&root, tmpNode, "  ");
        ui->treeView->expandAll();

    }
}

void QstdItemDialog::ParseXMLFile(QString sPath, QDomDocument *xmlDoc)
{
    QFile file(sPath);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file";
        ui->textEdit->setText("Failed to open file");
    }
    else
    {
        if(!xmlDoc->setContent(&file))
        {
            qDebug() << "Failed to load document";
            ui->textEdit->setText("Failed to load document");
        }
        file.close();
    }

}

void QstdItemDialog::ProcessXMLData(QDomElement *rootxml, QStandardItem *rootNode, QString tabStr)
{
    QStandardItem *tmpNode;
    QDomElement nextItem;
    QDomElement childItem;

    nextItem = *rootxml;
    while (nextItem.isNull() == FALSE)
    {
        qDebug() << tabStr << nextItem.attribute(DirAttrName);
        tmpNode = new QStandardItem(nextItem.attribute(DirAttrName));
        rootNode->appendRow(tmpNode);
//        tmpNode = new QStandardItem(nextItem.attribute(DirAttrName));
        if (nextItem.hasChildNodes())
        {
            childItem = nextItem.firstChildElement();
            QString tmp;
            tmp = tabStr + "  ";
            ProcessXMLData(&childItem, tmpNode, tmp);
        }
        else
        {
//            rootNode->appendRow(tmpNode);
        }
        nextItem = nextItem.nextSiblingElement(DirTagName);
    }

}

