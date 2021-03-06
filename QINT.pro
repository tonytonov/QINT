## build an app based on the one headers and two source files
TEMPLATE = 		app

SOURCES = \
  main.cpp \
    QintGUI.cpp \
    QintAnalysis.cpp \
    IntGUIParams.cpp \
    IntegrationScenario.cpp
	
HEADERS = \
    IntegrationScenario.h \
    IntGUIParams.h \
    QintAnalysis.h \
    QintGUI.h

include(NodeSequence/NodeSequence.pri)
include(TestFunction/TestFunction.pri)
include(EstimationAlgorithm/EstimationAlgorithm.pri)

## beyond the default configuration, also use SVG graphics
QT += 			svg

## comment this out if you need a different version of R, 
## and set set R_HOME accordingly as an environment variable
R_HOME = 		$$system(R RHOME)
#message("R_HOME is" $$R_HOME)

## include headers and libraries for R 
RCPPFLAGS = 		$$system($$R_HOME/bin/R CMD config --cppflags)
RLDFLAGS = 		$$system($$R_HOME/bin/R CMD config --ldflags)
RBLAS = 		$$system($$R_HOME/bin/R CMD config BLAS_LIBS)
RLAPACK = 		$$system($$R_HOME/bin/R CMD config LAPACK_LIBS)

## if you need to set an rpath to R itself, also uncomment
RRPATH =		-Wl,-rpath,$$R_HOME/lib

## include headers and libraries for Rcpp interface classes
RCPPINCL = 		$$system($$R_HOME/bin/Rscript -e \"Rcpp:::CxxFlags\(\)\")
RCPPLIBS = 		$$system($$R_HOME/bin/Rscript -e \"Rcpp:::LdFlags\(\)\")

## include headers and libraries for RInside embedding classes
RINSIDEINCL = 		$$system($$R_HOME/bin/Rscript -e \"RInside:::CxxFlags\(\)\")
RINSIDELIBS = 		$$system($$R_HOME/bin/Rscript -e \"RInside:::LdFlags\(\)\")

## compiler etc settings used in default make rules
QMAKE_CXXFLAGS +=	$$RCPPWARNING $$RCPPFLAGS $$RCPPINCL $$RINSIDEINCL
QMAKE_LIBS +=           $$RLDFLAGS $$RBLAS $$RLAPACK $$RINSIDELIBS $$RCPPLIBS

## c++0x support
QMAKE_CXXFLAGS +=       -std=c++0x

## addition clean targets
QMAKE_CLEAN +=		QintAnalysis Makefile

OTHER_FILES +=
