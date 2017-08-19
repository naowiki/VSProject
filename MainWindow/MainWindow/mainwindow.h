//============================================================================================================
/**
* @file   mainwindow.h
* @brief  メインウィンドウクラスヘッダファイル
* @author fukuda.naotaka
* @date   2017/07/24
*/
//============================================================================================================
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//#include <QAction>
class QAction;
//class QMenu;
//class QMenuBar;
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
//#include <FindDialog>
#include "finddialog.h"
#include "sortdialog.h"
//#include "spreadsheet.h"
class Spreadsheet;


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();

protected:
	void closeEvent( QCloseEvent *event );

private slots:
	void newFile();
	void open();
	bool save();
	bool saveAs();
	bool maybeSave();
	void find();
	void goToCell();
	void sort();
	void about();
	void updateCellIndicators();
	void updateStatusBar();
	void spreadsheetModified();
    void openRecentFile();

private:
	void createActions();
	void createMenus();
	void createContextMenu();
	void createToolBars();
	void createStatusBar();
	void readSettings();
	void writeSettings();
	bool okToContinue();
	void loadFile( const QString &filename );
	void saveFile( const QString &filename );
	void setCurrentFile( const QString &filename );
	void updateRecentFileActions();
	QString strippedName( const QString &fullFileName );

	Spreadsheet *spreadsheet;
	FindDialog  *findDialog;
    SortDialog  *sortDialog;
	QLabel      *locationLabel;
	QLabel      *formulaLabel;
	QStringList recentFiles;
	QString     curFile;

	enum { MaxRecentFiles = 5 };
	QAction     *recentFileActions[ MaxRecentFiles ];
	QAction     *separatorAction;

	QMenu       *fileMenu;
	QMenu       *editMenu;
	QMenu       *toolsMenu;
	QMenu       *optionsMenu;
	QMenu       *helpMenu;
    QMenu       *selectSubMenu;
	//・・・
	QToolBar    *fileToolBar;
	QToolBar    *editToolBar;
    /* アクションを生成 */
	QAction     *newAction;                                      // Newアクション
	QAction     *openAction;                                     // Openアクション
	QAction     *saveAction;                                     // Saveアクション
	QAction     *saveAsAction;                                   // SaveAsアクション
    QAction     *selectAllAction;                                // SelectAllアクション
    QAction     *showGridAction;                                 // ShowGridアクション
    QAction     *exitAction;                                     // Exitアクション
    QAction     *cutAction;                                      // Cutアクション
    QAction     *copyAction;                                     // Copyアクション
    QAction     *pasteAction;                                    // Pasteアクション
    QAction     *deleteAction;                                   // Deleteアクション
    QAction     *selectRowAction;                                // SelectRowアクション
    QAction     *selectColumnAction;                             // SelectColumnアクション
    QAction     *findAction;                                     // Findアクション
    QAction     *goToCellAction;                                 // GoToCellアクション
    QAction     *recalculateAction;                              // Recalculateアクション
    QAction     *sortAction;                                     // Sortアクション
    QAction     *autoRecalcAction;                               // AutoRecalcアクション
    QAction     *aboutAction;                                    // Aboutアクション
	//・・・
	QAction     *aboutQtAction;
};

#endif