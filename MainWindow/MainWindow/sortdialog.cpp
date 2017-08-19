//============================================================================================================
/**
* @file sortdialog.cpp
* @brief �\�[�g�_�C�A���O�N���X�����t�@�C��
* @author fukuda.naotaka
* @date 2017/07/23
*/
//============================================================================================================
#include <QtGui>

#include "sortdialog.h"
//============================================================================================================
/**
* @fn
* @brief �R���X�g���N�^
* @param �Ȃ�
* @return �Ȃ�
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
* @brief �e�R���{�{�b�N�X�ւ̃A�C�e���ݒ�̏���
* @param QChar first �ŏ��̕���
* @param QChar last  �Ō�̕���
* @return �Ȃ�
* @detail �R���{�{�b�N�X�ɃA�C�e����ݒ肷��B
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
* @brief [More]�{�^���������̏���
* @param �Ȃ�
* @return �Ȃ�
* @detail �{�^���̏�Ԃɉ����āA�{�^���̃L���v�V������ݒ肷��B
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