documents: fast-track-tutorials tutorial-1 tutorial-2 tutorial-3

fast-track-tutorials: fast-track-tutorials.pdf

fast-track-tutorials.pdf: fast-track-tutorials.md
	pandoc -s -i fast-track-tutorials.md -o fast-track-tutorials.pdf

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



tex: le-tutorial-1.tex le-tutorial-4.tex

le-tutorial-1.tex: tutorial-1.md
	pandoc tutorial-1.md -o le-tutorial-1.tex --latex-engine=xelatex --listings

le-tutorial-2.tex: tutorial-2.md
	pandoc tutorial-2.md -o le-tutorial-2.tex --latex-engine=xelatex --listings

le-tutorial-3.tex: tutorial-3.md
	pandoc tutorial-3.md -o le-tutorial-3.tex --latex-engine=xelatex --listings

le-tutorial-4.tex: tutorial-4.md
	pandoc tutorial-4.md -o le-tutorial-4.tex --latex-engine=xelatex --listings
