#include <QtGui>

#include "spreadsheet.h"

//==============================================================================================================================================================
/**
* @fn
* @brief  ����������������
* @author fukuda.naotaka
* @date   2017/07/31
* @param  �Ȃ�
* @return �Ȃ�
* @detail ����������������
*/
//==============================================================================================================================================================
Spreadsheet::Spreadsheet(QWidget *parent)
    : QDialog(parent),
      IsChecked(false)
{
    setupUi(this);
}
//==============================================================================================================================================================
/**
* @fn
* @brief  ����������������
* @author fukuda.naotaka
* @date   2017/07/31
* @param  �Ȃ�
* @return �Ȃ�
* @detail ����������������
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

}

bool Spreadsheet::readFile( QString fileName )
{
    return true;
}

bool Spreadsheet::writeFile(QString fileName)
{
    return true;
}