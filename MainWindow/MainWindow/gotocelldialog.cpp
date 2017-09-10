//============================================================================================================
/**
* @file gotocelldialog.cpp
* @brief RAD�f�U�C���m�F�p�N���X�����t�@�C��
* @author fukuda.naotaka
* @date 2017/07/06
*/
//============================================================================================================
#include <QtGui>

#include "gotocelldialog.h"
//============================================================================================================
/**
* @fn
* @brief OK�{�^���������̏���
* @param �Ȃ�
* @return �Ȃ�
* @detail ���C���G�f�B�b�g�ւ̓��͓��e���L���ł���΁AOK�{�^����L���ɂ���B
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
* @brief OK�{�^���������̏���
* @param �Ȃ�
* @return �Ȃ�
* @detail ���C���G�f�B�b�g�ւ̓��͓��e���o���f�[�^�ɒ�`�������e�ł���΁AOK�{�^����L���\���ɂ���B
*/
//============================================================================================================
void GoToCellDialog::on_lineEdit_textChanged()
{
    okButton->setEnabled( lineEdit->hasAcceptableInput() );
}
