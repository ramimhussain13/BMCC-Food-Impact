#pragma once
#include <QWidget>

class HomeTab : public QWidget {
    Q_OBJECT
public:
    HomeTab(int itemCount, QWidget *parent = nullptr);
};