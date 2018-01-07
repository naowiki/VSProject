//============================================================================================================
/**
* @file sortdialog.cpp
* @brief ソートダイアログクラス実装ファイル
* @author fukuda.naotaka
* @date 2017/07/23
*/
//============================================================================================================
#include <QtGui>
//#ii
#include "sortdialog.h"
//============================================================================================================
/**
* @fn
* @brief コンストラクタ
* @param なし
* @return なし
* @detail 
*/
//============================================================================================================
SortDialog::SortDialog(QWidget *parent)
    : QDialog(parent),
      bIsAdvanced(false)
{
    setupUi( this );

    secondaryGroupBox->hide();
    tertiaryGroupBox->hide();
    layout()->setSizeConstraint( QLayout::SetFixedSize );

    setColumnRange( 'A', 'X' );

    connect( moreButton, SIGNAL(clicked()),
             this, SLOT(findMoreButtonClicked()) );
}
//============================================================================================================
/**
* @fn
* @brief 各コンボボックスへのアイテム設定の処理
* @param QChar first 最初の文字
* @param QChar last  最後の文字
* @return なし
* @detail コンボボックスにアイテムを設定する。
*/
//============================================================================================================
void SortDialog::setColumnRange( QChar first, QChar last )
{
    primaryColumnCombo->clear();
    secondaryColumnCombo->clear();
    tertiaryColumnCombo->clear();

    secondaryColumnCombo->addItem( tr("None") );
    tertiaryColumnCombo->addItem( tr("None") );

    primaryColumnCombo->setMinimumSize(
        secondaryColumnCombo->sizeHint() );

    QChar ch = first;
    while ( ch <= last )
    {
        primaryColumnCombo->addItem( QString(ch) );
        secondaryColumnCombo->addItem( QString(ch) );
        tertiaryColumnCombo->addItem( QString(ch) );
        ch = ch.unicode() + 1;
    }
}
//============================================================================================================
/**
* @fn
* @brief [More]ボタン押下時の処理
* @param なし
* @return なし
* @detail ボタンの状態に応じて、ボタンのキャプションを設定する。
*/
//============================================================================================================
void SortDialog::findMoreButtonClicked()
{
    bIsAdvanced = !bIsAdvanced;
    if ( !bIsAdvanced )
    {
        moreButton->setText("Normal Mode");
    }
    else
    {
        moreButton->setText("Advanced Mode");
    }
}