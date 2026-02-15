# Contributing to PSD

Firstly, thank you for considering contributing to PSD! It is people like you that make PSD a better tool for the scientific computing community and eventually help it to grow.

PSD is a Massively Parallel FEM solver for continuum dynamics. Because this is a high-performance computing (HPC) project, we maintain high standards for code efficiency, readability, and correctness.

## How Can I Contribute?

### Reporting Bugs
* Check the [Issues tab](https://github.com/mohd-afeef-badri/psd/issues) to see if the bug has already been reported.
* If not, open a new issue. Clearly describe the problem, including:
    * Your OS and compiler and dependencies version (MPI, FreeFEM, PETSc, MFront, ...)
    * The MPI implementation used (e.g., OpenMPI, MPICH).
    * Steps to reproduce the issue (and a minimal mesh/input file if possible).

### Suggesting Enhancements
* Open an [issue](https://github.com/mohd-afeef-badri/psd/issues) to discuss the proposed feature before starting work.
* Explain the physical or numerical rationale behind the enhancement.

### Pull Requests
1. **Fork the repository** and create your branch from `main`.
2. **Coding Style**: Please follow the existing style in the repository. We prefer clear variable naming and consistent indentation (matching the existing codebase).
3. **Tests**: If you add a new numerical feature or solver, include a test case or a validation example. There are three kinds of tests in PSD: unit, validation, and numerical. 
4. **Documentation**: Update the appropiate section in markdown file in `docs` or inline comments if your changes modify how the solver is used.
5. **Commit Messages**: Use descriptive commit messages (e.g., `feat: add Newmark-beta integrator` or `fix: resolve MPI deadlock in boundary exchange`).

## Getting Help
Either of the three are acceptable:
1. Via direct email: mohd-afeef.badri@cea.fr
2. GitHub [issue](https://github.com/mohd-afeef-badri/psd/issues): For bug reports and feature requests
3. Documentation: https://mohd-afeef-badri.github.io/psd/


## Recognition
Contributors are recognized in: [CONTRIBUTORS.md](https://github.com/mohd-afeef-badri/psd/blob/main/CONTRIBUTORS.md) file
GitHub's contributor list. And release notes for significant contributions

## License
By contributing to PSD, you agree that your contributions will be licensed under the Apache License 2.0.

Thank you for contributing to PSD! Your efforts help make high-performance computational mechanics accessible to researchers and engineers worldwide.
