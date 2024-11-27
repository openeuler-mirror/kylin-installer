#ifndef INSTALLEDPACKAGEDLG_H
#define INSTALLEDPACKAGEDLG_H

#include <QDialog>
#include <QStringListModel>

namespace Ui {
class installedPackageDlg;
}

class installedPackageDlg : public QDialog
{
    Q_OBJECT

public:
    explicit installedPackageDlg(QWidget *parent = nullptr);
    ~installedPackageDlg();
    void getPackages();
signals:
    void selectInstalledPackage(QString);

private slots:
    void on_buttonBox_accepted();

    void on_listView_clicked(const QModelIndex &index);

private:
    Ui::installedPackageDlg *ui;
    QStringListModel *item;
};

#endif // INSTALLEDPACKAGEDLG_H
