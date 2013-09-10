#ifndef QINTGUI_H
#define QINTGUI_H

#include <QMainWindow>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QGroupBox>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <intguiparams.h>
#include <qintanalysis.h>

class QIntGUI : public QMainWindow
{
    Q_OBJECT

public:
    QIntGUI(RInside &R);
    ~QIntGUI();

    void setupDisplay();

public slots:
    void configureQint();

private:
    IntGuiParams *params;           // params from GUI forms
    QIntAnalysis *qint;             // analysis object
};

#endif // QINTGUI_H
