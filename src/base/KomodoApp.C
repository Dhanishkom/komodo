#include "KomodoApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

InputParameters
KomodoApp::validParams()
{
  InputParameters params = MooseApp::validParams();
  params.set<bool>("use_legacy_material_output") = false;
  params.set<bool>("use_legacy_initial_residual_evaluation_behavior") = false;
  return params;
}

KomodoApp::KomodoApp(InputParameters parameters) : MooseApp(parameters)
{
  KomodoApp::registerAll(_factory, _action_factory, _syntax);
}

KomodoApp::~KomodoApp() {}

void
KomodoApp::registerAll(Factory & f, ActionFactory & af, Syntax & syntax)
{
  ModulesApp::registerAllObjects<KomodoApp>(f, af, syntax);
  Registry::registerObjectsTo(f, {"KomodoApp"});
  Registry::registerActionsTo(af, {"KomodoApp"});

  /* register custom execute flags, action syntax, etc. here */
}

void
KomodoApp::registerApps()
{
  registerApp(KomodoApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
KomodoApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  KomodoApp::registerAll(f, af, s);
}
extern "C" void
KomodoApp__registerApps()
{
  KomodoApp::registerApps();
}
