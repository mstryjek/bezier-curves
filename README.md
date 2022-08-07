# bezier-curves
C++ classes and functions for fitting Bezier curves of any degree to a set of points.

## TODO
- [ ] Python version
- [ ] Docstrings
- [ ] README
- [ ] Nicer drawing colors
- [ ] GIF in README (cubic + quartic curves in one GIF)
- [ ] Enable 0-dimensional Bezier curves to allow for fitting quadratic curves and calculating their curvature
- [ ] Move Cj coefficients to be precalculated in the Bezier and DerivativeBezier classes
- [X] Compilation warnings
- [X] Shorthand types for BC< T, D, D >
- [X] Different degree tests
- [X] Main tests
- [X] Fix BezierCurve::at() method
- [X] Determine factorial degree+1 at compile time