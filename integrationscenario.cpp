#include "integrationscenario.h"

IntegrationScenario::IntegrationScenario()
{
}

IntegrationScenario::IntegrationScenario(NodeSequence s, TestFunction f) : seq(s), fun(f)
{
}
