/**
* @file sortdialog.h
* @brief R�\�[�g�_�C�A���O�N���X�w�b�_�t�@�C��
* @author fukuda.naotaka
* @date 2017/07/23
*/
#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <QDialog>
#include <QLabel>

#include "ui_spreadsheet.h"

class Spreadsheet : public QDialog, public Ui::Spreadsheet
{
	Q_OBJECT

public:
	Spreadsheet( QWidget *parent = 0 );
    bool showGrid();
    void clear();
    QString currentLocation();
    QString currentFormula();

public slots:
    void newFile();

private:
    bool IsChecked;
};

#endif // SPREADSHEET_H