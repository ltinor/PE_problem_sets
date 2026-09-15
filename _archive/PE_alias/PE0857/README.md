# PE 857: Beautiful Graphs / 美丽图

## Problem
A graph on n labeled vertices where each pair has one of: red→+blue← (directed), green (undirected), or brown (undirected). Conditions: (1) Any cycle contains a red edge iff it contains a blue edge; (2) No triangle is all green or all brown. Find G(10^7) mod 10^9+7.

## Answer
**697354363**

## Solution Approach
The red digraph must be acyclic (DAG). The green and brown subgraphs must be triangle-free. Verified for n=3 (G=24), n=4 (G=186), n=5 (G=1752) by brute force.

## File Structure
```
PE0857/
├── code/
│   └── std.cpp    # C++ solution with brute-force verification
└── README.md
```
