<!-- omit in toc -->
# C++ Bezier Curves

<p align="center">
	<img src="resources/curves.gif"/>
</p>

<p align="center">
	<b>Bezier curves fitted to sample points</b>
</p>

<div align="center">

![](https://img.shields.io/badge/opencv-4.x-yellow?style=for-the-badge&logo=opencv&logoColor=yellow)
![](https://img.shields.io/badge/c++-11\/14\/17\/20-blue?style=for-the-badge&logo=c%2B%2B&logoColor=blue)
![](https://img.shields.io/badge/Eigen-3.3-red?style=for-the-badge)
![](https://img.shields.io/badge/License-MIT-brightgreen?style=for-the-badge)

</div>

<details>
<summary>Table of Contents</summary>

- [About](#about)
- [Getting started](#getting-started)
	- [Setup](#setup)
	- [Demo](#demo)
	- [Usage](#usage)
- [A note about file extensions](#a-note-about-file-extensions)
- [Limitations](#limitations)
- [License](#license)
- [Bugs and contributing](#bugs-and-contributing)

</details>

## About
This is a set of C++ tools meant to provide an easy means of working with [Bezier curves](https://en.wikipedia.org/wiki/B%C3%A9zier_curve), including a non-heuristic method to automatically fit a Bezier curve to a set of points. Curves of any degree and in any number of dimensions are supported. There are also utilit functions providing an easy means of visualizing two-dimensional curves on images, based on OpenCV.

**The algorithm for fitting Bezier curves to points is an implementation of [Jim Herold's algorithm](https://www.jimherold.com/computer-science/best-fit-bezier-curve). All credit goes to him.**

If you're not familiar with Bezier curves work, you can play around with them [here](https://cubic-bezier.com).


## Getting started
### Setup
To build [the demo file](src/main.cpp), you'll need to use [CMake](https://cmake.org/):
```bash
mkdir build
cd build
cmake ..
make
```
### Demo
After you've built the demo, simply run it with
```bash
./main
```
### Usage
Declaring curve variables:
```c++
#include "bezier_curves/bezier_curve.hpp"

...

Bezier::BezierCurve<TYPENAME, DEGREE, DIMENSIONS> curve;
```
Replace `TYPENAME` with an arithmetic typename (`double` allows for best precision), `DEGREE` should be the degree of the curve (a curve of degree `N` has `N+1` control points) and `DIMENSIONS` should be the dimensionality of the curve.


## A note about file extensions
You may notice that most source code files have the `.tpp` extension. This is meant to mark template implementation source code, but the files are already included in the header files.

Some text editors may not be able to associate these files with C++ at first. In Visual Studio Code, add:
```json
"files.associtations": {
	...,
	"*.tpp": "cpp"
}

```
to `.vscode/settings.json`.


## Limitations
- Fitting curves to points only works well if the points you pass to the curves are in the correct order. If they passed out of order to the fitting method, you will get undesired effects
- There are known numeric stability issues for points with large coordinate values
- Drawing is limited to 2D curves (since images are two-dimensional objects)
- There is currently no way to fit degree-1 curves (a.k.a. line segments) to points. Instead, consider [simple linear regression](https://en.wikipedia.org/wiki/Simple_linear_regression)


## License
Distributed under the MIT License. See [`LICENSE`](LICENSE) for more information. If you end up using this repo in a public project, I'd appreciated if you left a link to this repo in your code or in your README.md.


## Bugs and contributing
If you find any bugs, or implement your own features that you'd like merged in the repo, make sure to
submit a PR!
