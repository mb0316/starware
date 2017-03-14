// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME G__STARWAREDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "/Users/MoonByul/Moon_root/EURICA/BMprogram/starware/cmake/source/BMspec.h"
#include "/Users/MoonByul/Moon_root/EURICA/BMprogram/starware/cmake/source/BMgui.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static TClass *BMspec_Dictionary();
   static void BMspec_TClassManip(TClass*);
   static void *new_BMspec(void *p = 0);
   static void *newArray_BMspec(Long_t size, void *p);
   static void delete_BMspec(void *p);
   static void deleteArray_BMspec(void *p);
   static void destruct_BMspec(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::BMspec*)
   {
      ::BMspec *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::BMspec));
      static ::ROOT::TGenericClassInfo 
         instance("BMspec", "BMspec.h", 34,
                  typeid(::BMspec), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &BMspec_Dictionary, isa_proxy, 0,
                  sizeof(::BMspec) );
      instance.SetNew(&new_BMspec);
      instance.SetNewArray(&newArray_BMspec);
      instance.SetDelete(&delete_BMspec);
      instance.SetDeleteArray(&deleteArray_BMspec);
      instance.SetDestructor(&destruct_BMspec);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::BMspec*)
   {
      return GenerateInitInstanceLocal((::BMspec*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::BMspec*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *BMspec_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::BMspec*)0x0)->GetClass();
      BMspec_TClassManip(theClass);
   return theClass;
   }

   static void BMspec_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *BMgui_Dictionary();
   static void BMgui_TClassManip(TClass*);
   static void *new_BMgui(void *p = 0);
   static void *newArray_BMgui(Long_t size, void *p);
   static void delete_BMgui(void *p);
   static void deleteArray_BMgui(void *p);
   static void destruct_BMgui(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::BMgui*)
   {
      ::BMgui *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::BMgui));
      static ::ROOT::TGenericClassInfo 
         instance("BMgui", "BMgui.h", 33,
                  typeid(::BMgui), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &BMgui_Dictionary, isa_proxy, 0,
                  sizeof(::BMgui) );
      instance.SetNew(&new_BMgui);
      instance.SetNewArray(&newArray_BMgui);
      instance.SetDelete(&delete_BMgui);
      instance.SetDeleteArray(&deleteArray_BMgui);
      instance.SetDestructor(&destruct_BMgui);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::BMgui*)
   {
      return GenerateInitInstanceLocal((::BMgui*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::BMgui*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *BMgui_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::BMgui*)0x0)->GetClass();
      BMgui_TClassManip(theClass);
   return theClass;
   }

   static void BMgui_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_BMspec(void *p) {
      return  p ? new(p) ::BMspec : new ::BMspec;
   }
   static void *newArray_BMspec(Long_t nElements, void *p) {
      return p ? new(p) ::BMspec[nElements] : new ::BMspec[nElements];
   }
   // Wrapper around operator delete
   static void delete_BMspec(void *p) {
      delete ((::BMspec*)p);
   }
   static void deleteArray_BMspec(void *p) {
      delete [] ((::BMspec*)p);
   }
   static void destruct_BMspec(void *p) {
      typedef ::BMspec current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::BMspec

namespace ROOT {
   // Wrappers around operator new
   static void *new_BMgui(void *p) {
      return  p ? new(p) ::BMgui : new ::BMgui;
   }
   static void *newArray_BMgui(Long_t nElements, void *p) {
      return p ? new(p) ::BMgui[nElements] : new ::BMgui[nElements];
   }
   // Wrapper around operator delete
   static void delete_BMgui(void *p) {
      delete ((::BMgui*)p);
   }
   static void deleteArray_BMgui(void *p) {
      delete [] ((::BMgui*)p);
   }
   static void destruct_BMgui(void *p) {
      typedef ::BMgui current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::BMgui

namespace {
  void TriggerDictionaryInitialization_libSTARWAREDict_Impl() {
    static const char* headers[] = {
"source/BMspec.h",
"source/BMgui.h",
0
    };
    static const char* includePaths[] = {
"/Users/MoonByul/root/include",
"/Users/MoonByul/Moon_root/EURICA/BMprogram/starware/cmake/source",
"/Users/MoonByul/root/include",
"/Users/MoonByul/Moon_root/EURICA/BMprogram/starware/cmake/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libSTARWAREDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$source/BMspec.h")))  BMspec;
class __attribute__((annotate("$clingAutoload$source/BMgui.h")))  BMgui;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libSTARWAREDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "source/BMspec.h"
#include "source/BMgui.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"BMgui", payloadCode, "@",
"BMspec", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libSTARWAREDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libSTARWAREDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libSTARWAREDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libSTARWAREDict() {
  TriggerDictionaryInitialization_libSTARWAREDict_Impl();
}
