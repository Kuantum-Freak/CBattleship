
# Copyright (c) 2017 The Gupta Empire - All Rights Reserved
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential
#
# Written by Aryan Gupta <me@theguptaempire.net>
# 
# ==============================================================================
# @author 			Aryan Gupta
# @project 			Console Battleship
# @file 			Makefile
# @date				2017-03-12 (YYYY-MM-DD)
# @version			1.0.0
# @brief 			This is the Makefile for The Battleshipe Project
# ==============================================================================
.DEFAULT_GOAL := all
# ==========================  CONST MACROS  ====================================
CC = "C:\Compiler\MinGW-w64\mingw32\bin\g++.exe"
7Z = "C:\Program Files (Portable)\7-Zip\7z.exe"
RES = "C:\Compiler\MinGW-w64\mingw32\bin\windres.exe"
OBJDIR = .\obj
BINDIR = .\bin
DATDIR = .\dat

DEBUG = -g -DDEBUG=true

# ==============================  MACROS  ======================================
CFLAGS = $(DEBUG) -Wall -std=c++17 -c
LFLAGS = $(DEBUG) -Wall
OBJ = $(OBJDIR)\main.o $(OBJDIR)\res.o $(OBJDIR)\computerAI.o $(OBJDIR)\gameFunc.o $(OBJDIR)\setUp.o $(OBJDIR)\updateBoardFunc.o $(OBJDIR)\display.o

# ============================ RECEPIES ========================================

$(OBJDIR)\main.o: .\main.cpp
	$(CC) .\$^ -o .\$@ $(CFLAGS)

$(OBJDIR)\computerAI.o: .\computerAI.cpp
	$(CC) .\$^ -o .\$@ $(CFLAGS)

$(OBJDIR)\gameFunc.o: .\gameFunc.cpp
	$(CC) .\$^ -o .\$@ $(CFLAGS)

$(OBJDIR)\setUp.o: .\setUp.cpp
	$(CC) .\$^ -o .\$@ $(CFLAGS)

$(OBJDIR)\updateBoardFunc.o: .\updateBoardFunc.cpp
	$(CC) .\$^ -o .\$@ $(CFLAGS)
	
$(OBJDIR)\display.o: .\display.cpp
	$(CC) .\$^ -o .\$@ $(CFLAGS)

$(OBJDIR)\%.o: .\%.cpp
	$(CC) .\$^ -o .\$@ $(CFLAGS) 

$(OBJDIR)\res.o: .\res.rc .\info.h
	$(RES) .\res.rc  .\$@
	
# Link	
$(BINDIR)\main.exe: $(OBJ)
	$(CC) .\$^ -o .\$@ $(LFLAGS)

# ============================= PHONY RECEPIES =================================
.PHONY: all
all: clean $(OBJ)
	$(CC) $(OBJ) $(LFLAGS) $(LSDLL) $(LSDLIL) $(LSDLTL) -o $(BINDIR)\final.exe

.PHONY: link
link:
	$(CC) .\$^ $(LFLAGS) $(LSDLL) $(LSDLIL) $(LSDLTL) -o $(BINDIR)\main.exe	
	
.PHONY: clean
clean:
	del $(OBJDIR)\*.o
	del $(BINDIR)\*.exe
	del $(DATDIR)\*.dat

.PHONY: archive
archive:
	$(7Z) a -tzip .\arc\"%DATE:~-4%%DATE:~4,2%%DATE:~7,2%".zip * -xr!obj -xr!bin -xr!arc