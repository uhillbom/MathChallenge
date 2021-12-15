CC := g++ # This is the main compiler
SRCDIR := src
PRGNAME := TovasMathChallange
OUTDIR := bin
CCFlags = -Wall
RM := rm

build:
	@echo "Starting build..."
	$(CC) $(CCFlags) $(SRCDIR)/$(PRGNAME).cpp -o $(OUTDIR)/$(PRGNAME).exe

clean:
	@echo " Cleaning...";
	@echo " $(RM) -f $(OUTDIR)/*.* "; $(RM) -f $(OUTDIR)/*.*
