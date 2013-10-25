#ifndef QSTDITEMDIALOG_H
#define QSTDITEMDIALOG_H

#include <QDialog>
#include <QDir>
#include <QtCore>
#include <QtGui>
#include <QStandardItem>

namespace Ui {
class QstdItemDialog;
}

class QstdItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QstdItemDialog(QWidget *parent = 0);
    ~QstdItemDialog();

private:
    Ui::QstdItemDialog *ui;

    QStandardItemModel *StdModel;

};

#endif // QSTDITEMDIALOG_H
