#include <QtGui>
#include <QList>

//#include "cell.h"
#include "spreadsheet.h"

//==============================================================================================================================================================
/**
* @fn
* @brief  ‚˜‚˜‚˜‚˜‚˜‚˜‚˜‚˜
* @author fukuda.naotaka
* @date   2017/07/31
* @param  ‚È‚µ
* @return ‚È‚µ
* @detail ‚˜‚˜‚˜‚˜‚˜‚˜‚˜‚˜
*/
//==============================================================================================================================================================
Spreadsheet::Spreadsheet(QWidget *parent)
    : QTableWidget(parent),\
      IsChecked(false)
{
    setupUi(this);

    autoRecalc = true;

    setSelectionMode( ContiguousSelection );

    connect( this, SIGNAL( itemChanged( QTableWidgetItem * ) ),
             this, SLOT( somethingChanged() ) );

    setRowCount( 1000 );
    setColumnCount( 6 );

    //clear();
}
//==============================================================================================================================================================
/**
* @fn
* @brief  ‚˜‚˜‚˜‚˜‚˜‚˜‚˜‚˜
* @author fukuda.naotaka
* @date   2017/07/31
* @param  ‚È‚µ
* @return ‚È‚µ
* @detail ‚˜‚˜‚˜‚˜‚˜‚˜‚˜‚˜
*/
//==============================================================================================================================================================
bool Spreadsheet::showGrid()
{
    return IsChecked;
}
void Spreadsheet::newFile()
{
    QString strFilename = filenameLineEdit->text();
}

QString Spreadsheet::currentLocation()
{
    return "Current Location";
}

QString Spreadsheet::currentFormula()
{
    return "Current Formula";
}

void Spreadsheet::clear()
{
    setRowCount( 0 );
    setColumnCount( 0 );
}

bool Spreadsheet::readFile( QString fileName )
{
    return true;
}

bool Spreadsheet::writeFile(QString fileName)
{
    return true;
}
void Spreadsheet::setCurrentCell( int nRow, int nCol )
{

}

QTableWidgetSelectionRange Spreadsheet::selectedRange() const
{
//    QList<QTableWidgetSelectionRange> ranges = selectedRange();
//    if ( ranges.isEmpty() )
//    {
        return QTableWidgetSelectionRange();
//    }
//    return ranges.first();
}

void Spreadsheet::sort( const SpreadsheetCompare &compare )
{

}

void Spreadsheet::somethingChanged()
{

}

//Cell *Spreadsheet::cell( int row, int column ) const
//{
//    return static_cast<Cell *> (item( row, column ) );
//}
