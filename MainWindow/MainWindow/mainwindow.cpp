//==============================================================================================================================================================
/**
* @file   mainwindow.cpp
* @brief  ���C���E�B���h�E�N���X�����t�@�C��
* @author fukuda.naotaka
* @date   2017/07/24
*/
//==============================================================================================================================================================
#include <QtGui>
#include "mainwindow.h"
#include "finddialog.h"
#include "sortdialog.h"
#include "spreadsheet.h"
#include "gotocelldialog.h"
//==============================================================================================================================================================
/**
* @fn
* @brief  �R���X�g���N�^
* @param  �Ȃ�
* @return �Ȃ�
* @detail 
*/
//==============================================================================================================================================================
MainWindow::MainWindow()
{
    resize(640, 480);
    // �X�v���b�h�V�[�g��\��
    spreadsheet = new Spreadsheet;
    setCentralWidget( spreadsheet );

    // �����_�C�A���O��\��
    //findDialog = new FindDialog;
    //setCentralWidget( findDialog );
    // �\�[�g�_�C�A���O��\��
    //sortDialog = new SortDialog;
    //setCentralWidget( sortDialog );

    createActions();
    createMenus();
    createContextMenu();
    createToolBars();
    createStatusBar();

    readSettings();
    findDialog = 0;

    setWindowIcon( QIcon(":/MainWindow/images/icon.png") );
    setCurrentFile("");


    connect( spreadsheet->newButton, SIGNAL( clicked() ),
                               this, SLOT( newFile() ) );
}
//==============================================================================================================================================================
/**
* @fn
* @brief  �A�N�V�����𐶐�
* @author fukuda.naotaka
* @date   2017/07/27
* @param  �Ȃ�
* @return �Ȃ�
* @detail New,Open,Save,SaveAs�A�N�V�����𐶐�
*/
//==============================================================================================================================================================
void MainWindow::createActions()
{
    /* New�A�N�V�����𐶐� */
    newAction = new QAction( tr("&New"), this );                                         // �A�N�Z�����[�^New��ݒ�
    newAction->setIcon( QIcon(":/images/new.png") );                                     // �A�C�R��(New.Png)��ݒ�
    newAction->setShortcut( tr("Ctrl+N") );                                              // �V���[�g�J�b�g�L�[(Ctrl+N)��ݒ�
    newAction->setStatusTip( tr("Create a New spreadsheet file.") );                     // �X�e�[�^�X�o�[���b�Z�[�W��ݒ�
    connect( newAction, SIGNAL( triggered() ), this, SLOT( newFile() ) );                // �A�N�V������triggered()�V�O�i�����X���b�g�֐�newFile�ɐڑ�
    /* Open�A�N�V�����𐶐� */
    openAction = new QAction( tr("&Open"), this );                                       // �A�N�Z�����[�^Open��ݒ�
    openAction->setIcon( QIcon(":/images/open.png") );                                   // �A�C�R��(open.Png)��ݒ�
    openAction->setShortcut( tr("Ctrl+O") );                                             // �V���[�g�J�b�g�L�[(Ctrl+N)��ݒ�
    openAction->setStatusTip( tr("Open a spreadsheet file.") );                          // �X�e�[�^�X�o�[���b�Z�[�W��ݒ�
    connect( openAction, SIGNAL( triggered() ), this, SLOT( open() ) );                  // �A�N�V������triggered()�V�O�i�����X���b�g�֐�open�ɐڑ�
    /* Save�A�N�V�����𐶐� */
    saveAction = new QAction( tr("&Save"), this );                                       // �A�N�Z�����[�^Save��ݒ�
    saveAction->setIcon( QIcon(":/images/save.png") );                                   // �A�C�R��(save.Png)��ݒ�
    saveAction->setShortcut( tr("Ctrl+S") );                                             // �V���[�g�J�b�g�L�[(Ctrl+N)��ݒ�
    saveAction->setStatusTip( tr("Save a spreadsheet file.") );                          // �X�e�[�^�X�o�[���b�Z�[�W��ݒ�
    connect( saveAction, SIGNAL( triggered() ), this, SLOT( save() ) );                  // �A�N�V������triggered()�V�O�i�����X���b�g�֐�saveFile�ɐڑ�
    /* SaveAs�A�N�V�����𐶐� */
    saveAsAction = new QAction( tr("Save&As"), this );                                   // �A�N�Z�����[�^SaveAs��ݒ�
    saveAsAction->setIcon( QIcon(":/images/saveas.png") );                               // �A�C�R��(save.Png)��ݒ�
    saveAsAction->setShortcut( tr("Ctrl+A") );                                           // �V���[�g�J�b�g�L�[(Ctrl+N)��ݒ�
    saveAsAction->setStatusTip( tr("Save as a spreadsheet file.") );                     // �X�e�[�^�X�o�[���b�Z�[�W��ݒ�
    connect( saveAsAction, SIGNAL( triggered() ), this, SLOT( saveAs() ) );              // �A�N�V������triggered()�V�O�i�����X���b�g�֐�saveas�ɐڑ�
    /* �ŋߊJ�����t�@�C�� */
    for ( int i = 0; i < MaxRecentFiles; ++i  )
    {
        recentFileActions[ i ] = new QAction( this );
        recentFileActions[ i ]->setVisible( false );
        connect( recentFileActions[i], SIGNAL( triggered() ),
                                 this, SLOT( openRecentFile() ) );
    }
    /* Select All�A�N�V�����𐶐� */
    selectAllAction = new QAction( tr("&All"), this );                                   // �A�N�Z�����[�^SelectAll��ݒ�
    selectAllAction->setShortcut( tr("Ctrl+A") );                                        // �V���[�g�J�b�g�L�[(Ctrl+A)��ݒ�
    selectAllAction->setStatusTip( tr("Select all the cells in the spreadsheet") );      // �X�e�[�^�X�o�[���b�Z�[�W��ݒ�
    connect( selectAllAction, SIGNAL( triggered() ),
                 spreadsheet, SLOT( selectAll() ) );                                     // �A�N�V������triggered()�V�O�i�����X���b�g�֐�selectAll�ɐڑ�
    /* Show Grid�A�N�V�����𐶐� */
    showGridAction = new QAction( tr("&Show Grid"), this );                              // �A�N�Z�����[�^ShowGrid��ݒ�
    showGridAction->setCheckable( true );                                                // ShowGrid���g�O���ɐݒ�
    showGridAction->setChecked( spreadsheet->showGrid() );                               // spreadsheet���̃f�t�H���g�l��ݒ�
    showGridAction->setStatusTip( tr("Show or hide the spreadsheet's grid") );           // �X�e�[�^�X�o�[���b�Z�[�W��ݒ�
    connect( showGridAction, SIGNAL( toggled( bool ) ),                                  // �A�N�V������triggered()�V�O�i�����X���b�g�֐�setShowGrid�ɐڑ�
                spreadsheet, SLOT( setShowGrid( bool ) ) );
    /* About�A�N�V�����𐶐� */
    aboutQtAction = new QAction( tr("About &Qt"), this );                                // �A�N�Z�����[�^About��ݒ�
    aboutQtAction->setStatusTip( tr("Show the Qt library's About box") );                // �X�e�[�^�X�o�[���b�Z�[�W��ݒ�
    connect( aboutQtAction, SIGNAL( triggered() ),                                       // �A�N�V������triggered()�V�O�i�����X���b�g�֐�aboutQt�ɐڑ�
                      qApp, SLOT( aboutQt() ) );
    /* Exit�A�N�V�����𐶐� */
    exitAction = new QAction( tr("&Exit"), this );                                       // �A�N�Z�����[�^Exit��ݒ�
    connect( exitAction, SIGNAL( triggered() ),                                          // �A�N�V������triggered()�V�O�i�����X���b�g�֐�quit�ɐڑ�
                   qApp, SLOT( quit() ) );
    /* Cut�A�N�V�����𐶐� */
    cutAction = new QAction( tr("&Cut"), this );                                         // �A�N�Z�����[�^Cut��ݒ�
    /* Copy�A�N�V�����𐶐� */
    copyAction = new QAction( tr("&Copy"), this );                                       // �A�N�Z�����[�^Copy��ݒ�
    /* Paste�A�N�V�����𐶐� */
    pasteAction = new QAction( tr("&Paste"), this );                                     // �A�N�Z�����[�^Paste��ݒ�
    /* Delete�A�N�V�����𐶐� */
    deleteAction = new QAction( tr("&Delete"), this );                                   // �A�N�Z�����[�^Delete��ݒ�
    /* SelectRow�A�N�V�����𐶐� */
    selectRowAction = new QAction( tr("Select &Row"), this );                            // �A�N�Z�����[�^SelectRow��ݒ�
    /* SelectColumn�A�N�V�����𐶐� */
    selectColumnAction = new QAction( tr("Select &Column"), this );                      // �A�N�Z�����[�^SelectColumn��ݒ�
    /* Find�A�N�V�����𐶐� */
    findAction = new QAction( tr("&Find"), this );                                       // �A�N�Z�����[�^findAction��ݒ�
	findAction->setIcon(QIcon(":/images/find.png"));                                     // �A�C�R��(New.Png)��ݒ�
	findAction->setShortcut(tr("Ctrl+F"));                                               // �V���[�g�J�b�g�L�[(Ctrl+N)��ݒ�
	findAction->setStatusTip(tr("Find a spreadsheet file."));                            // �X�e�[�^�X�o�[���b�Z�[�W��ݒ�
	connect( findAction, SIGNAL(triggered()), this, SLOT(find()));                    // �A�N�V������triggered()�V�O�i�����X���b�g�֐�newFile�ɐڑ�
    /* GoToCell�A�N�V�����𐶐� */
    goToCellAction = new QAction( tr("&GoTo Cell"), this );                              // �A�N�Z�����[�^goToCellAction��ݒ�
    /* Recalculate�A�N�V�����𐶐� */
    recalculateAction = new QAction( tr("&Recalculate"), this );                         // �A�N�Z�����[�^Recalculate��ݒ�
    /* Sort�A�N�V�����𐶐� */
    sortAction = new QAction( tr("&Sort"), this );                                       // �A�N�Z�����[�^Sort��ݒ�
    /* AutoRecalc�A�N�V�����𐶐� */
    autoRecalcAction = new QAction( tr("&AutoRecalc"), this );                           // �A�N�Z�����[�^AutoRecalc��ݒ�
    /* About�A�N�V�����𐶐� */
    aboutAction = new QAction( tr("&About"), this );                                     // �A�N�Z�����[�^About��ݒ�
}
//==============================================================================================================================================================
/**
* @fn
* @brief  ���j���[���쐬
* @author fukuda.naotaka
* @date   2017/07/24
* @param  �Ȃ�
* @return �Ȃ�
* @detail ����������������
*/
//==============================================================================================================================================================
void MainWindow::createMenus()
{
    /* File���j���[���쐬 */
    fileMenu = menuBar()->addMenu( tr("&File") );
    fileMenu->addAction( newAction );
    fileMenu->addAction( openAction );
    fileMenu->addAction( saveAction );
    fileMenu->addAction( saveAsAction );
    fileMenu->addAction( selectAllAction );
    fileMenu->addAction( showGridAction );
    fileMenu->addAction( aboutQtAction );
    separatorAction = fileMenu->addSeparator();
    for (int i = 0; i < MaxRecentFiles; ++i)
    {
        fileMenu->addAction( recentFileActions[i] );
    }
    fileMenu->addSeparator();
    fileMenu->addAction( exitAction );

    /* Edit���j���[���쐬 */
    editMenu = menuBar()->addMenu( tr("&Edit") );
    editMenu->addAction( cutAction );
    editMenu->addAction( copyAction );
    editMenu->addAction( pasteAction );
    editMenu->addAction( deleteAction );
    /* Edit�T�u���j���[���쐬 */
    selectSubMenu = editMenu->addMenu( tr("&Select") );
    selectSubMenu->addAction( selectRowAction );
    selectSubMenu->addAction( selectColumnAction );
    selectSubMenu->addAction( selectAllAction );
    /* Edit���j���[���쐬 */
    editMenu->addSeparator();
    editMenu->addAction( findAction );
    editMenu->addAction( goToCellAction );

    /* Tools���j���[���쐬 */
    toolsMenu = menuBar()->addMenu( tr("&Tools") );
    toolsMenu->addAction( recalculateAction );
    toolsMenu->addAction( sortAction );

    /* Options���j���[���쐬 */
    optionsMenu = menuBar()->addMenu( tr("&Options") );
    optionsMenu->addAction( showGridAction );
    optionsMenu->addAction( autoRecalcAction );
    optionsMenu->addSeparator();

    /* Help���j���[���쐬 */
    helpMenu = menuBar()->addMenu( tr("&Help") );
    helpMenu->addAction( aboutAction );
    helpMenu->addAction( aboutQtAction );
}
//==============================================================================================================================================================
/**
* @fn
* @brief  ����������������
* @author fukuda.naotaka
* @date   2017/07/24
* @param  �Ȃ�
* @return �Ȃ�
* @detail ����������������
*/
//==============================================================================================================================================================
void MainWindow::createContextMenu()
{
    /* �E�N���b�N���s���̃R���e�N�X�g���j���[�쐬 */
    spreadsheet->addAction( cutAction );
    spreadsheet->addAction( copyAction );
    spreadsheet->addAction( pasteAction );
    spreadsheet->setContextMenuPolicy( Qt::ActionsContextMenu );
}
//==============================================================================================================================================================
/**
* @fn
* @brief  ����������������
* @author fukuda.naotaka
* @date   2017/07/24
* @param  �Ȃ�
* @return �Ȃ�
* @detail ����������������
*/
//==============================================================================================================================================================
void MainWindow::createToolBars()
{
    fileToolBar = addToolBar( tr("&File") );
    fileToolBar->addAction( newAction );
    fileToolBar->addAction( openAction );
    fileToolBar->addAction( saveAction );

    editToolBar = addToolBar( tr("&Edit") );
    editToolBar->addAction( cutAction );
    editToolBar->addAction( copyAction );
    editToolBar->addAction( pasteAction );
    editToolBar->addSeparator();
    editToolBar->addAction( findAction );
    editToolBar->addAction( goToCellAction );
}
//==============================================================================================================================================================
/**
* @fn
* @brief  ����������������
* @author fukuda.naotaka
* @date   2017/07/24
* @param  �Ȃ�
* @return �Ȃ�
* @detail ����������������
*/
//==============================================================================================================================================================
void MainWindow::createStatusBar()
{
    locationLabel = new QLabel(" W999 ");
    locationLabel->setAlignment( Qt::AlignCenter );
    locationLabel->setMinimumSize( locationLabel->sizeHint() );

    formulaLabel = new QLabel;
    formulaLabel->setIndent( 3 );

    statusBar()->addWidget( locationLabel );
    statusBar()->addWidget( formulaLabel, 1 );

    connect( spreadsheet, SIGNAL( currentCellChanged( int, int, int, int ) ),
                    this, SLOT( updateStatusBar() ) );
    connect( spreadsheet, SIGNAL( modified() ),
                    this, SLOT( spreadsheetModified() ) );

    updateStatusBar();
}
//==============================================================================================================================================================
/**
* @fn
* @brief  ����������������
* @author fukuda.naotaka
* @date   2017/07/24
* @param  �Ȃ�
* @return �Ȃ�
* @detail ����������������
*/
//==============================================================================================================================================================
void MainWindow::readSettings()
{

}
//==============================================================================================================================================================
/**
* @fn
* @brief  ����������������
* @author fukuda.naotaka
* @date   2017/07/24
* @param  �Ȃ�
* @return �Ȃ�
* @detail ����������������
*/
//==============================================================================================================================================================
void MainWindow::writeSettings()
{

}
//==============================================================================================================================================================
/**
* @fn
* @brief  �C����ۑ����邩������
* @author fukuda.naotaka
* @date   2017/09/10
* @param  �Ȃ�
* @return �Ȃ�
* @detail ����������������
*/
//==============================================================================================================================================================
bool MainWindow::okToContinue()
{
    if ( isWindowModified() )
    {
        int ret = QMessageBox::warning( this, tr( "Spreadsheet" ),
                            tr( "The document has been modified.\n"
                                "Do you want to save your changes?" ),
                            QMessageBox::Yes | QMessageBox::Default,
                            QMessageBox::No,
                            QMessageBox::Cancel | QMessageBox::Escape );
        if ( ret == QMessageBox::Yes )
        {
            return save();
        }
        else if ( ret == QMessageBox::Cancel )
        {
            return false;
        }
        return true;
    }
}
//==============================================================================================================================================================
/**
* @fn
* @brief  �t�@�C���������[�h
* @author fukuda.naotaka
* @date   2017/09/10
* @param  �Ȃ�
* @return �Ȃ�
* @detail ����������������
*/
//==============================================================================================================================================================
bool MainWindow::loadFile( const QString &fileName )
{
    if ( !spreadsheet->readFile( fileName) )
    {
        statusBar()->showMessage( tr( "Loading canceled" ), 2000 );
        return false;
    }

    setCurrentFile( fileName );
    statusBar()->showMessage( tr( "File loaded" ), 2000 );
    return true;
}
//==============================================================================================================================================================
/**
* @fn
* @brief  ����������������
* @author fukuda.naotaka
* @date   2017/09/10
* @param  �Ȃ�
* @return �Ȃ�
* @detail ����������������
*/
//==============================================================================================================================================================
bool MainWindow::saveFile(const QString &fileName)
{
    if ( !spreadsheet->writeFile( fileName ) )
    {
        statusBar()->showMessage( tr( "Saving canceled" ), 2000 );
        return false;
    }
    setCurrentFile( fileName );
    statusBar()->showMessage( tr( "File saved" ), 2000 );
    return true;
}
//==============================================================================================================================================================
/**
* @fn
* @brief  �ҏW���̃t�@�C����ݒ�
* @author fukuda.naotaka
* @date   2017/09/10
* @param  �Ȃ�
* @return �Ȃ�
* @detail ����������������
*/
//==============================================================================================================================================================
void MainWindow::setCurrentFile( const QString &fileName )
{
    curFile = fileName;
    setWindowModified( false );

    QString shownName = "Untitled";
    if ( !curFile.isEmpty() )
    {
        shownName = strippedName( curFile );
        recentFiles.removeAll( curFile );
        recentFiles.prepend( curFile );
        updateRecentFileActions();
    }
    setWindowTitle(tr("%1[*] - %2").arg( shownName )
                                   .arg( tr( "Spreadsheet" ) ) );
}
//==============================================================================================================================================================
/**
* @fn
* @brief  �ŋߎg�p�����t�@�C���X�V����
* @author fukuda.naotaka
* @date   2017/09/10
* @param  �Ȃ�
* @return �Ȃ�
* @detail ����������������
*/
//==============================================================================================================================================================
void MainWindow::updateRecentFileActions()
{
    QMutableStringListIterator i( recentFiles );
    while ( i.hasNext() ) {
        if ( !QFile::exists( i.next() ) )
        {
            i.remove();
        }
    }

    for (int j = 0; j < MaxRecentFiles; ++j)
    {
        if (j < recentFiles.count())
        {
            QString text = tr("&%1 %2")
                .arg(j + 1)
                .arg(strippedName(recentFiles[j]));
            recentFileActions[j]->setText(text);
            recentFileActions[j]->setData(recentFiles[j]);
            recentFileActions[j]->setVisible(true);
        }
        else
        {
            recentFileActions[j]->setVisible(false);
        }
    }
    separatorAction->setVisible( !recentFiles.isEmpty() );
}
//==============================================================================================================================================================
/**
* @fn
* @brief  ����������������
* @author fukuda.naotaka
* @date   2017/07/24
* @param  �Ȃ�
* @return �Ȃ�
* @detail ����������������
*/
//==============================================================================================================================================================
QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo( fullFileName ).fileName();
}
//==============================================================================================================================================================
/**
* @fn
* @brief  ����������������
* @author fukuda.naotaka
* @date   2017/07/24
* @param  �Ȃ�
* @return �Ȃ�
* @detail ����������������
*/
//==============================================================================================================================================================
void MainWindow::newFile()
{
    if ( maybeSave() )
    {
        spreadsheet->clear();
        setCurrentFile("");
    }
}
//==============================================================================================================================================================
/**
* @fn
* @brief  �t�@�C�����J��
* @author fukuda.naotaka
* @date   2017/09/10
* @param  �Ȃ�
* @return �Ȃ�
* @detail 
*/
//==============================================================================================================================================================
void MainWindow::open()
{
    if ( okToContinue() )
    {
        QString fileName = QFileDialog::getOpenFileName( this,
            tr( "Open Spreadsheet" ), ".",
            tr( "Spreadsheet files (*.sp)" ) );
        if ( !fileName.isEmpty() )
        {
            loadFile( fileName );
        }
    }
}
//==============================================================================================================================================================
/**
* @fn
* @brief  �ۑ�����
* @author fukuda.naotaka
* @date   2017/09/10
* @param  �Ȃ�
* @return bool �ۑ�����
* @detail 
*/
//==============================================================================================================================================================
bool MainWindow::save()
{
    if ( curFile.isEmpty() )
    {
        return saveAs();
    }
    else
    {
        return saveFile( curFile );
    }
}
//==============================================================================================================================================================
/**
* @fn
* @brief  �ʖ��ŕۑ�����
* @author fukuda.naotaka
* @date   2017/09/10
* @param  �Ȃ�
* @return bool �ʖ��ŕۑ�����
* @detail 
*/
//==============================================================================================================================================================
bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName( this,
                               tr( "Save Spreadsheet" ), ".",
                               tr( "Spreadsheet files (*.sp)") );
    if ( fileName.isEmpty() )
    {
        return false;
    }
    return saveFile( fileName );
}
//==============================================================================================================================================================
/**
* @fn
* @brief  ��������
* @author fukuda.naotaka
* @date   2017/09/10
* @param  �Ȃ�
* @return �Ȃ�
* @detail ����������������
*/
//==============================================================================================================================================================
void MainWindow::find()
{
	if( !findDialog )
	{
		findDialog = new FindDialog( this );
		connect( findDialog,  SIGNAL( findNext( const QString &, Qt::CaseSensitivity ) ),
			     spreadsheet, SLOT(   findNext( const QString &, Qt::CaseSensitivity ) ) );
		connect( findDialog,  SIGNAL( findPrev( const QString &, Qt::CaseSensitivity ) ),
			     spreadsheet, SLOT(   findPrev( const QString &, Qt::CaseSensitivity ) ) );
	}
	findDialog->show();
	findDialog->activateWindow();
}
//==============================================================================================================================================================
/**
* @fn
* @brief  ����������������
* @author fukuda.naotaka
* @date   2017/07/24
* @param  �Ȃ�
* @return �Ȃ�
* @detail ����������������
*/
//==============================================================================================================================================================
void MainWindow::goToCell()
{

}
//==============================================================================================================================================================
/**
* @fn
* @brief  ����������������
* @author fukuda.naotaka
* @date   2017/07/24
* @param  �Ȃ�
* @return �Ȃ�
* @detail ����������������
*/
//==============================================================================================================================================================
void MainWindow::sort()
{

}
//==============================================================================================================================================================
/**
* @fn
* @brief  ����������������
* @author fukuda.naotaka
* @date   2017/07/24
* @param  �Ȃ�
* @return �Ȃ�
* @detail ����������������
*/
//==============================================================================================================================================================
void MainWindow::about()
{

}

