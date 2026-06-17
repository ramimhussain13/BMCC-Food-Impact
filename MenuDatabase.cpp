#include "MenuDatabase.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <stdexcept>   // for std::exception
#include <iostream>    // for printing the error

void MenuDatabase::addItem(MenuItem item) {
    items.push_back(item);
}

int MenuDatabase::count() {
    return items.size();
}

bool MenuDatabase::loadFromJson(string path) {
    QFile file(QString::fromStdString(path));
    if (!file.open(QIODevice::ReadOnly))
        return false;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if (!doc.isArray())
        return false;

    // exception handling
    // catch it here so the program reports the problem instead of crashing
    try {
        for (auto value : doc.array()) {
            QJsonObject obj = value.toObject();

            // a missing or malformed "name" is treated as a fatal data error
            if (!obj.contains("name"))
                throw runtime_error("menu item is missing its name");

            string name  = obj["name"].toString().toStdString();
            double price = obj["price"].toDouble();
            int    cat   = obj["category"].toInt();
            double co2   = obj["co2_kg"].toDouble();
            double water = obj["water_liters"].toDouble();
            double land  = obj["land_m2"].toDouble();

            addItem(MenuItem(name, price, cat, EnvironmentalImpact(co2, water, land)));
        }
    }
    catch (const exception& e) {
       //report it and signal failure
        cout << "Error loading menu: " << e.what() << endl;
        return false;
    }

    return true;
}