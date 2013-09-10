#include "qintanalysis.h"
#include "NodeSequence/sobolsequence.h"
#include "NodeSequence/mcuniformsequence.h"
#include "TestFunction/genzfunction.h"
#include "EstimationAlgorithm/mcconfint.h"
#include "EstimationAlgorithm/qmcqconfint.h"
#include "intguiparams.h"
#include <cmath>
#include <QtGui>

QIntAnalysis::QIntAnalysis(RInside &R) : instR(R)
{
    tempfile = QString::fromStdString(Rcpp::as<std::string>(instR.parseEval("tfile <- tempfile()")));
    svgfile = QString::fromStdString(Rcpp::as<std::string>(instR.parseEval("sfile <- tempfile()")));

    params = new IntGuiParams();
    params->setFunctionIndex(0);
    params->setFunctionDim(5);
    params->setRuleIndex(0);
    params->setSeqLength(100);
    params->setsParam(1);

    setupDisplay();
}

QIntAnalysis::~QIntAnalysis()
{
    delete params;
    delete svg;
    QFile outfile(svgfile);
    outfile.remove();
}

void QIntAnalysis::setupDisplay()
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
    QObject::connect(startButton, SIGNAL(released()), this, SLOT(configure()));

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
    svg = new QSvgWidget();
    svg->setMinimumSize(720, 576);
    svg->setMaximumSize(720, 576);
    svg->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    lowerlayout->addWidget(svg);

    QVBoxLayout *outer = new QVBoxLayout;
    outer->addLayout(upperlayout);
    outer->addLayout(lowerlayout);
    window->setLayout(outer);
    window->show();
}

void QIntAnalysis::configure()
{
    NodeSequence *seq;
    EstimationAlgorithm *alg;
    switch (params->getRuleIndex())
    {
    case 0:
        seq = new SobolSequence(params->getFunctionDim(), params->getSeqLength());
        alg = new QMCQConfint(seq, params->getkParam(), params->getsParam());
        break;
    case 1:
        seq = new MCUniformSequence(params->getFunctionDim(), params->getSeqLength(), 1, instR);
        alg = new MCConfint(0.95, 1.64);
    default:
        break;
    }

    TestFunction *fun;
    fun = new GenzFunction(params->getFunctionIndex() + 1, params->getFunctionDim());

    routine.setSeq(seq);
    routine.setFun(fun);
    routine.setAlg(alg);
    routine.RunAnalysis();
    plot();
}

void QIntAnalysis::plot()
{
    std::vector<double> estimate = routine.getAlg()->getEstimate().toStdVector();
    std::vector<int> borderIndices = routine.getAlg()->getBorder()[0].keys().toVector().toStdVector();
    std::vector<double> borderValues = routine.getAlg()->getBorder()[0].values().toVector().toStdVector();
    instR["estimate"] = estimate;
    instR["exact"] = routine.getExact();
    instR["borderIndices"] = borderIndices;
    instR["borderValues"] = borderValues;
    std::string cmd0 = "require(ggplot2);require(reshape2);"
    "image.df <- data.frame(error = abs(estimate - exact), border = NA);"
    "image.df$border[borderIndices] <- borderValues;"
    "image.df$number <- as.numeric(rownames(image.df));"
    "image.melt.df <- melt(image.df, id.vars='number');"
    "image <- ggplot(image.melt.df, aes(x=number, y=value, colour=variable, group=variable)) + "
    "geom_path(size=1.2) + "
    "labs(title=paste('QINT ', sep=''),"
    "    y='', x='', colour='', size='') + "
    "scale_colour_brewer(palette='Set1') + "
    "theme("
    "   legend.text = element_text(size = 16, face = 'bold'),"
    "   legend.title = element_text(size = 16, face = 'bold'),"
    "   plot.title = element_text(size = 16, face = 'bold', vjust = 1.2),"
    "   axis.title.x = element_text(size = 16, face = 'bold', vjust = -0.2),"
    "   axis.title.y = element_text(size = 16, face = 'bold', vjust = 0.2),"
    "   axis.text.x = element_text(size = 14, colour = 'black'),"
    "   axis.text.y = element_text(size = 14, colour = 'black')"
    "   ) + "
    "expand_limits(y=0);";
    std::string cmd1 = "ggsave(file=tfile, plot=image, device=svg, width=10, height=8);";
    std::string cmd = cmd0 + cmd1;
    instR.parseEvalQ(cmd);
    filterFile();
    svg->load(svgfile);
}

void QIntAnalysis::filterFile()
{
    // cairoDevice creates richer SVG than Qt can display
    QFile infile(tempfile);
    infile.open(QFile::ReadOnly);
    QFile outfile(svgfile);
    outfile.open(QFile::WriteOnly | QFile::Truncate);

    QTextStream in(&infile);
    QTextStream out(&outfile);
    QRegExp rx1("<symbol");
    QRegExp rx2("</symbol");
    while (!in.atEnd()) {
        QString line = in.readLine();
        line.replace(rx1, "<g"); // so '<symbol' becomes '<g ...'
        line.replace(rx2, "</g");// and '</symbol becomes '</g'
        out << line << "\n";
    }
    infile.close();
    infile.remove();
    outfile.close();
}
