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
#include <QTableWidget>

#include <QTableWidgetSelectionRange>

#include "ui_spreadsheet.h"

class SpreadsheetCompare;
//class Cell;

class Spreadsheet : public QTableWidget, public Ui::Spreadsheet
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
	void setCurrentCell( int, int );
	QTableWidgetSelectionRange selectedRange() const;
    void sort( const SpreadsheetCompare &compare );

public slots:
    void newFile();

private slots:
    void somethingChanged();

private:
    bool IsChecked;
    bool autoRecalc;
    //Cell *cell( int row, int column ) const;
};

class SpreadsheetCompare
{
public:
    bool operator() ( const QStringList &row1,
                      const QStringList &row2 ) const;
    enum { KeyCount = 3 };
    int keys[ KeyCount ];
    bool ascending[ KeyCount ];
};
#endif // SPREADSHEET_H
