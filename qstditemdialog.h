#ifndef QSTDITEMDIALOG_H
#define QSTDITEMDIALOG_H

#include <QDialog>
#include <QDir>
#include <QtCore>
#include <QtGui>
#include <QStandardItem>
#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>
#include <QFileDialog>

namespace Ui {
class QstdItemDialog;
}

class QstdItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QstdItemDialog(QWidget *parent = 0);
    ~QstdItemDialog();

private slots:
    void on_pushButton_clicked();

    void on_pBLoad_clicked();

    void on_pBSave_clicked();

private:
    Ui::QstdItemDialog *ui;

    QStandardItemModel *StdModel;

    QDomDocument xmldoc;
    QDir directory;

    void ParseXMLFile(QString sPath, QDomDocument *xmlDoc);
    void SaveXMLFile(QString sPath, QDomDocument *xmlDoc);
    void ProcessXMLData(QDomElement *rootxml, QStandardItem *rootNode, QString tabStr);
};

#endif // QSTDITEMDIALOG_H
