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
}

QstdItemDialog::~QstdItemDialog()
{
    delete ui;
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


    //get the root element
    QDomElement root = xmlDoc->firstChildElement();
    QDomNodeList items = root.elementsByTagName(DirTagName);

//     qDebug() << "Total items = " << items.count();
     QString tmp_str;
     tmp_str = "Total items  = ";
     QLocale tmpLoc;
     tmp_str += tmpLoc.toString(items.count());
//     tmp_str += QLocale::toString(i);


     ui->textEdit->setText(tmp_str);

     for(int i = 0; i < items.count(); i++)
     {
        QDomNode itemnode = items.at(i);

        //convert to element
        if(itemnode.isElement())
        {
            QDomElement itemele = itemnode.toElement();
//            qDebug() << itemele.attribute(DirAttrName);
            tmp_str = ui->textEdit->toPlainText();
            tmp_str += "\n";
            tmp_str += itemele.attribute("name");
            ui->textEdit->setText(tmp_str);
        }
     }
}

void QstdItemDialog::on_pushButton_clicked()
{
    ParseXMLFile("C:/Users/dmmacs/Documents/Qt Projects/QFileSystemModel/tmp.xml", &xmldoc);

    QStandardItem *item = StdModel->invisibleRootItem();
    //    QStandardItem *tmp3, *tmp4;

    //    tmp3 = new QStandardItem("test1");
    //    tmp4 = new QStandardItem("Test2");
    //    item->appendRow(tmp3);
    //    tmp3->appendRow(tmp4);

    QDomElement root = xmldoc.firstChildElement(DirTagName);
    qDebug() << root.attribute(DirAttrName);


    // Add the Root node
    QStandardItem *tmpNode;
    tmpNode = new QStandardItem(root.attribute(DirAttrName));
    item->appendRow(tmpNode);

    ProcessXMLData(&root, tmpNode);

#if 0

    root = root.firstChildElement();
    qDebug() <<"Root = " << root.attribute(DirAttrName);
    tmpNode = new QStandardItem(root.attribute(DirAttrName));
    item->appendRow(tmpNode);
    ProcessXMLData(&root, item);
#endif

#if 0
    QDomNodeList items = root.elementsByTagName("dir");

    for (int i = 0; i < items.count(); i++)
    {
        QDomNode itemNode = items.at(i);
        //Convert to element
        if (itemNode.isElement())
        {
            QStandardItem *treeNode;
            QDomElement itemEle = itemNode.toElement();
            treeNode = new QStandardItem(itemEle.attribute("name"));
            item->appendRow(treeNode);
        }
    }
#endif
}

void QstdItemDialog::ProcessXMLData(QDomElement *rootxml, QStandardItem *rootNode)
{



#if 0
    QDomElement nextItem;
    nextItem = rootxml->nextSiblingElement(DirTagName);
    qDebug() << nextItem.isNull() << "," << nextItem.attribute(DirAttrName);

    while (!nextItem.isNull())
    {
        QStandardItem *tmpNode;
        tmpNode = new QStandardItem(nextItem.attribute(DirAttrName));
        rootNode->appendRow(tmpNode);

        nextItem = nextItem.nextSiblingElement(DirTagName);
    }
#endif
}

