/**
* @file gotocelldialog.h
* @brief RADデザイン確認用クラスヘッダファイル
* @author fukuda.naotaka
* @date 2017/07/06
*/
#ifndef GOTOCELLDIALOG_H
#define GOTOCELLDIALOG_H

#include <QDialog>

#include "ui_gotocelldialog.h"

class GoToCellDialog : public QDialog, public Ui::GoToCellDialog
{
    Q_OBJECT

public:
    GoToCellDialog( QWidget *parent = 0 );

private slots:
    void on_lineEdit_textChanged();
};

#endif // GOTOCELLDIALOG_H
