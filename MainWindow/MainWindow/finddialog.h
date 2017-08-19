#ifndef finddialog_H
#define finddialog_H
#include <QDialog>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    FindDialog( QWidget *parent = 0 );
signals:
    void findNext( const QString &str, Qt::CaseSensitivity cs );
    void findPrevious( const QString &str, Qt::CaseSensitivity cs );
private slots:
    void findClicked();
    void enableFindButton( const QString &test );
private:
    QLabel      *label;
    QLineEdit   *lineEdit;
    QCheckBox   *caseCheckBox;
    QCheckBox   *backwardCheckBox;
    QPushButton *findButton;
    QPushButton *closeButton;
};
#endif // finddialog_H
