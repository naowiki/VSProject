//==============================================================================================================================================================
/**
* @file   mainwindow.cpp
* @brief  メインウィンドウクラス実装ファイル
* @author fukuda.naotaka
* @date   2017/07/24
*/
//==============================================================================================================================================================
#include <QtGui>
#include <QTableWidgetSelectionRange>
#include "mainwindow.h"
#include "finddialog.h"
#include "sortdialog.h"
#include "spreadsheet.h"
#include "gotocelldialog.h"
//==============================================================================================================================================================
/**
* @fn
* @brief  コンストラクタ
* @param  なし
* @return なし
* @detail 
*/
//==============================================================================================================================================================
MainWindow::MainWindow()
{
    resize(640, 480);
    // スプレッドシートを表示
    spreadsheet = new Spreadsheet;
    setCentralWidget( spreadsheet );

    // 検索ダイアログを表示
    //findDialog = new FindDialog;
    //setCentralWidget( findDialog );
    // ソートダイアログを表示
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
* @brief  アクションを生成
* @author fukuda.naotaka
* @date   2017/07/27
* @param  なし
* @return なし
* @detail New,Open,Save,SaveAsアクションを生成
*/
//==============================================================================================================================================================
void MainWindow::createActions()
{
    /* Newアクションを生成 */
    newAction = new QAction( tr("&New"), this );                                         // アクセラレータNewを設定
    newAction->setIcon( QIcon(":/images/new.png") );                                     // アイコン(New.Png)を設定
    newAction->setShortcut( tr("Ctrl+N") );                                              // ショートカットキー(Ctrl+N)を設定
    newAction->setStatusTip( tr("Create a New spreadsheet file.") );                     // ステータスバーメッセージを設定
    connect( newAction, SIGNAL( triggered() ), this, SLOT( newFile() ) );                // アクションのtriggered()シグナルをスロット関数newFileに接続
    /* Openアクションを生成 */
    openAction = new QAction( tr("&Open"), this );                                       // アクセラレータOpenを設定
    openAction->setIcon( QIcon(":/images/open.png") );                                   // アイコン(open.Png)を設定
    openAction->setShortcut( tr("Ctrl+O") );                                             // ショートカットキー(Ctrl+N)を設定
    openAction->setStatusTip( tr("Open a spreadsheet file.") );                          // ステータスバーメッセージを設定
    connect( openAction, SIGNAL( triggered() ), this, SLOT( open() ) );                  // アクションのtriggered()シグナルをスロット関数openに接続
    /* Saveアクションを生成 */
    saveAction = new QAction( tr("&Save"), this );                                       // アクセラレータSaveを設定
    saveAction->setIcon( QIcon(":/images/save.png") );                                   // アイコン(save.Png)を設定
    saveAction->setShortcut( tr("Ctrl+S") );                                             // ショートカットキー(Ctrl+N)を設定
    saveAction->setStatusTip( tr("Save a spreadsheet file.") );                          // ステータスバーメッセージを設定
    connect( saveAction, SIGNAL( triggered() ), this, SLOT( save() ) );                  // アクションのtriggered()シグナルをスロット関数saveFileに接続
    /* SaveAsアクションを生成 */
    saveAsAction = new QAction( tr("Save&As"), this );                                   // アクセラレータSaveAsを設定
    saveAsAction->setIcon( QIcon(":/images/saveas.png") );                               // アイコン(save.Png)を設定
    saveAsAction->setShortcut( tr("Ctrl+A") );                                           // ショートカットキー(Ctrl+N)を設定
    saveAsAction->setStatusTip( tr("Save as a spreadsheet file.") );                     // ステータスバーメッセージを設定
    connect( saveAsAction, SIGNAL( triggered() ), this, SLOT( saveAs() ) );              // アクションのtriggered()シグナルをスロット関数saveasに接続
    /* 最近開いたファイル */
    for ( int i = 0; i < MaxRecentFiles; ++i  )
    {
        recentFileActions[ i ] = new QAction( this );
        recentFileActions[ i ]->setVisible( false );
        connect( recentFileActions[i], SIGNAL( triggered() ),
                                 this, SLOT( openRecentFile() ) );
    }
    /* Select Allアクションを生成 */
    selectAllAction = new QAction( tr("&All"), this );                                   // アクセラレータSelectAllを設定
    selectAllAction->setShortcut( tr("Ctrl+A") );                                        // ショートカットキー(Ctrl+A)を設定
    selectAllAction->setStatusTip( tr("Select all the cells in the spreadsheet") );      // ステータスバーメッセージを設定
    connect( selectAllAction, SIGNAL( triggered() ),
                 spreadsheet, SLOT( selectAll() ) );                                     // アクションのtriggered()シグナルをスロット関数selectAllに接続
    /* Show Gridアクションを生成 */
    showGridAction = new QAction( tr("&Show Grid"), this );                              // アクセラレータShowGridを設定
    showGridAction->setCheckable( true );                                                // ShowGridをトグルに設定
    showGridAction->setChecked( spreadsheet->showGrid() );                               // spreadsheet側のデフォルト値を設定
    showGridAction->setStatusTip( tr("Show or hide the spreadsheet's grid") );           // ステータスバーメッセージを設定
    connect( showGridAction, SIGNAL( toggled( bool ) ),                                  // アクションのtriggered()シグナルをスロット関数setShowGridに接続
                spreadsheet, SLOT( setShowGrid( bool ) ) );
    /* AboutQtアクションを生成 */
    aboutQtAction = new QAction( tr("About &Qt"), this );                                // アクセラレータAboutを設定
    aboutQtAction->setStatusTip( tr("Show the Qt library's About box") );                // ステータスバーメッセージを設定
    connect( aboutQtAction, SIGNAL( triggered() ),                                       // アクションのtriggered()シグナルをスロット関数aboutQtに接続
                      qApp, SLOT( aboutQt() ) );
    /* Exitアクションを生成 */
    exitAction = new QAction( tr("&Exit"), this );                                       // アクセラレータExitを設定
    connect( exitAction, SIGNAL( triggered() ),                                          // アクションのtriggered()シグナルをスロット関数quitに接続
                   qApp, SLOT( quit() ) );
    /* Cutアクションを生成 */
    cutAction = new QAction( tr("&Cut"), this );                                         // アクセラレータCutを設定
    /* Copyアクションを生成 */
    copyAction = new QAction( tr("&Copy"), this );                                       // アクセラレータCopyを設定
    /* Pasteアクションを生成 */
    pasteAction = new QAction( tr("&Paste"), this );                                     // アクセラレータPasteを設定
    /* Deleteアクションを生成 */
    deleteAction = new QAction( tr("&Delete"), this );                                   // アクセラレータDeleteを設定
    /* SelectRowアクションを生成 */
    selectRowAction = new QAction( tr("Select &Row"), this );                            // アクセラレータSelectRowを設定
    /* SelectColumnアクションを生成 */
    selectColumnAction = new QAction( tr("Select &Column"), this );                      // アクセラレータSelectColumnを設定
    /* Findアクションを生成 */
    findAction = new QAction( tr("&Find"), this );                                       // アクセラレータfindActionを設定
	findAction->setIcon(QIcon(":/images/find.png"));                                     // アイコン(New.Png)を設定
	findAction->setShortcut(tr("Ctrl+F"));                                               // ショートカットキー(Ctrl+N)を設定
	findAction->setStatusTip(tr("Find a spreadsheet file."));                            // ステータスバーメッセージを設定
	connect( findAction, SIGNAL(triggered()), this, SLOT(find()));                    // アクションのtriggered()シグナルをスロット関数newFileに接続
    /* GoToCellアクションを生成 */
    goToCellAction = new QAction( tr("&GoTo Cell"), this );                              // アクセラレータgoToCellActionを設定
    goToCellAction->setIcon( QIcon( ":/images/goto.png" ) );                                     // アイコン(New.Png)を設定
    goToCellAction->setShortcut( tr( "Ctrl+G" ) );                                               // ショートカットキー(Ctrl+N)を設定
    goToCellAction->setStatusTip( tr( "Go to the Cell." ) );                            // ステータスバーメッセージを設定
    connect( goToCellAction, SIGNAL( triggered() ), this, SLOT( goToCell() ) );                    // アクションのtriggered()シグナルをスロット関数newFileに接続
    /* Recalculateアクションを生成 */
    recalculateAction = new QAction( tr("&Recalculate"), this );                         // アクセラレータRecalculateを設定
    /* Sortアクションを生成 */
    sortAction = new QAction( tr("&Sort"), this );                                       // アクセラレータSortを設定
	sortAction->setIcon(QIcon(":/images/sort.png"));                                     // アイコン(New.Png)を設定
	sortAction->setShortcut(tr("Ctrl+S"));                                               // ショートカットキー(Ctrl+N)を設定
	sortAction->setStatusTip(tr("Sort Cells."));                            // ステータスバーメッセージを設定
	connect(sortAction, SIGNAL(triggered()), this, SLOT(sort()));                    // アクションのtriggered()シグナルをスロット関数newFileに接続
    /* AutoRecalcアクションを生成 */
    autoRecalcAction = new QAction( tr("&AutoRecalc"), this );                           // アクセラレータAutoRecalcを設定
    /* Aboutアクションを生成 */
    aboutAction = new QAction( tr("&About"), this );                                     // アクセラレータAboutを設定
	aboutAction->setIcon(QIcon(":/images/about.png"));                                     // アイコン(New.Png)を設定
	aboutAction->setShortcut(tr("Ctrl+A"));                                               // ショートカットキー(Ctrl+N)を設定
	aboutAction->setStatusTip(tr("About"));                            // ステータスバーメッセージを設定
	connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));                    // アクションのtriggered()シグナルをスロット関数newFileに接続

}
//==============================================================================================================================================================
/**
* @fn
* @brief  メニューを作成
* @author fukuda.naotaka
* @date   2017/07/24
* @param  なし
* @return なし
* @detail ｘｘｘｘｘｘｘｘ
*/
//==============================================================================================================================================================
void MainWindow::createMenus()
{
    /* Fileメニューを作成 */
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

    /* Editメニューを作成 */
    editMenu = menuBar()->addMenu( tr("&Edit") );
    editMenu->addAction( cutAction );
    editMenu->addAction( copyAction );
    editMenu->addAction( pasteAction );
    editMenu->addAction( deleteAction );
    /* Editサブメニューを作成 */
    selectSubMenu = editMenu->addMenu( tr("&Select") );
    selectSubMenu->addAction( selectRowAction );
    selectSubMenu->addAction( selectColumnAction );
    selectSubMenu->addAction( selectAllAction );
    /* Editメニューを作成 */
    editMenu->addSeparator();
    editMenu->addAction( findAction );
    editMenu->addAction( goToCellAction );

    /* Toolsメニューを作成 */
    toolsMenu = menuBar()->addMenu( tr("&Tools") );
    toolsMenu->addAction( recalculateAction );
    toolsMenu->addAction( sortAction );

    /* Optionsメニューを作成 */
    optionsMenu = menuBar()->addMenu( tr("&Options") );
    optionsMenu->addAction( showGridAction );
    optionsMenu->addAction( autoRecalcAction );
    optionsMenu->addSeparator();

    /* Helpメニューを作成 */
    helpMenu = menuBar()->addMenu( tr("&Help") );
    helpMenu->addAction( aboutAction );
    helpMenu->addAction( aboutQtAction );
}
//==============================================================================================================================================================
/**
* @fn
* @brief  ｘｘｘｘｘｘｘｘ
* @author fukuda.naotaka
* @date   2017/07/24
* @param  なし
* @return なし
* @detail ｘｘｘｘｘｘｘｘ
*/
//==============================================================================================================================================================
void MainWindow::createContextMenu()
{
    /* 右クリック実行時のコンテクストメニュー作成 */
    spreadsheet->addAction( cutAction );
    spreadsheet->addAction( copyAction );
    spreadsheet->addAction( pasteAction );
    spreadsheet->setContextMenuPolicy( Qt::ActionsContextMenu );
}
//==============================================================================================================================================================
/**
* @fn
* @brief  ｘｘｘｘｘｘｘｘ
* @author fukuda.naotaka
* @date   2017/07/24
* @param  なし
* @return なし
* @detail ｘｘｘｘｘｘｘｘ
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
* @brief  ｘｘｘｘｘｘｘｘ
* @author fukuda.naotaka
* @date   2017/07/24
* @param  なし
* @return なし
* @detail ｘｘｘｘｘｘｘｘ
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
* @brief  ｘｘｘｘｘｘｘｘ
* @author fukuda.naotaka
* @date   2017/07/24
* @param  なし
* @return なし
* @detail ｘｘｘｘｘｘｘｘ
*/
//==============================================================================================================================================================
void MainWindow::readSettings()
{
    QSettings settings("Software Inc.", "Spreadshet");

    QRect rect = settings.value( "geometry",
                                 QRect( 200, 200, 640, 480 ) ).toRect();

    move( rect.topLeft() );
    resize( rect.size() );

    recentFiles = settings.value( "recentFiles" ).toStringList();
    updateRecentFileActions();

    bool showGrid = settings.value( "showGrid", true ).toBool();
    showGridAction->setChecked( showGrid );

    bool autoRecalc = settings.value( "autoRecalc", true ).toBool();
    autoRecalcAction->setChecked( autoRecalc );
}
//==============================================================================================================================================================
/**
* @fn
* @brief  ｘｘｘｘｘｘｘｘ
* @author fukuda.naotaka
* @date   2017/07/24
* @param  なし
* @return なし
* @detail ｘｘｘｘｘｘｘｘ
*/
//==============================================================================================================================================================
void MainWindow::writeSettings()
{
    QSettings settings("Software Inc.", "Spreadshet");

    settings.setValue( "geometry", geometry() );
    settings.setValue( "recentFiles", recentFiles );
    settings.setValue( "showGrid", showGridAction->isChecked() );
    settings.setValue( "autoRecalc", autoRecalcAction->isChecked() );
    settings.beginGroup( "findDialog" );
    settings.setValue( "matchCase", findDialog->caseCheckBox->isChecked() );
    settings.setValue( "searchBackward", findDialog->backwardCheckBox->isChecked() );
	settings.endGroup();
}
//==============================================================================================================================================================
/**
* @fn
* @brief  修正を保存するかを決定
* @author fukuda.naotaka
* @date   2017/09/10
* @param  なし
* @return なし
* @detail ｘｘｘｘｘｘｘｘ
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
* @brief  ファイル名をロード
* @author fukuda.naotaka
* @date   2017/09/10
* @param  なし
* @return なし
* @detail ｘｘｘｘｘｘｘｘ
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
* @brief  ｘｘｘｘｘｘｘｘ
* @author fukuda.naotaka
* @date   2017/09/10
* @param  なし
* @return なし
* @detail ｘｘｘｘｘｘｘｘ
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
* @brief  編集中のファイルを設定
* @author fukuda.naotaka
* @date   2017/09/10
* @param  なし
* @return なし
* @detail ｘｘｘｘｘｘｘｘ
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
* @brief  最近使用したファイル更新処理
* @author fukuda.naotaka
* @date   2017/09/10
* @param  なし
* @return なし
* @detail ｘｘｘｘｘｘｘｘ
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
* @brief  ｘｘｘｘｘｘｘｘ
* @author fukuda.naotaka
* @date   2017/07/24
* @param  なし
* @return なし
* @detail ｘｘｘｘｘｘｘｘ
*/
//==============================================================================================================================================================
QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo( fullFileName ).fileName();
}
//==============================================================================================================================================================
/**
* @fn
* @brief  ｘｘｘｘｘｘｘｘ
* @author fukuda.naotaka
* @date   2017/07/24
* @param  なし
* @return なし
* @detail ｘｘｘｘｘｘｘｘ
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
* @brief  ファイルを開く
* @author fukuda.naotaka
* @date   2017/09/10
* @param  なし
* @return なし
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
* @brief  保存処理
* @author fukuda.naotaka
* @date   2017/09/10
* @param  なし
* @return bool 保存成否
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
* @brief  別名で保存処理
* @author fukuda.naotaka
* @date   2017/09/10
* @param  なし
* @return bool 別名で保存成否
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
* @brief  検索処理
* @author fukuda.naotaka
* @date   2017/09/10
* @param  なし
* @return なし
* @detail ｘｘｘｘｘｘｘｘ
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
* @brief  ｘｘｘｘｘｘｘｘ
* @author fukuda.naotaka
* @date   2017/07/24
* @param  なし
* @return なし
* @detail ｘｘｘｘｘｘｘｘ
*/
//==============================================================================================================================================================
void MainWindow::goToCell()
{
    GoToCellDialog *dialog = new GoToCellDialog( this );
    if ( dialog->exec() ) {
        QString str = dialog->lineEdit->text().toUpper();
        spreadsheet->setCurrentCell( str.mid( 1 ).toInt() - 1,
                                     str[0].unicode() - 'A' );
    }
    delete dialog;
}
//==============================================================================================================================================================
/**
* @fn
* @brief  ソート処理
* @author fukuda.naotaka
* @date   2017/09/21
* @param  なし
* @return なし
* @detail ｘｘｘｘｘｘｘｘ
*/
//==============================================================================================================================================================
void MainWindow::sort()
{
    SortDialog dialog(this);
    QTableWidgetSelectionRange range = spreadsheet->selectedRange();
    dialog.setColumnRange( 'A' + range.leftColumn(),
                           'A' + range.rightColumn() );
    if ( dialog.exec() ) {
        SpreadsheetCompare compare;
        compare.keys[ 0 ] =
            dialog.primaryColumnCombo->currentIndex();
        compare.keys[ 1 ] =
            dialog.secondaryColumnCombo->currentIndex() - 1;
        compare.keys[ 2 ] =
            dialog.tertiaryColumnCombo->currentIndex() - 1;
        compare.ascending[ 0 ] =
            ( dialog.primaryOrderCombo->currentIndex() == 0 );
        compare.ascending[ 1 ] =
            ( dialog.secondaryOrderCombo->currentIndex() == 0 );
        compare.ascending[ 2 ] =
            ( dialog.tertiaryOrderCombo->currentIndex() == 0 );
        spreadsheet->sort( compare );
    }
}
//==============================================================================================================================================================
/**
* @fn
* @brief  ｘｘｘｘｘｘｘｘ
* @author fukuda.naotaka
* @date   2017/07/24
* @param  なし
* @return なし
* @detail ｘｘｘｘｘｘｘｘ
*/
//==============================================================================================================================================================
void MainWindow::about()
{
    QMessageBox::about(this, tr("About Spreadsheet"),
        tr("<h2>Spreadsheet 1.0</h2>"
           "<p>Copyright &copy; 2006 Software Inc."
           "<p>Spreadsheet is a small application that "
           "demonstrates <b>QAction</b>, <b>QMainWindow</b>, "
           "<b>QMenuBar</b>, <b>QStatusbar</b>, "
           "<b>>QToolBar</b>, and many other Qt classes." ) );
}

void MainWindow::updateCellIndicators()
{

}
//==============================================================================================================================================================
/**
* @fn
* @brief  ｘｘｘｘｘｘｘｘ
* @author fukuda.naotaka
* @date   2017/07/24
* @param  なし
* @return なし
* @detail ｘｘｘｘｘｘｘｘ
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
* @brief  ｘｘｘｘｘｘｘｘ
* @author fukuda.naotaka
* @date   2017/07/24
* @param  なし
* @return なし
* @detail ｘｘｘｘｘｘｘｘ
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
* @brief  最近使用したファイル開く処理
* @author fukuda.naotaka
* @date   2017/09/10
* @param  なし
* @return なし
* @detail ｘｘｘｘｘｘｘｘ
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
* @brief  閉じる処理
* @author fukuda.naotaka
* @date   2017/09/10
* @param  なし
* @return なし
* @detail ｘｘｘｘｘｘｘｘ
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
* @brief  ｘｘｘｘｘｘｘｘ
* @author fukuda.naotaka
* @date   2017/08/04
* @param  なし
* @return bool 保存された？
* @detail 
*/
//==============================================================================================================================================================
bool MainWindow::maybeSave()
{
    return true;
}