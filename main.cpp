#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // app-wide visual theme
    app.setStyleSheet(R"(
        QMainWindow, QWidget {
            background-color: #1e2228;
            color: #e6e6e6;
            font-family: 'Segoe UI';
            font-size: 14px;
        }
        QTabWidget::pane {
            border: 1px solid #2e333b;
            border-radius: 6px;
        }
        QTabBar::tab {
            background: #2a2f37;
            color: #b8c0cc;
            padding: 8px 16px;
            border-top-left-radius: 6px;
            border-top-right-radius: 6px;
            margin-right: 2px;
        }
        QTabBar::tab:selected {
            background: #3b6d4f;
            color: white;
        }
        QListWidget {
            background: #262b32;
            border: 1px solid #2e333b;
            border-radius: 6px;
            padding: 4px;
        }
        QListWidget::item {
            padding: 8px;
            border-radius: 4px;
        }
        QListWidget::item:selected {
            background: #3b6d4f;
            color: white;
        }
        QListWidget::item:hover {
            background: #2f3640;
        }
        QPushButton {
            background: #3b6d4f;
            color: white;
            border: none;
            border-radius: 6px;
            padding: 8px 16px;
            font-weight: bold;
        }
        QPushButton:hover {
            background: #4a8662;
        }
        QComboBox {
            background: #262b32;
            border: 1px solid #2e333b;
            border-radius: 6px;
            padding: 6px;
        }
        QProgressBar {
            background: #262b32;
            border: 1px solid #2e333b;
            border-radius: 6px;
            height: 22px;
            text-align: center;
        }
        QLabel {
            color: #e6e6e6;
        }
    )");

    MainWindow w;
    w.show();
    return app.exec();
}