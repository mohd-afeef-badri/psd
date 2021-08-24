documents: fast-track-tutorials tutorial-1 tutorial-2 tutorial-3 tutorial-4 tutorial-5 tutorial-6 tutorial-7 tutorial-8 tutorial-9 exercises

fast-track-tutorials: fast-track-tutorials.pdf

fast-track-tutorials.pdf: fast-track-tutorials.md
	pandoc -s -i fast-track-tutorials.md -o fast-track-tutorials.pdf

exercises: exercises.pdf

exercises.pdf: exercises.md
	pandoc -s -i exercises.md -o exercises.pdf

tutorial-1: tutorial-1.pdf

tutorial-1.pdf: tutorial-1.md
	pandoc -s -i tutorial-1.md -o tutorial-1.pdf

tutorial-2: tutorial-2.pdf

tutorial-2.pdf: tutorial-2.md
	pandoc -s -i tutorial-2.md -o tutorial-2.pdf

tutorial-3: tutorial-3.pdf

tutorial-3.pdf: tutorial-3.md
	pandoc -s -i tutorial-3.md -o tutorial-3.pdf

tutorial-4: tutorial-4.pdf

tutorial-4.pdf: tutorial-4.md
	pandoc -s -i tutorial-4.md -o tutorial-4.pdf

tutorial-5: tutorial-5.pdf

tutorial-5.pdf: tutorial-5.md
	pandoc -s -i tutorial-5.md -o tutorial-5.pdf

tutorial-6: tutorial-6.pdf

tutorial-6.pdf: tutorial-6.md
	pandoc -s -i tutorial-6.md -o tutorial-6.pdf

tutorial-7: tutorial-7.pdf

tutorial-7.pdf: tutorial-7.md
	pandoc -s -i tutorial-7.md -o tutorial-7.pdf

tutorial-8: tutorial-8.pdf

tutorial-8.pdf: tutorial-8.md
	pandoc -s -i tutorial-8.md -o tutorial-8.pdf

tutorial-9: tutorial-9.pdf

tutorial-9.pdf: tutorial-9.md
	pandoc -s -i tutorial-9.md -o tutorial-9.pdf

tex: le-tutorial-1.tex le-tutorial-2.tex le-tutorial-3.tex le-tutorial-4.tex  le-tutorial-5.tex le-tutorial-6.tex le-tutorial-7.tex le-tutorial-8.tex le-tutorial-9.tex le-exercises.tex

le-exercises.tex: exercises.md
	pandoc exercises.md -o le-exercises.tex --latex-engine=xelatex --listings

le-tutorial-1.tex: tutorial-1.md
	pandoc tutorial-1.md -o le-tutorial-1.tex --latex-engine=xelatex --listings

le-tutorial-2.tex: tutorial-2.md
	pandoc tutorial-2.md -o le-tutorial-2.tex --latex-engine=xelatex --listings

le-tutorial-3.tex: tutorial-3.md
	pandoc tutorial-3.md -o le-tutorial-3.tex --latex-engine=xelatex --listings

le-tutorial-4.tex: tutorial-4.md
	pandoc tutorial-4.md -o le-tutorial-4.tex --latex-engine=xelatex --listings

le-tutorial-5.tex: tutorial-5.md
	pandoc tutorial-5.md -o le-tutorial-5.tex --latex-engine=xelatex --listings

le-tutorial-6.tex: tutorial-6.md
	pandoc tutorial-6.md -o le-tutorial-6.tex --latex-engine=xelatex --listings

le-tutorial-7.tex: tutorial-7.md
	pandoc tutorial-7.md -o le-tutorial-7.tex --latex-engine=xelatex --listings

le-tutorial-8.tex: tutorial-8.md
	pandoc tutorial-8.md -o le-tutorial-8.tex --latex-engine=xelatex --listings

clean:
        rm -rf *.tex *~

le-tutorial-9.tex: tutorial-9.md
	pandoc tutorial-9.md -o le-tutorial-9.tex --latex-engine=xelatex --listings

