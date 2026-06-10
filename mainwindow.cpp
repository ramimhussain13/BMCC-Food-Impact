#include "mainwindow.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QFrame>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), firstPick(nullptr), impactMode(0), currentItem(nullptr)
{
    setWindowTitle("BMCC Cafeteria Food Impact");
    resize(940, 640);

    db.loadFromJson(":/menu.json");

    pages = new QStackedWidget();
    pages->addWidget(buildHomePage());     // index 0
    pages->addWidget(buildMenuPage());     // index 1
    pages->addWidget(buildComparePage());  // index 2

    setCentralWidget(pages);
}

// builds category sub-tabs; each list connects to the given click handler
QTabWidget* MainWindow::buildCategoryTabs(void (MainWindow::*handler)(QListWidgetItem*))
{
    QString categoryNames[] = {
        "Breakfast", "Lunch", "Pizza", "BBQ",
        "Snacks", "Entrees", "Desserts", "Beverages"
    };

    QTabWidget *tabs = new QTabWidget();
    for (int c = 0; c < 8; c++) {
        QListWidget *list = new QListWidget();
        for (size_t i = 0; i < db.items.size(); i++) {
            if (db.items[i].category == c) {
                list->addItem(QString::fromStdString(db.items[i].name));
            }
        }
        connect(list, &QListWidget::itemClicked, this, handler);
        tabs->addTab(list, categoryNames[c]);
    }
    return tabs;
}

// Returns the impact score using the subclass for the current mode.
// This is where inheritance does its work: the same getScore() call
// runs different code depending on which impact object we build.
int MainWindow::scoreFor(MenuItem item)
{
    double co2   = item.impact.co2Kg;
    double water = item.impact.waterLiters;
    double land  = item.impact.landM2;

    EnvironmentalImpact *imp;
    if (impactMode == 1)
        imp = new WaterImpact(co2, water, land);
    else if (impactMode == 2)
        imp = new LandImpact(co2, water, land);
    else
        imp = new EnvironmentalImpact(co2, water, land);

    int score = imp->getScore();   // virtual call: picks the right override
    delete imp;
    return score;
}

// Home page: title, about, impact graph, and nav buttons
QWidget* MainWindow::buildHomePage()
{
    QWidget *home = new QWidget();
    QVBoxLayout *root = new QVBoxLayout(home);
    root->setContentsMargins(60, 50, 60, 50);
    root->setSpacing(22);

    QLabel *title = new QLabel("BMCC Cafeteria Food Impact");
    title->setStyleSheet("font-size: 34px; font-weight: bold; color: #ffffff;");

    QLabel *tagline = new QLabel(
        "Understand the environmental footprint of your food, and find greener choices.");
    tagline->setStyleSheet("font-size: 15px; color: #8a93a0;");
    tagline->setWordWrap(true);

    root->addWidget(title);
    root->addWidget(tagline);

    QLabel *aboutBody = new QLabel(
        "Every cafeteria item is rated by its carbon footprint using real data "
        "from Poore & Nemecek (2018). When an item has a high impact, the app "
        "suggests a lower-impact option still on the menu \u2014 so eating greener "
        "is easy and informed. Small daily swaps, across thousands of students, "
        "add up to a real reduction in emissions.");
    aboutBody->setStyleSheet(
        "font-size: 14px; color: #d4d9e0;"
        "background: #20252c; border: 1px solid #2e333b;"
        "border-radius: 10px; padding: 18px;");
    aboutBody->setWordWrap(true);
    aboutBody->setMinimumHeight(110);
    root->addWidget(aboutBody);

    QHBoxLayout *nav = new QHBoxLayout();
    nav->setSpacing(16);
    QPushButton *menuBtn = new QPushButton("Browse the Menu");
    QPushButton *compareBtn = new QPushButton("Compare Two Items");
    menuBtn->setMinimumHeight(48);
    compareBtn->setMinimumHeight(48);
    connect(menuBtn, &QPushButton::clicked, [this]() { pages->setCurrentIndex(1); });
    connect(compareBtn, &QPushButton::clicked, [this]() { pages->setCurrentIndex(2); });
    nav->addWidget(menuBtn);
    nav->addWidget(compareBtn);
    root->addLayout(nav);

    root->addSpacing(8);
    QLabel *chartTitle = new QLabel("Highest-impact items on the menu");
    chartTitle->setStyleSheet("font-size: 18px; font-weight: bold; color: #ffffff;");
    root->addWidget(chartTitle);

    QLabel *chartNote = new QLabel("Measured in kilograms of CO\u2082 per kilogram of food");
    chartNote->setStyleSheet("font-size: 12px; color: #8a93a0;");
    root->addWidget(chartNote);

    root->addSpacing(6);

    vector<MenuItem> ranked = calc.rankByImpact(db);
    double maxCO2 = ranked.empty() ? 1.0 : ranked[0].impact.co2Kg;

    int shown = 0;
    for (size_t i = 0; i < ranked.size() && shown < 7; i++, shown++) {
        MenuItem item = ranked[i];
        QHBoxLayout *row = new QHBoxLayout();
        row->setSpacing(14);

        QLabel *name = new QLabel(QString::fromStdString(item.name));
        name->setFixedWidth(170);
        name->setStyleSheet("color: #d4d9e0; font-size: 13px;");

        QFrame *bar = new QFrame();
        int barWidth = (int)(380.0 * item.impact.co2Kg / maxCO2);
        bar->setFixedSize(barWidth + 1, 22);

        QString color;
        if (item.impact.co2Kg > 10)      color = "#C0392B";
        else if (item.impact.co2Kg >= 3) color = "#B9770E";
        else                             color = "#4a8662";
        bar->setStyleSheet("background: " + color + "; border-radius: 5px;");

        QLabel *value = new QLabel(QString::number(item.impact.co2Kg) + " kg");
        value->setStyleSheet("color: #b8c0cc; font-size: 13px; font-weight: bold;");

        row->addWidget(name);
        row->addWidget(bar);
        row->addWidget(value);
        row->addStretch();
        root->addLayout(row);
    }

    root->addStretch();
    return home;
}

