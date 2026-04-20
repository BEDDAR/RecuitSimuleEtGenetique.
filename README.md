# Portfolio Optimization with Diversification
## Simulated Annealing & Genetic Algorithm

**Academic project** — Master 2 IMFL, Université Le Havre Normandie (2018)  
**Supervisor:** Mr. I. Diarrassouba

---

## Problem Description

Portfolio optimization problem with diversification constraints 
using the **Herfindahl-Hirschmann Index (H)** as the objective 
function to minimize.

Given n financial assets classified in 3 types (A, B, C), 
the goal is to find the optimal allocation W = (w1, ..., wn) 
that minimizes portfolio concentration while respecting 
risk constraints per asset class.

### Mathematical Formulation
- **Objective:** Minimize H(W) = Σ wi²
- **Constraints:** budget allocation, risk thresholds per 
asset class (Solvency constraints)

---

## Algorithms Implemented

### 1. Simulated Annealing
- Two neighborhood selection strategies
- Temperature cooling factor: μ = 0.99
- Best results with T_initial = 16

### 2. Genetic Algorithm
- Selection based on objective function probability
- Crossover by asset type permutation
- Population size k and iterations as parameters

---

## Key Results

| Assets (n1/n2/n3) | Simulated Annealing | Genetic Algorithm |
|---|---|---|
| 5/5/5 | 0.0808 | 0.0879 |
| 5/4/3 | 0.1189 | 0.1025 |
| 4/4/3 | 0.1211 | 0.2561 |
| 1/1/1 | 0.3336 | 0.6871 |

**Conclusion:** Simulated Annealing generally outperforms 
Genetic Algorithm on this problem. Both algorithms confirm 
that portfolio diversification reduces risk.

---

## Technologies
- Language: [C++]
- Domain: Financial optimization, Metaheuristics, 
Operations Research

---

## Academic Context
This project was part of the Master's program in Applied 
Mathematics and Financial Engineering, focusing on 
quantitative methods for financial risk management.
