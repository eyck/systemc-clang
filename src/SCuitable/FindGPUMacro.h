#ifndef __FIND_GPU_MACRO_H
#define __FIND_GPU_MACRO_H

#include "clang/AST/DeclCXX.h"
#include "llvm/Support/raw_ostream.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include <map>

namespace scpar {
 
  using namespace std;
  using namespace clang;

  class GPUMacro {
   
    public:
      GPUMacro(int, int, int, int, int, int, int, int);
      GPUMacro();
      ~GPUMacro();
			
			void addGPUFit();
			void denyGPUFit();
      int getBlockIdx();
      int getBlockIdy();
      int getBlockIdz();
      int getThreadIdx();
      int getThreadIdy();
      int getThreadIdz();
      int getGPUTime();
      int getCPUTime(); 
      bool isGPUFit();
			void dump(raw_ostream&);      

    private:
			
      int _blockIdx;
      int _blockIdy;
      int _blockIdz;
      int _threadIdx;
      int _threadIdy;
      int _threadIdz;
      int _gpuTime;
      int _cpuTime; 
			bool _gpuFit;
  };
  

  class FindGPUMacro:public RecursiveASTVisitor <FindGPUMacro> {
    public:
			
			typedef pair<int, ForStmt*> forStmtInstanceIdPairType;
			typedef map<int, ForStmt*> forStmtInstanceIdMapType;

			typedef pair <forStmtInstanceIdPairType, GPUMacro* > forStmtGPUMacroPairType;
      typedef map	 <forStmtInstanceIdPairType, GPUMacro* > forStmtGPUMacroMapType; 
      
      FindGPUMacro(CXXMethodDecl*, int, raw_ostream&);
      ~FindGPUMacro();
      // ANI : Need to add other loops as well.....       
      virtual bool VisitForStmt(ForStmt *);

      forStmtGPUMacroMapType getForStmtGPUMacroMap();

      void dump();


    private:
     map<string, int> fetchStmtInitDecl(Stmt* stmt);
     int fetchExprInc(Expr* expr);
     int processCondExpr(Expr* expr);
     void printLoopBounds(ForStmt* forStmt);

     forStmtGPUMacroMapType _forStmtGPUMacroMap; 
     CXXMethodDecl* _entryFunction;		 
		 int _instanceNum;
		 raw_ostream& _os;

  };
}
#endif
