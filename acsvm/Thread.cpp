//-----------------------------------------------------------------------------
//
// Copyright (C) 2015 David Hill
//
// See COPYING for license information.
//
//-----------------------------------------------------------------------------
//
// Thread classes.
//
//-----------------------------------------------------------------------------

#include "Thread.hpp"

#include "Array.hpp"
#include "Module.hpp"
#include "Scope.hpp"
#include "Script.hpp"


//----------------------------------------------------------------------------|
// Extern Functions                                                           |
//

namespace ACSVM
{
   //
   // Thread constructor
   //
   Thread::Thread() :
      codePtr {nullptr},
      module  {nullptr},
      scopeGbl{nullptr},
      scopeHub{nullptr},
      scopeMap{nullptr},
      scopeMod{nullptr},
      script  {nullptr},
      delay   {0},
      result  {0}
   {
   }

   //
   // Thread destructor
   //
   Thread::~Thread()
   {
   }

   //
   // Thread::start
   //
   void Thread::start(Script *script_, MapScope *map)
   {
      script  = script_;
      module  = script->module;
      codePtr = module->codeV + script->codeIdx;

      scopeMod = map->getModuleScope(module);
      scopeMap = map;
      scopeHub = scopeMap->hub;
      scopeGbl = scopeHub->global;

      callStk.reserve(CallStkSize);
      dataStk.reserve(DataStkSize);
      localArr.alloc(script->locArrC);
      localReg.alloc(script->locRegC);

      state = ThreadState::Running;
   }

   //
   // Thread::stop
   //
   void Thread::stop()
   {
      // TODO: Resume threads waiting on this thread's completion.

      // TODO: Notify external environment of script termination.

      // Clear execution state.
      callStk.clear();
      dataStk.clear();
      localArr.clear();
      localReg.clear();
      printBuf.clear();

      codePtr = nullptr;
      delay   = 0;
      module  = nullptr;
      result  = 0;
      script  = nullptr;
      state   = ThreadState::Inactive;
   }
}

// EOF

