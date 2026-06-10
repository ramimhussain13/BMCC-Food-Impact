#include "hometab.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFrame>

// builds a small stat card: a big number above a caption
static QFrame* makeStatCard(QString number, QString caption) {
    QFrame *card = new QFrame();
    card->setStyleSheet(
        "QFrame { background: #262b32; border: 1px solid #2e333b;"
        "border-radius: 10px; }");

    QVBoxLayout *cardLayout = new QVBoxLayout(card);

    QLabel *num = new QLabel(number);
    num->setStyleSheet("font-size: 28px; font-weight: bold; color: #4a8662; border: none;");
    num->setAlignment(Qt::AlignCenter);

    QLabel *cap = new QLabel(caption);
    cap->setStyleSheet("font-size: 12px; color: #b8c0cc; border: none;");
    cap->setAlignment(Qt::AlignCenter);
    cap->setWordWrap(true);

    cardLayout->addWidget(num);
    cardLayout->addWidget(cap);
    return card;
}

HomeTab::HomeTab(int itemCount, QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *root = new QVBoxLayout(this);
    root->setContentsMargins(40, 40, 40, 40);
    root->setSpacing(20);

    // welcome banner
    QLabel *title = new QLabel("BMCC Food Impact");
    title->setStyleSheet("font-size: 34px; font-weight: bold; color: #ffffff;");

    QLabel *tagline = new QLabel(
        "See the environmental footprint of cafeteria food — and find greener choices.");
    tagline->setStyleSheet("font-size: 15px; color: #b8c0cc;");
    tagline->setWordWrap(true);

    root->addWidget(title);
    root->addWidget(tagline);

    // quick stats row
    QHBoxLayout *stats = new QHBoxLayout();
    stats->setSpacing(16);
    stats->addWidget(makeStatCard(QString::number(itemCount), "menu items tracked"));
    stats->addWidget(makeStatCard("8", "food categories"));
    stats->addWidget(makeStatCard("99x", "more CO2 in beef vs. veggie"));
    root->addLayout(stats);

    // about section
    QLabel *aboutTitle = new QLabel("About");
    aboutTitle->setStyleSheet("font-size: 20px; font-weight: bold; color: #ffffff;");

    QLabel *aboutBody = new QLabel(
        "This app helps BMCC students understand how their food choices affect "
        "the environment. Each cafeteria item is rated by its carbon footprint "
        "using real data from Poore & Nemecek (2018). When an item has a high "
        "impact, the app suggests a lower-impact alternative that's still on the "
        "menu — so eating greener is easy, informed, and doesn't mean giving up a "
        "full meal. Small daily swaps, multiplied across thousands of students, "
        "add up to a real reduction in emissions.");
    aboutBody->setStyleSheet("font-size: 14px; color: #d4d9e0; line-height: 150%;");
    aboutBody->setWordWrap(true);

    root->addWidget(aboutTitle);
    root->addWidget(aboutBody);
    root->addStretch();
}