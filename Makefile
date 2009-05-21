#------------------------------------------------------------ 
# Created By harite for mingw32 on win32 and GCC on other OS
# Mailto:Harite.K@gmail.com
# For libproperties v1.0
# http://code.google.com/p/libproperties
# Date:05/10/2007
#
# When gcc's ld links the objects, it has bugs.
# This trouble me when write the Makefile! In fact, i spend lots of time to learn it.
#
# test.c
# int f(){return 3;}
# %gcc -c test.c -o test.o
# %ar cfs libtest.a test.o
# main.c
# int main(){return f();}
# %gcc -c main.c -o main.o
# Not work command
# %gcc -o main -L. -ltest main.o
# main.o: In function 'main':
# main.o(.text+0x4): undefined reference to 'f'
# collect2: ld return 1 exit status
# The error message indicates that even though libtest.a contains a definition of f,the
# linker did not find it.That’s because libtest.a was searched when it was first encoun-
# tered,and at that point the linker hadn’t seen any references to f.
# On the other hand,if we use this line,no error messages are issued:
# %gcc -o app app.o -L. –ltest
# The reason is that the reference to f in app.o causes the linker to include the test.o
# object file from the libtest.a archive.
# 
#
#------------------------------------------------------------

#------------------------------------------------------------
# Modified By harite Harite.K@gmail.com
# Date: 06/10/2007
#       1.add the "dll" target, it create dll using mingw32
#         BUT the dll can NOT be used.I don't know why.
#       2.modify the "help" target, the command "echo *" will
#         list all the files in currently directory. This is 
#         NOT what i want.
#       3.modify the "shared" target, add the LD_LIBRARY_PATH
#         to run the test program with shared lib.
#------------------------------------------------------------

#------------------------------------------------------------
# Modified By harite Harite.K@gmail.com
# Date: 07/10/2007
#       1.根据新的源码目录重新设置选项。
#          modify some settings depend on new source directory
#------------------------------------------------------------

CPP = g++
RM = rm -rf
MD = mkdir
AR = ar
RANLIB = ranlib

ARFLAGS = r

DEBUGFLAGS = -g -O2
RELEASEFLAGS = -O3 -DNDEBUG -s

MINGW32_DLLWRAP = dllwrap
MINGW32_DLLWRAP_FLAGS = --no-export-all-symbols --add-stdcall-alias --enable-auto-import
MINGW32_BUILD_DYNAMIC_FLAGS = -DLIBPROPERTIES_BUILDING_DLL

BUILD_STATIC_DIR = static_lib
BUILD_DYNAMIC_DIR = mingw32_dll
BUILD_SHARED_DIR = shared_lib
INTERFACE_INCLUDE_DIR = src/libproperties/include
TINYXML_INCLUDE_DIR = src/tinyxml/include
BUILD_LIBPROPERTIES_SRC_DIR = src/libproperties/src
BUILD_TINYXML_SRC_DIR = src/tinyxml/src
TEST_SRC_DIR = src/test
TEST_LIBPROPERTIES_SRC_FILENAME = testlibproperties.cpp
TEST_TINYXML_SRC_FILENAME = testtinyxml.cpp
TEST_LIBPROPERTIES_OBJ_FILENAME = testlibproperties.o
TEST_TINYXML_OBJ_FILENAME = testtinyxml.o
TEST_LIBPROPERTIES_FILENAME = testlibproperties
TEST_TINYXML_FILENAME = testtinyxml

LINUX_SHARED_EXPORT = export
LINUX_SHARED_EXPORT_ADD_LIBPATH = ./:$(BUILD_SHARED_DIR)

#gcc's bug
#if want to link rightly, some objects MUST at the right point of gcc's param
#have funny~
#当编译时，正确的目标构建顺序是非常重要的
#比如此处libproperties_tinyxml_ext.o要处在tinyxml后，libproperties.o在最后
#咳~GCC真是调皮阿...
LIBPROPERTIESOBJS = tinystr.o tinyxml.o tinyxmlerror.o tinyxmlparser.o \
                   libproperties.o

LIBPROPERTIESSRCCPPS = $(BUILD_TINYXML_SRC_DIR)/tinystr.cpp \
                   $(BUILD_TINYXML_SRC_DIR)/tinyxml.cpp \
                   $(BUILD_TINYXML_SRC_DIR)/tinyxmlerror.cpp \
                   $(BUILD_TINYXML_SRC_DIR)/tinyxmlparser.cpp \
                   $(BUILD_LIBPROPERTIES_SRC_DIR)/libproperties.cpp

STATIC_LIB_NAME = libproperties.a
DYNAMIC_IMPLIB_MINGW32_NAME = libproperties.a
MINGW32_DLL_DEFFILE = libproperties.def
DYNAMIC_DLL_MINGW32_NAME = libproperties.dll
DYNAMIC_DLL_GCC_NAME = libproperties.so

CPPFLAGS = -Wall -DTIXML_USE_STL $(RELEASEFLAGS) -I$(INTERFACE_INCLUDE_DIR) \
                        -I$(TINYXML_INCLUDE_DIR)

