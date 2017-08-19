/**
* @file sortdialog.h
* @brief Rソートダイアログクラスヘッダファイル
* @author fukuda.naotaka
* @date 2017/07/23
*/
#ifndef SORTDIALOG_H
#define SORTDIALOG_H

#include <QDialog>

#include "ui_sortdialog.h"

class SortDialog : public QDialog, public Ui::SortDialog
{
	Q_OBJECT

private:
    bool bIsAdvanced;

public:
	SortDialog( QWidget *parent = 0 );

	void setColumnRange( QChar first, QChar last );

private slots:
    void findMoreButtonClicked();
};

#endif // SORTDIALOG_H