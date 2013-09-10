#include "qintgui.h"

QIntGUI::QIntGUI(RInside &R)
{
    qint = new QIntAnalysis(R);

    params = new IntGuiParams();
    params->setFunctionIndex(0);
    params->setFunctionDim(5);
    params->setRuleIndex(0);
    params->setSeqLength(100);
    params->setsParam(1);

    setupDisplay();
}

QIntGUI::~QIntGUI()
{
    delete qint;
    delete params;
}

void QIntGUI::setupDisplay()
{
    QWidget *window = new QWidget;
    window->setWindowTitle("QINT: numerical integration with error control");

    QComboBox *testFunctionPick = new QComboBox;
    testFunctionPick->addItem("foo1");
    testFunctionPick->addItem("foo2");
    testFunctionPick->addItem("foo3");
    testFunctionPick->addItem("foo4");
    testFunctionPick->addItem("foo5");
    testFunctionPick->addItem("foo6");
    testFunctionPick->setCurrentIndex(params->getFunctionIndex());
    QObject::connect(testFunctionPick, SIGNAL(activated(int)), this->params, SLOT(setFunctionIndex(int)));

    QValidator *dimValidator = new QIntValidator(1, 100);
    QLineEdit *dimEdit = new QLineEdit;
    dimEdit->setValidator(dimValidator);
    dimEdit->setText(QString::number(params->getFunctionDim()));
    QObject::connect(dimEdit, SIGNAL(textEdited(QString)), this->params, SLOT(setFunctionDim(QString)));

    QVBoxLayout *topleft = new QVBoxLayout;
    topleft->addWidget(testFunctionPick);
    topleft->addWidget(dimEdit);
    QGroupBox *testFunctionBox = new QGroupBox("Test function");
    testFunctionBox->setMinimumSize(360,140);
    testFunctionBox->setMaximumSize(360,140);
    testFunctionBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    testFunctionBox->setLayout(topleft);

    QComboBox *intRulePick = new QComboBox;
    intRulePick->addItem("bar1");
    intRulePick->addItem("bar2");
    //intRulePick->addItem("bar3");
    intRulePick->setCurrentIndex(params->getRuleIndex());
    QObject::connect(intRulePick, SIGNAL(activated(int)), this->params, SLOT(setRuleIndex(int)));

    QValidator *lenValidator = new QIntValidator(1, 1000);
    QLineEdit *lenEdit = new QLineEdit;
    lenEdit->setValidator(lenValidator);
    lenEdit->setText(QString::number(params->getSeqLength()));
    QObject::connect(lenEdit, SIGNAL(textEdited(QString)), this->params, SLOT(setSeqLength(QString)));

    QValidator *sParamValidator = new QIntValidator(1, floor(log2(params->getSeqLength())));
    QLineEdit *sParamEdit = new QLineEdit;
    sParamEdit->setValidator(sParamValidator);
    sParamEdit->setText(QString::number(params->getsParam()));
    QObject::connect(sParamEdit, SIGNAL(textEdited(QString)), this->params, SLOT(setsParam(QString)));

    QPushButton *startButton = new QPushButton("Launch");
    QObject::connect(startButton, SIGNAL(released()), this, SLOT(configureQint()));

    QVBoxLayout *topright = new QVBoxLayout;
    topright->addWidget(intRulePick);
    topright->addWidget(lenEdit);
    topright->addWidget(sParamEdit);
    topright->addWidget(startButton);
    QGroupBox *integrationRuleBox = new QGroupBox("Integration rule and parameters");
    integrationRuleBox->setMinimumSize(360,140);
    integrationRuleBox->setMaximumSize(360,140);
    integrationRuleBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    integrationRuleBox->setLayout(topright);

    QHBoxLayout *upperlayout = new QHBoxLayout;
    upperlayout->addWidget(testFunctionBox);
    upperlayout->addWidget(integrationRuleBox);

    QHBoxLayout *lowerlayout = new QHBoxLayout;
    qint->configureSvgWidget(720, 568);
    lowerlayout->addWidget(qint->getSvgWidget());

    QVBoxLayout *outer = new QVBoxLayout;
    outer->addLayout(upperlayout);
    outer->addLayout(lowerlayout);
    window->setLayout(outer);
    window->show();
}

void QIntGUI::configureQint()
{
    qint->configure(params);
}
