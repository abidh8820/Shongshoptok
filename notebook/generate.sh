#!/bin/sh
python3 script.py
lualatex out.tex
lualatex out.tex
cp out.pdf team-notebook.pdf 
zathura team-notebook.pdf
