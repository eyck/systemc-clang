//===-- src/TimeAnalysis.h - systec-clang class definition -------*- C++ -*-===//
//
//                     systemc-clang: SystemC Parser
//
// This file is distributed under the TBD
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// \brief A short example of how to use the plugin architecture.
///
//===----------------------------------------------------------------------===//
#ifndef _TIME_ANALYSIS_H_
#define _TIME_ANALYSIS_H_
#include "SystemCClang.h"

using namespace clang;
using namespace scpar;

class TimeAnalysis
: public SystemCConsumer {

public:
  TimeAnalysis( CompilerInstance& ci)
  : SystemCConsumer(ci) {
  
  }
  
  // Virtual methods.
  // void preFire();
  // void fire();
  // void postFire();
  
  bool postFire() {
    Model* model = getSystemCModel();
    
    // Just dump the model traits.
    llvm::errs() << "\n TimeAnalysis plugin is active\n";
    //model->dump(llvm::errs());

		SplitWaitBlocks splitWaitBlocks(model->getEntryFunctionContainerVector(), &_context, llvm::errs());
		
		splitWaitBlocks.init();
		splitWaitBlocks.findWaitBlocks();
    splitWaitBlocks.extractVarMap();
		splitWaitBlocks.genSauto();	
		
		FindSuspensionTime findSuspensionTime(splitWaitBlocks.returnEntryFunctionGraphMap(), llvm::errs());

		findSuspensionTime.calculateSuspensionTiming();
		findSuspensionTime.dump();
		return true;
  } 
};

#endif /* _OoO_ANALYSIS_H_ */
