FILE_LIST_PDF = \
	tutorials.pdf

doc: $(FILE_LIST_PDF)

%.pdf : %.md
	pandoc -s --pdf-engine=xelatex \
		--variable colorlinks=true \
		--variable linkcolor=blue \
		$< -o $@

clean:
	rm -rf *.tex *~ *.pdf

