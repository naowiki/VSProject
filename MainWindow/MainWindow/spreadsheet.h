/**
* @file sortdialog.h
* @brief Rソートダイアログクラスヘッダファイル
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
    bool readFile( QString );
    bool writeFile( QString );

public slots:
    void newFile();

private:
    bool IsChecked;
};

#endif // SPREADSHEET_H