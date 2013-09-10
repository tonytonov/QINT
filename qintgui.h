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

    QWidget *window;
    QComboBox *testFunctionPick;
    QValidator *dimValidator;
    QLineEdit *dimEdit;
    QVBoxLayout *topleft;
    QVBoxLayout *topright;
    QGroupBox *testFunctionBox;
    QComboBox *intRulePick;
    QValidator *lenValidator;
    QLineEdit *lenEdit;
    QValidator *sParamValidator;
    QLineEdit *sParamEdit;
    QPushButton *startButton;
    QGroupBox *integrationRuleBox;
    QHBoxLayout *upperlayout;
    QHBoxLayout *lowerlayout;
    QVBoxLayout *outer;
    QHBoxLayout *skParamLayout;
    QLabel *kParamText;
};

#endif // QINTGUI_H