// Menu page: category tabs + impact details, with a back button and impact-type toggle
QWidget* MainWindow::buildMenuPage()
{
    QWidget *page = new QWidget();
    QVBoxLayout *root = new QVBoxLayout(page);
    root->setContentsMargins(20, 20, 20, 20);

    QPushButton *back = new QPushButton("< Back to Home");
    connect(back, &QPushButton::clicked, [this]() { pages->setCurrentIndex(0); });
    root->addWidget(back);

    // impact-type toggle: switches which subclass scores the item
    QComboBox *modeBox = new QComboBox();
    modeBox->addItem("Carbon footprint");
    modeBox->addItem("Water usage");
    modeBox->addItem("Land use");
    connect(modeBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this](int index){
                impactMode = index;
                if (currentItem != nullptr)
                    onMenuItemClicked(currentItem);   // redisplay with the new mode
            });
    root->addWidget(modeBox);

    menuImpact = new QLabel("Click an item to see its impact");
    menuImpact->setWordWrap(true);

    menuMeter = new QProgressBar();
    menuMeter->setRange(0, 10);
    menuMeter->setValue(0);
    menuMeter->setTextVisible(false);

    QVBoxLayout *rightSide = new QVBoxLayout();
    rightSide->addWidget(menuImpact);
    rightSide->addWidget(menuMeter);
    rightSide->addStretch();

    QHBoxLayout *body = new QHBoxLayout();
    body->addWidget(buildCategoryTabs(&MainWindow::onMenuItemClicked));
    body->addLayout(rightSide);
    root->addLayout(body);

    return page;
}

// Compare page: category tabs; click two items to compare them
QWidget* MainWindow::buildComparePage()
{
    QWidget *page = new QWidget();
    QVBoxLayout *root = new QVBoxLayout(page);
    root->setContentsMargins(20, 20, 20, 20);

    QPushButton *back = new QPushButton("< Back to Home");
    connect(back, &QPushButton::clicked, [this]() {
        pages->setCurrentIndex(0);
        firstPick = nullptr;
    });
    root->addWidget(back);

    compareResult = new QLabel("Click one item, then another, to compare them");
    compareResult->setWordWrap(true);

    QVBoxLayout *rightSide = new QVBoxLayout();
    rightSide->addWidget(compareResult);
    rightSide->addStretch();

    QHBoxLayout *body = new QHBoxLayout();
    body->addWidget(buildCategoryTabs(&MainWindow::onCompareItemClicked));
    body->addLayout(rightSide);
    root->addLayout(body);

    return page;
}

void MainWindow::onMenuItemClicked(QListWidgetItem *clicked)
{
    QString name = clicked->text();
    currentItem = clicked;
    for (size_t i = 0; i < db.items.size(); i++) {
        if (QString::fromStdString(db.items[i].name) == name) {
            MenuItem item = db.items[i];

            // pick the right value and unit for the current mode
            QString modeName, valueText;
            if (impactMode == 1) {
                modeName  = "Water usage";
                valueText = QString::number(item.impact.waterLiters) + " liters per kg";
            } else if (impactMode == 2) {
                modeName  = "Land use";
                valueText = QString::number(item.impact.landM2) + " m2 per kg";
            } else {
                modeName  = "Carbon footprint";
                valueText = QString::number(item.impact.co2Kg) + " kg CO2";
            }

            int score = scoreFor(item);

            QString info = name + "\n\n"
                           + modeName + ": " + valueText + "\n"
                           + "Impact score: " + QString::number(score) + " / 10\n\n"
                           + "Greener pick (by carbon):\n"
                           + QString::fromStdString(calc.suggestSwap(item, db));

            menuMeter->setValue(score);

            // color the meter by the score, so it matches whichever mode is active
            QString barColor;
            if (score >= 7)      barColor = "#A32D2D";
            else if (score >= 4) barColor = "#854F0B";
            else                 barColor = "#3B6D11";
            menuMeter->setStyleSheet(
                "QProgressBar::chunk { background-color: " + barColor + "; }");

            menuImpact->setText(info);
            return;
        }
    }
}

void MainWindow::onCompareItemClicked(QListWidgetItem *clicked)
{
    QString name = clicked->text();

    MenuItem *picked = nullptr;
    for (size_t i = 0; i < db.items.size(); i++) {
        if (QString::fromStdString(db.items[i].name) == name) {
            picked = &db.items[i];
            break;
        }
    }
    if (picked == nullptr) return;

    if (firstPick == nullptr) {
        firstPick = picked;
        compareResult->setText("First pick: " + name
                               + "  (" + QString::number(picked->impact.co2Kg) + " kg CO2)"
                               + "\n\nNow click a second item to compare.");
        return;
    }

    QString a = QString::fromStdString(firstPick->name);
    QString b = name;
    double co2A = firstPick->impact.co2Kg;
    double co2B = picked->impact.co2Kg;
    double diff = calc.compareCO2(*firstPick, *picked);

    QString result =
        a + ": " + QString::number(co2A) + " kg CO2\n"
        + b + ": " + QString::number(co2B) + " kg CO2\n\n";

    if (diff > 0)
        result += a + " is worse by " + QString::number(diff) + " kg CO2";
    else if (diff < 0)
        result += b + " is worse by " + QString::number(-diff) + " kg CO2";
    else
        result += "Both have the same footprint";

    compareResult->setText(result);
    firstPick = nullptr;
}