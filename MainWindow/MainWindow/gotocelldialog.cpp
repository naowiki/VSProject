//============================================================================================================
/**
* @file gotocelldialog.cpp
* @brief RADデザイン確認用クラス実装ファイル
* @author fukuda.naotaka
* @date 2017/07/06
*/
//============================================================================================================
#include <QtGui>

#include "gotocelldialog.h"
//============================================================================================================
/**
* @fn
* @brief OKボタン押下時の処理
* @param なし
* @return なし
* @detail ラインエディットへの入力内容が有効であれば、OKボタンを有効にする。
*/
//============================================================================================================
GoToCellDialog::GoToCellDialog( QWidget *parent )
    : QDialog( parent )
{
    setupUi( this );

    QRegExp regExp("[A-Za-z][1-9][0-9]{0,2}");
    lineEdit->setValidator( new QRegExpValidator( regExp, this ) );
    
    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}
//============================================================================================================
/**
* @fn
* @brief OKボタン押下時の処理
* @param なし
* @return なし
* @detail ラインエディットへの入力内容がバリデータに定義した内容であれば、OKボタンを有効表示にする。
*/
//============================================================================================================
void GoToCellDialog::on_lineEdit_textChanged()
{
    okButton->setEnabled( lineEdit->hasAcceptableInput() );
}
