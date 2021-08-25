FILE_LIST_PDF = \
fast-track-tutorials.pdf \
exercises.pdf  \
tutorial-1.pdf \
tutorial-2.pdf \
tutorial-3.pdf \
tutorial-4.pdf


FILE_LIST_TEX = \
exercises.tex   \
tutorial-1.tex  \
tutorial-2.tex  \
tutorial-3.tex  \
tutorial-4.tex

doc: $(FILE_LIST_PDF)

tex: $(FILE_LIST_TEX)

%.pdf : %.md
	pandoc -s -i $< -o $@

%.tex : %.md
	pandoc $<  --latex-engine=xelatex --listings -o fm-$@

clean :
	rm -rf *.tex *~

