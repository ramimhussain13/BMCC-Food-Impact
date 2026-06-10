#pragma once
#include <QMainWindow>
#include <QStackedWidget>
#include <QTabWidget>
#include <QListWidget>
#include <QLabel>
#include <QProgressBar>
#include "MenuDatabase.h"
#include "ImpactCalculator.h"
#include "WaterImpact.h"
#include "LandImpact.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onMenuItemClicked(QListWidgetItem *clicked);
    void onCompareItemClicked(QListWidgetItem *clicked);

private:
    QWidget* buildHomePage();
    QWidget* buildMenuPage();
    QWidget* buildComparePage();
    QTabWidget* buildCategoryTabs(void (MainWindow::*handler)(QListWidgetItem*));
    int scoreFor(MenuItem item);

    MenuDatabase     db;
    ImpactCalculator calc;
    QStackedWidget  *pages;
    int              impactMode;     // 0 = Carbon, 1 = Water, 2 = Land

    // menu page widgets
    QLabel          *menuImpact;
    QProgressBar    *menuMeter;
    QListWidgetItem *currentItem;    // the item currently shown on the menu page

    // compare page widgets
    MenuItem        *firstPick;
    QLabel          *compareResult;
};