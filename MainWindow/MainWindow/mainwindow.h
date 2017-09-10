//============================================================================================================
/**
* @file   mainwindow.h
* @brief  ���C���E�B���h�E�N���X�w�b�_�t�@�C��
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
#include <QMessageBox>
#include <QFileDialog>
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
    bool loadFile( const QString &filename );
    bool saveFile( const QString &filename );
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
    //�E�E�E
    QToolBar    *fileToolBar;
    QToolBar    *editToolBar;
    /* �A�N�V�����𐶐� */
    QAction     *newAction;                                      // New�A�N�V����
    QAction     *openAction;                                     // Open�A�N�V����
    QAction     *saveAction;                                     // Save�A�N�V����
    QAction     *saveAsAction;                                   // SaveAs�A�N�V����
    QAction     *selectAllAction;                                // SelectAll�A�N�V����
    QAction     *showGridAction;                                 // ShowGrid�A�N�V����
    QAction     *exitAction;                                     // Exit�A�N�V����
    QAction     *cutAction;                                      // Cut�A�N�V����
    QAction     *copyAction;                                     // Copy�A�N�V����
    QAction     *pasteAction;                                    // Paste�A�N�V����
    QAction     *deleteAction;                                   // Delete�A�N�V����
    QAction     *selectRowAction;                                // SelectRow�A�N�V����
    QAction     *selectColumnAction;                             // SelectColumn�A�N�V����
    QAction     *findAction;                                     // Find�A�N�V����
    QAction     *goToCellAction;                                 // GoToCell�A�N�V����
    QAction     *recalculateAction;                              // Recalculate�A�N�V����
    QAction     *sortAction;                                     // Sort�A�N�V����
    QAction     *autoRecalcAction;                               // AutoRecalc�A�N�V����
    QAction     *aboutAction;                                    // About�A�N�V����
    //�E�E�E
    QAction     *aboutQtAction;
};

#endif