#.PHONY: all help static dll shared clean

all: help

help:
	@echo =======================================================
	@echo ===Makefile for Mingw32 on win32 and GCC on other OS===
	@echo ========libproperties Made By harite===================
	@echo ========Mailto:Harite.K@gmail.com======================
	@echo ========Project Homepage:============================== 
	@echo ===========http://code.google.com/p/libproperties======
	@echo ====Build it:==========================================
	@echo ====Show the message:==================================
	@echo ====================make [help]========================
	@echo ====Make Static lib:===================================
	@echo ====================make static========================
	@echo ====Make Shared lib in GCC:============================
	@echo ====================make shared========================
	@echo ====Make Dll with mingw32:=============================
	@echo ====================make dll===========================
	@echo ====Clean the result:==================================
	@echo ====================make clean=========================
	@echo =======================================================

static: 
	@$(RM) $(BUILD_STATIC_DIR)
	@echo [Clean workspace Done]
	@$(MD) $(BUILD_STATIC_DIR)
	@echo [Make workspace Done]
	$(CPP) $(CPPFLAGS) -c $(LIBPROPERTIESSRCCPPS)
	@echo [Make libproperties objects Done]
	$(AR) $(ARFLAGS) $(BUILD_STATIC_DIR)/$(STATIC_LIB_NAME) $(LIBPROPERTIESOBJS)
	$(RANLIB) $(BUILD_STATIC_DIR)/$(STATIC_LIB_NAME)
	@echo [Make static lib Done]
	@$(RM) $(LIBPROPERTIESOBJS)
	@echo [Clean libproperties objects Done]
	$(CPP) $(CPPFLAGS) -c $(TEST_SRC_DIR)/$(TEST_LIBPROPERTIES_SRC_FILENAME) \
                       -o $(BUILD_STATIC_DIR)/$(TEST_LIBPROPERTIES_OBJ_FILENAME)
	$(CPP) -o $(BUILD_STATIC_DIR)/$(TEST_LIBPROPERTIES_FILENAME) \
              $(BUILD_STATIC_DIR)/$(TEST_LIBPROPERTIES_OBJ_FILENAME) \
              -L./$(BUILD_STATIC_DIR) -lproperties
	$(RM) $(BUILD_STATIC_DIR)/$(TEST_LIBPROPERTIES_OBJ_FILENAME)
	@echo [Make test program using static lib Done]

# want to build dll in win32 with mingw32, but fail.
# if you do it, mail me or find us website
dll:
	@$(RM) $(BUILD_DYNAMIC_DIR)
	@echo [Clean workspace Done]
	@$(MD) $(BUILD_DYNAMIC_DIR)
	@echo [Make workspace Done]
	@$(CPP) $(CPPFLAGS) $(MINGW32_BUILD_DYNAMIC_FLAGS) -c $(LIBPROPERTIESSRCCPPS)
	@$(MINGW32_DLLWRAP) --output-def $(BUILD_DYNAMIC_DIR)/$(MINGW32_DLL_DEFFILE) --driver-name c++ --implib $(BUILD_DYNAMIC_DIR)/$(DYNAMIC_IMPLIB_MINGW32_NAME) $(LIBPROPERTIESOBJS) $(MINGW32_DLLWRAP_FLAGS) -o $(BUILD_DYNAMIC_DIR)/$(DYNAMIC_DLL_MINGW32_NAME)
	@echo [Make dll and its input lib Done]
	@$(RM) $(LIBPROPERTIESOBJS)
	@echo [Clean libproperties objects Done]
	@echo [!!Now We can NOT use the dll!!]
	@echo [And I do NOT know why]

shared:
	@$(RM) $(BUILD_SHARED_DIR)
	@echo [Clean workspace Done]
	@$(MD) $(BUILD_SHARED_DIR)
	@echo [Make workspace Done]
	@$(CPP) $(CPPFLAGS) -fPIC -c $(LIBPROPERTIESSRCCPPS)
	@$(CPP) $(CPPFLAGS) -shared -fPIC -o $(BUILD_SHARED_DIR)/$(DYNAMIC_DLL_GCC_NAME) $(LIBPROPERTIESSRCCPPS)
	@echo [Make shared lib Done]
	@$(RM) $(LIBPROPERTIESOBJS)
	@echo [Clean libproperties objects Done]
	@$(CPP) $(CPPFLAGS) -o $(BUILD_SHARED_DIR)/$(TESTOUTFILE) $(TEST_SRC_DIR)/testproperties.cpp -L./$(BUILD_SHARED_DIR) -lproperties
	@echo [Make test program using shared lib Done]
	@$(LINUX_SHARED_EXPORT) LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(LINUX_SHARED_EXPORT_ADD_LIBPATH)
	@echo [Set LD_LIBRARY_PATH Done]

clean: 
	@$(RM) $(BUILD_STATIC_DIR) $(BUILD_DYNAMIC_DIR) $(BUILD_SHARED_DIR) $(LIBPROPERTIESOBJS)
	@echo Clean Done
