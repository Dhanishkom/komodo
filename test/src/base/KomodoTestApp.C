//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "KomodoTestApp.h"
#include "KomodoApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"

InputParameters
KomodoTestApp::validParams()
{
  InputParameters params = KomodoApp::validParams();
  params.set<bool>("use_legacy_material_output") = false;
  params.set<bool>("use_legacy_initial_residual_evaluation_behavior") = false;
  return params;
}

KomodoTestApp::KomodoTestApp(InputParameters parameters) : MooseApp(parameters)
{
  KomodoTestApp::registerAll(
      _factory, _action_factory, _syntax, getParam<bool>("allow_test_objects"));
}

KomodoTestApp::~KomodoTestApp() {}

void
KomodoTestApp::registerAll(Factory & f, ActionFactory & af, Syntax & s, bool use_test_objs)
{
  KomodoApp::registerAll(f, af, s);
  if (use_test_objs)
  {
    Registry::registerObjectsTo(f, {"KomodoTestApp"});
    Registry::registerActionsTo(af, {"KomodoTestApp"});
  }
}

void
KomodoTestApp::registerApps()
{
  registerApp(KomodoApp);
  registerApp(KomodoTestApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
KomodoTestApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  KomodoTestApp::registerAll(f, af, s);
}
extern "C" void
KomodoTestApp__registerApps()
{
  KomodoTestApp::registerApps();
}
