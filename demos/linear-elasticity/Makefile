FILE_LIST_PDF = \
fast-track-tutorials.pdf \
exercises.pdf  \
tutorial-1.pdf \
tutorial-2.pdf \
tutorial-3.pdf \
tutorial-4.pdf \
tutorial-5.pdf \
tutorial-6.pdf \
tutorial-7.pdf \
tutorial-8.pdf \
tutorial-9.pdf


FILE_LIST_TEX = \
tutorial-1.tex  \
tutorial-2.tex  \
tutorial-3.tex  \
tutorial-4.tex  \
tutorial-5.tex  \
tutorial-6.tex  \
tutorial-7.tex  \
tutorial-8.tex  \
tutorial-9.tex

doc: $(FILE_LIST_PDF)

tex: $(FILE_LIST_TEX)

%.pdf : %.md
	pandoc -s -i $< -o $@

%.tex : %.md
	pandoc $<  --latex-engine=xelatex --listings -o le-$@

clean :
	rm -rf *.tex *~

