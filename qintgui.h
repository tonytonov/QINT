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
#include <QProgressBar>
#include <IntGUIParams.h>
#include <QintAnalysis.h>

class QIntGUI : public QMainWindow
{
    Q_OBJECT

public:
    QIntGUI(RInside &R);
    ~QIntGUI();

    void setupDisplay();

public slots:
    void configureQint();
    void showProgressBar();
    void hideProgressBar();
    void sValidatorAdjust(int value);

private:
    IntGuiParams *params;           // params from GUI forms
    QIntAnalysis *qint;             // analysis object

    QWidget *window;
    QComboBox *testFunctionPick;
    QIntValidator *dimValidator;
    QLineEdit *dimEdit;
    QVBoxLayout *topleft;
    QVBoxLayout *topright;
    QGroupBox *testFunctionBox;
    QComboBox *intRulePick;
    QIntValidator *lenValidator;
    QLineEdit *lenEdit;
    QIntValidator *sParamValidator;
    QLineEdit *sParamEdit;
    QPushButton *startButton;
    QPushButton *exportButton;
    QGroupBox *integrationRuleBox;
    QHBoxLayout *upperlayout;
    QVBoxLayout *lowerlayout;
    QVBoxLayout *outer;
    QHBoxLayout *skParamLayout;
    QLabel *kParamText;
    QProgressBar *analysisPB;

signals:
    void computationStarted();
    void computationFinished();
};

#endif // QINTGUI_H
