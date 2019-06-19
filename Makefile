CXXFLAGS=-std=c++17 -O2 -Iinc/
LINK=-lstdc++fs -Llib -lbprinter -pthread
OBJDIR=obj
INCDIR=inc
SRCDIR=src

OBJ=$(OBJDIR)/main.o \
	$(OBJDIR)/helper.o \
	$(OBJDIR)/presentation.o \
	$(OBJDIR)/configer.o \
	$(OBJDIR)/Checker.o \
	$(OBJDIR)/CompileResult.o \
	$(OBJDIR)/DiffChecker.o \
	$(OBJDIR)/JudgeResult.o \
	$(OBJDIR)/RunResult.o \
	$(OBJDIR)/Solution.o \
	$(OBJDIR)/SolutionResult.o \
	$(OBJDIR)/TestResult.o \
	$(OBJDIR)/Verdict.o \
	$(OBJDIR)/Test.o

HEADERS=$(INCDIR)/Checker.h \
		$(INCDIR)/CompileResult.h \
		$(INCDIR)/configer.h \
		$(INCDIR)/DiffChecker.h \
		$(INCDIR)/helper.h \
		$(INCDIR)/JudgeResult.h \
		$(INCDIR)/presentation.h \
		$(INCDIR)/RunResult.h \
		$(INCDIR)/Solution.h \
		$(INCDIR)/SolutionResult.h \
		$(INCDIR)/TestResult.h \
		$(INCDIR)/CompileResult.h \
		$(INCDIR)/Verdict.h \
		$(INCDIR)/definitions.h \
		$(INCDIR)/Test.h

all: judge

judge: $(OBJ)
	$(CXX) $(OBJ) -o judge $(LINK)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS)
	$(CXX) -c $(CXXFLAGS) $< -o $@

clean:
	rm $(OBJDIR)/* judge

install:
	sudo cp judge /usr/bin/