void MainWindow::updateCellIndicators()
{

}
//==============================================================================================================================================================
/**
* @fn
* @brief  ����������������
* @author fukuda.naotaka
* @date   2017/07/24
* @param  �Ȃ�
* @return �Ȃ�
* @detail ����������������
*/
//==============================================================================================================================================================
void MainWindow::updateStatusBar()
{
    locationLabel->setText( spreadsheet->currentLocation() );
    formulaLabel->setText( spreadsheet->currentFormula() );
}
//==============================================================================================================================================================
/**
* @fn
* @brief  ����������������
* @author fukuda.naotaka
* @date   2017/07/24
* @param  �Ȃ�
* @return �Ȃ�
* @detail ����������������
*/
//==============================================================================================================================================================
void MainWindow::spreadsheetModified()
{
    setWindowModified( true );
    updateStatusBar();
}
//==============================================================================================================================================================
/**
* @fn
* @brief  �ŋߎg�p�����t�@�C���J������
* @author fukuda.naotaka
* @date   2017/09/10
* @param  �Ȃ�
* @return �Ȃ�
* @detail ����������������
*/
//==============================================================================================================================================================
void MainWindow::openRecentFile()
{
    if ( okToContinue() )
    {
        QAction *action = qobject_cast<QAction *>( sender() );
        if( action )
        { 
            loadFile( action->data().toString() );
        }
    }
}
//==============================================================================================================================================================
/**
* @fn
* @brief  ���鏈��
* @author fukuda.naotaka
* @date   2017/09/10
* @param  �Ȃ�
* @return �Ȃ�
* @detail ����������������
*/
//==============================================================================================================================================================
void MainWindow::closeEvent(QCloseEvent *event)
{
    if ( okToContinue() )
    {
        writeSettings();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}
//==============================================================================================================================================================
/**
* @fn
* @brief  ����������������
* @author fukuda.naotaka
* @date   2017/08/04
* @param  �Ȃ�
* @return bool �ۑ����ꂽ�H
* @detail 
*/
//==============================================================================================================================================================
bool MainWindow::maybeSave()
{
    return true;
}