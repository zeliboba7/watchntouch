/********************************************************************************
** Form generated from reading UI file 'window.ui'
**
** Created: Wed Dec 29 23:25:15 2010
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDockWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QTextBrowser>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *openAction;
    QAction *exitAction;
    QAction *increaseScaleAction;
    QAction *decreaseScaleAction;
    QAction *documentControlsAction;
    QAction *selectedTextAction;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QMenuBar *menubar;
    QMenu *menu_File;
    QMenu *menu_Windows;
    QStatusBar *statusbar;
    QDockWidget *controlsDockWidget;
    QWidget *dockWidgetContents;
    QHBoxLayout *hboxLayout;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *_2;
    QLabel *pageLabel;
    QSpinBox *pageSpinBox;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *_3;
    QLabel *searchLabel;
    QLineEdit *searchLineEdit;
    QComboBox *searchComboBox;
    QPushButton *findButton;
    QPushButton *clearButton;
    QSpacerItem *spacerItem;
    QLabel *label;
    QComboBox *scaleComboBox;
    QSpacerItem *horizontalSpacer_3;
    QDockWidget *selectionDockWidget;
    QWidget *dockWidgetContents_2;
    QHBoxLayout *horizontalLayout_2;
    QTextBrowser *textViewer;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(858, 600);
        MainWindow->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks|QMainWindow::ForceTabbedDocks);
        openAction = new QAction(MainWindow);
        openAction->setObjectName(QString::fromUtf8("openAction"));
        exitAction = new QAction(MainWindow);
        exitAction->setObjectName(QString::fromUtf8("exitAction"));
        increaseScaleAction = new QAction(MainWindow);
        increaseScaleAction->setObjectName(QString::fromUtf8("increaseScaleAction"));
        decreaseScaleAction = new QAction(MainWindow);
        decreaseScaleAction->setObjectName(QString::fromUtf8("decreaseScaleAction"));
        documentControlsAction = new QAction(MainWindow);
        documentControlsAction->setObjectName(QString::fromUtf8("documentControlsAction"));
        documentControlsAction->setCheckable(true);
        documentControlsAction->setChecked(true);
        selectedTextAction = new QAction(MainWindow);
        selectedTextAction->setObjectName(QString::fromUtf8("selectedTextAction"));
        selectedTextAction->setCheckable(true);
        selectedTextAction->setChecked(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        scrollArea = new QScrollArea(centralwidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollArea->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 852, 268));
        scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout->addWidget(scrollArea);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 858, 23));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menu_Windows = new QMenu(menubar);
        menu_Windows->setObjectName(QString::fromUtf8("menu_Windows"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        controlsDockWidget = new QDockWidget(MainWindow);
        controlsDockWidget->setObjectName(QString::fromUtf8("controlsDockWidget"));
        controlsDockWidget->setEnabled(true);
        controlsDockWidget->setFloating(false);
        controlsDockWidget->setFeatures(QDockWidget::AllDockWidgetFeatures);
        controlsDockWidget->setAllowedAreas(Qt::BottomDockWidgetArea|Qt::TopDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        hboxLayout = new QHBoxLayout(dockWidgetContents);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(4, 0, 4, 0);
        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(horizontalSpacer);

        _2 = new QHBoxLayout();
        _2->setObjectName(QString::fromUtf8("_2"));
        pageLabel = new QLabel(dockWidgetContents);
        pageLabel->setObjectName(QString::fromUtf8("pageLabel"));

        _2->addWidget(pageLabel);

        pageSpinBox = new QSpinBox(dockWidgetContents);
        pageSpinBox->setObjectName(QString::fromUtf8("pageSpinBox"));
        pageSpinBox->setEnabled(false);

        _2->addWidget(pageSpinBox);


        hboxLayout->addLayout(_2);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(horizontalSpacer_2);

        _3 = new QHBoxLayout();
        _3->setObjectName(QString::fromUtf8("_3"));
        searchLabel = new QLabel(dockWidgetContents);
        searchLabel->setObjectName(QString::fromUtf8("searchLabel"));
        searchLabel->setTextFormat(Qt::AutoText);

        _3->addWidget(searchLabel);

        searchLineEdit = new QLineEdit(dockWidgetContents);
        searchLineEdit->setObjectName(QString::fromUtf8("searchLineEdit"));
        searchLineEdit->setEnabled(false);

        _3->addWidget(searchLineEdit);

        searchComboBox = new QComboBox(dockWidgetContents);
        searchComboBox->setObjectName(QString::fromUtf8("searchComboBox"));
        searchComboBox->setEnabled(false);

        _3->addWidget(searchComboBox);

        findButton = new QPushButton(dockWidgetContents);
        findButton->setObjectName(QString::fromUtf8("findButton"));
        findButton->setEnabled(false);

        _3->addWidget(findButton);

        clearButton = new QPushButton(dockWidgetContents);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));
        clearButton->setEnabled(false);

        _3->addWidget(clearButton);


        hboxLayout->addLayout(_3);

        spacerItem = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        label = new QLabel(dockWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));

        hboxLayout->addWidget(label);

        scaleComboBox = new QComboBox(dockWidgetContents);
        scaleComboBox->setObjectName(QString::fromUtf8("scaleComboBox"));
        scaleComboBox->setEnabled(false);

        hboxLayout->addWidget(scaleComboBox);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(horizontalSpacer_3);

        controlsDockWidget->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(4), controlsDockWidget);
        selectionDockWidget = new QDockWidget(MainWindow);
        selectionDockWidget->setObjectName(QString::fromUtf8("selectionDockWidget"));
        selectionDockWidget->setAllowedAreas(Qt::BottomDockWidgetArea|Qt::TopDockWidgetArea);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        horizontalLayout_2 = new QHBoxLayout(dockWidgetContents_2);
        horizontalLayout_2->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        textViewer = new QTextBrowser(dockWidgetContents_2);
        textViewer->setObjectName(QString::fromUtf8("textViewer"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(textViewer->sizePolicy().hasHeightForWidth());
        textViewer->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(textViewer);

        selectionDockWidget->setWidget(dockWidgetContents_2);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(8), selectionDockWidget);
#ifndef QT_NO_SHORTCUT
        pageLabel->setBuddy(pageSpinBox);
        searchLabel->setBuddy(searchLineEdit);
        label->setBuddy(scaleComboBox);
#endif // QT_NO_SHORTCUT

        menubar->addAction(menu_File->menuAction());
        menubar->addAction(menu_Windows->menuAction());
        menu_File->addAction(openAction);
        menu_File->addAction(exitAction);
        menu_Windows->addAction(documentControlsAction);

        retranslateUi(MainWindow);
        QObject::connect(clearButton, SIGNAL(clicked()), searchLineEdit, SLOT(clear()));

        scaleComboBox->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "PDF Viewer", 0, QApplication::UnicodeUTF8));
        openAction->setText(QApplication::translate("MainWindow", "&Open...", 0, QApplication::UnicodeUTF8));
        openAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        exitAction->setText(QApplication::translate("MainWindow", "E&xit", 0, QApplication::UnicodeUTF8));
        exitAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        increaseScaleAction->setText(QApplication::translate("MainWindow", "&Increase Scale", 0, QApplication::UnicodeUTF8));
        increaseScaleAction->setShortcut(QApplication::translate("MainWindow", "Ctrl++", 0, QApplication::UnicodeUTF8));
        decreaseScaleAction->setText(QApplication::translate("MainWindow", "&Decrease Scale", 0, QApplication::UnicodeUTF8));
        decreaseScaleAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+-", 0, QApplication::UnicodeUTF8));
        documentControlsAction->setText(QApplication::translate("MainWindow", "&Document Controls", 0, QApplication::UnicodeUTF8));
        selectedTextAction->setText(QApplication::translate("MainWindow", "&Selected Text", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
        menu_Windows->setTitle(QApplication::translate("MainWindow", "&Windows", 0, QApplication::UnicodeUTF8));
        controlsDockWidget->setWindowTitle(QApplication::translate("MainWindow", "Document Controls", 0, QApplication::UnicodeUTF8));
        pageLabel->setText(QApplication::translate("MainWindow", "&Page:", 0, QApplication::UnicodeUTF8));
        searchLabel->setText(QApplication::translate("MainWindow", "&Search for:", 0, QApplication::UnicodeUTF8));
        searchComboBox->clear();
        searchComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Forwards", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "Backwards", 0, QApplication::UnicodeUTF8)
        );
        findButton->setText(QApplication::translate("MainWindow", "&Find", 0, QApplication::UnicodeUTF8));
        clearButton->setText(QApplication::translate("MainWindow", "&Clear", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "&Scale document:", 0, QApplication::UnicodeUTF8));
        scaleComboBox->clear();
        scaleComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "25%", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "50%", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "75%", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "100%", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "125%", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "150%", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "200%", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "300%", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "400%", 0, QApplication::UnicodeUTF8)
        );
        selectionDockWidget->setWindowTitle(QApplication::translate("MainWindow", "Selected Text", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
