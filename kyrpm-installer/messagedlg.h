#ifndef MESSAGEDLG_H
#define MESSAGEDLG_H

#include <QDialog>

namespace Ui {
class MessageDlg;
}

class MessageDlg : public QDialog
{
    Q_OBJECT

public:
    explicit MessageDlg(QWidget *parent = nullptr);
    ~MessageDlg();

    void setOptions(QStringList resultList);

private:
    Ui::MessageDlg *ui;
    QStringList m_resultList;
};

#endif // MESSAGEDLG_H
