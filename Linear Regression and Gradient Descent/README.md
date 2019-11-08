## Introduction
A Gradient Descent Solution to Linear Regresstion in C++
## Dataset
Linear Regression uses the scaled edition of [Housing](https://www.csie.ntu.edu.tw/~cjlin/libsvmtools/datasets/regression.html#housing) in LIBSVM Data, including 506 samples and each sample has 13 features. The code is written in C++.
## Algorithms
### Gradient Descent Solution to Linear Regression
Initialization:
>**w** = **0**

Loss Function:
>**J**(**w**) = 1/n * sum(ln(1 + e<sup>-y<sub>i</sub>**w**<sup>T</sup>x<sub>i</sub></sup>)) + penalty_factor/2 * ||**w**||<sup>2</sup>

Update Parameter:
>**w** = (1 - learning_rate*penalty_factor)**w** + learning_rate/n * sum(y<sub>i</sub>**x**<sub>i</sub> / (1 + e<sup>y<sub>i</sub>**w**<sup>T</sup>x<sub>i</sub></sup>))
