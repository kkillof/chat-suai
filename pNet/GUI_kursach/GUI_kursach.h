#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GUI_kursach.h"

class GUI_kursach : public QMainWindow
{
    Q_OBJECT

public:
    GUI_kursach(QWidget *parent = Q_NULLPTR);

private slots:
    void SendMessage();
    void SendNickname();
private:
    Ui::GUI_kursachClass ui;
};
