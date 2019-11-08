## Introduction
This is my first experiment of the currently ongoing machine learning course at SCUT. In this experiment, there are a closed-form solution and a stochastic solution to linear regression.
## Dataset
Linear Regression uses the scaled edition of [Housing](https://www.csie.ntu.edu.tw/~cjlin/libsvmtools/datasets/regression.html#housing) in LIBSVM Data, including 506 samples and each sample has 13 features. The code is written in python on jupyter.
## Algorithms
### Closed-Form Solution to Linear Regression
Closed-Form Equation:
>**w*** = (**X**<sup>T</sup>**X**)<sup>-1</sup>**X**<sup>T</sup>**y**
### Stochastic Gradient Descent Solution to Linear Regression
Initialization:
>**w** = **0**

Loss Function:
>**L**(**w**) = 1/(2n) * (**y** - **Xw**)<sup>T</sup>(**y** - **Xw**) + 1/(2n) * lambda * **w**<sup>T</sup>**w**

Gradient:
>**G** = (**X<sub>i</sub>**<sup>T</sup>(**X<sub>i</sub>w** - y<sub>i</sub>) + lambda * **w**)/n

Update Parameter:
>**w** = **w** - learning_rate * **G**
