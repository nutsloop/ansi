# Minimal makefile for Sphinx documentation
#

# You can set these variables from the command line, and also
# from the environment for the first two.
SPHINXOPTS    ?=
VENV          := .venv
SPHINXBUILD   := $(VENV)/bin/sphinx-build
SOURCEDIR     = source
BUILDDIR      = build

ifneq ("$(wildcard $(SPHINXBUILD))","")
else
$(error Sphinx not found in .venv. Run: python3 -m venv .venv && source .venv/bin/activate && pip install -r requirements.txt)
endif

# Put it first so that "make" without argument is like "make help".
help:
	@$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

.PHONY: help Makefile

# Catch-all target: route all unknown targets to Sphinx using the new
# "make mode" option.  $(O) is meant as a shortcut for $(SPHINXOPTS).
%: Makefile
	@$(SPHINXBUILD) -M $@ "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(O)

copy-logos:
	mkdir -p $(BUILDDIR)/_static
	cp $(SOURCEDIR)/_static/logo-light.png $(BUILDDIR)/_static/logo-light.png
	cp $(SOURCEDIR)/_static/logo-dark.png $(BUILDDIR)/_static/logo-dark.png

html: copy-logos

open:
	open $(BUILDDIR)/html/index.html