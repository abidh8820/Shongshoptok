python script.py
pdflatex out.tex
pdflatex out.tex
del "out.log"
del "out.aux"
del "out.out"
del "out.toc"
start "" /max "out.pdf"