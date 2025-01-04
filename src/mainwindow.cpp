#include "mainwindow.h"
#include "StandardPixmapList.h"

#include <QStyle>
#include <QLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QApplication>
#include <QClipboard>
#include <QStatusBar>

MainWindow::MainWindow(QWidget* parent) noexcept:
    QMainWindow{parent}
{
    auto status = new QStatusBar;
    setStatusBar(status);

    auto widget = new QWidget;
    auto layout = new QGridLayout;

    constexpr const int rowSize = 10;
    for (int i = 0; StandardPixmapList[i].value != std::numeric_limits<unsigned int>::max(); i++)
    {
        auto button = new QPushButton();
        button->setMinimumSize(48, 48);
        button->setIcon(style()->standardIcon(static_cast<QStyle::StandardPixmap>(StandardPixmapList[i].value)));
        button->setToolTip(StandardPixmapList[i].name);
        connect(button, &QPushButton::clicked, [this, i, status](){
            qApp->clipboard()->setText(StandardPixmapList[i].name);

            if (qApp->clipboard()->text() == StandardPixmapList[i].name)
            {
                status->showMessage(tr("Copied '%1'").arg(StandardPixmapList[i].name), 3000);
            }
            else
            {
                status->showMessage(tr("Copy Failed"), 3000);
            }
            
        });
        layout->addWidget(button, i / rowSize, i % rowSize);
    }

    widget->setLayout(layout); 
    setCentralWidget(widget);
}

MainWindow::~MainWindow() noexcept
{

}