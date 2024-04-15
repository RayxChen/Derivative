A simple derivatives pricing engine from Joshi's book.
Add an implementation for Barrier option.

The Monte Carlo method is a versatile tool in financial derivatives pricing, well-suited for simulating the underlying asset distributions necessary for pricing complex derivatives. Its main advantage lies in its ability to manage high-dimensional problems and its amenability to parallelization, which facilitates large-scale computations.

Despite its computational intensity and slow error convergence, which requires numerous simulations to achieve accuracy, techniques like importance sampling can enhance its efficiency by reducing variance in estimations. Additionally, the quasi-Monte Carlo method offers improved performance in specific high-dimensional scenarios by employing deterministic low-discrepancy sequences.

While generally simpler than deterministic methods, Monte Carlo simulations can be complex for certain applications, such as American options pricing. However, this was largely addressed with the development of the Least Square Monte Carlo method. The method's flexibility makes it particularly valuable in portfolio pricing and risk calculations involving multiple correlated variables, such as in Value at Risk (VaR) and other risk metrics.
