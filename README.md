# Algorithms

This repository contains a collection of algorithms and data structures.
All algorithms are written in modern c++ and aim to be simple and efficient.
Several implementations have been adapted from the great resource http://e-maxx.ru/.
Tests have been written for each algorithm but they are not extensive.
The test library is [catch](https://github.com/catchorg/Catch2).

## List of implementations

* [Data structures](/Src/DataStructure)
	* [Sets](/Src/DataStructure)/Sets)
		* [Binary search tree](/Src/DataStructure)/Sets/BST.h)
		* [AVL](/Src/DataStructure)/Sets/AVL.h)
		* [BTree](/Src/DataStructure)/Sets/BTree.h)
	* [Range queries](/Src/DataStructure)/RangeQueries)
		* [Sum array](/Src/DataStructure)/RangeQueries/SumArray.h)
		* [Difference array](/Src/DataStructure)/RangeQueries/DifferenceArray.h)
		* [Square root array](/Src/DataStructure)/RangeQueries/SqrtArray.h)
		* [Sparse table](/Src/DataStructure)/RangeQueries/SparseTable.h)
		* [Fenwick tree](/Src/DataStructure)/RangeQueries/FenwickTree.h)
		* [Segment tree](/Src/DataStructure)/RangeQueries/SegmentTree.h)
		* [Lazy segment tree](/Src/DataStructure)/RangeQueries/LazySegmentTree.h)
		* [2D segment tree](/Src/DataStructure)/RangeQueries/SegmentTree2D.h)
		* [Optimal range min/max query](/Src/DataStructure)/RangeQueries/OptimalRMQ.h)
	* [Heap](/Src/DataStructure/Heap.h)
	* [Union find](/Src/DataStructure/UnionFind.h)
* [Graph](/Src/Graph)
	* [DFS, BFS](/Src/Graph/BasicGraph.h)
	* [Dijkstra](/Src/Graph/Dijkstra.h)
	* [Bellman-Ford](/Src/Graph/BellmanFord.h)
	* [SPFA](/Src/Graph/SPFA.h)
	* [Floyd-Warshall](/Src/Graph/FloydWarshall.h)
	* [Toposort](/Src/Graph/Toposort.h)
	* [Cycle detection](/Src/Graph/CycleDetection.h)
	* [Connected components](/Src/Graph/ConnectedComponents.h)
	* [Strongly connected components](/Src/Graph/SCC.h)
	* [Bridge and articulation points](/Src/Graph/BridgeAndArticulation.h)
	* [Eulerian](/Src/Graph/Eulerian.h)
	* [Spanning tree](/Src/Graph/SpanningTree)
		* [Kruskal](/Src/Graph/SpanningTree/Kruskal.h)
		* [Prim](/Src/Graph/SpanningTree/Prim.h)
	* [Flows](/Src/Graph/Flows)
		* [Edmonds-Karp](/Src/Graph/Flows/MaxFlowEdmondsKarp.h)
		* [Push relabel](/Src/Graph/Flows/MaxFlowPushRelabel.h)
		* [Min cost flow](/Src/Graph/Flows/MinCostFlow.h)
	* [Lowest common ancestor](/Src/Graph/LCA)
		* [Binary lifting](/Src/Graph/LCA/LcaBinaryLifting.h)
		* [Range query](/Src/Graph/LCA/LcaRangeQuery.h)
		* [Tarjan offline](/Src/Graph/LCA/LcaTarjan.h)
	* [2-SAT](/Src/Graph/2-SAT.h)
	* [Pr�fer code](/Src/Graph/PruferCode.h)
* [Dynamic programming](/Src/Dynamic)
	* [Count subsequences](/Src/Dynamic/CountSubsequence.h)
	* [Longest common subsequence](/Src/Dynamic/LongestCommonSubsequence.h)
	* [Longest increasing subsequence](/Src/Dynamic/LongestIncreasingSubsequence.h)
	* [Minimum coins](/Src/Dynamic/MinimumCoins.h)
	* [Subset sum](/Src/Dynamic/SubsetSum.h)
	* [Knapsack](/Src/Dynamic/Knapsack.h)
	* [Edit distance](/Src/Dynamic/EditDistance.h)
	* [Matrix chain multiplication](/Src/Dynamic/MatrixChainMultiplication.h)
	* [Word break](/Src/Dynamic/WordBreak.h)
* [Math](/Src/Math)
	* [GCD, LCM, modular power](/Src/Math/BasicMath.h)
	* [Combinatorics](/Src/Math/Combinatorics.h)
		* Multinomial coefficients
		* Catalan
		* Derangements
	* [Modular](/Src/Math/Modular.h)
		* Modular inverse
		* Chinese remainder
	* [Factorization](/Src/Math/Factorization.h)
	* [Matrix](/Src/Math/Matrix.h)
	* [Matrix power](/Src/Math/MatrixPower.h)
	* [Strassen algorithm](/Src/Math/Strassen.h)
	* [Tortoise and hare](/Src/Math/TortoiseAndHare.h)
	* [Simplex](/Src/Math/Simplex.h)
	* [Fast Fourier transform](/Src/Math/FFT.h)
	* [Gauss elimination](/Src/Math/GaussElimination.h)
* [String](/Src/String)
	* [String hashing](/Src/String/StringHashing.h)
	* [Z-algorithm](/Src/String/Z_Algorithm.h)
	* [KMP](/Src/String/KMP.h)
	* [Suffix array](/Src/String/SuffixArray.h)
	* [Suffix automaton](/Src/String/SuffixAutomaton.h)
* [Sorting](/Src/Sorting)
	* [Classical algorithms](/Src/Sorting/BasicSorting.h)
	* [Merge sort](/Src/Sorting/MergeSort.h)
	* [Quick sort](/Src/Sorting/QuickSort.h)
	* [Radix sort](/Src/Sorting/RadixSort.h)
	* [Binary search](/Src/Sorting/BinarySearch.h)
	* [Ternary search](/Src/Sorting/TernarySearch.h)
* [Geometry](/Src/Geometry)
	* [Point](/Src/Geometry/Point.h)
	* [Line](/Src/Geometry/Line.h)
	* [Segment](/Src/Geometry/Segment.h)
	* [Polygon](/Src/Geometry/Polygon.h)
	* [Closest points](/Src/Geometry/ClosestPoints.h)
* [Miscellaneous](/Src/Misc)
	* [Subsets](/Src/Misc/Subsets.h)
	* [Permutations](/Src/Misc/Permutations.h)
	* [2-Sum](/Src/Misc/TwoSum.h)
	* [Nearest smaller values](/Src/Misc/NearestSmallerValues.h)
	* [Sliding window](/Src/Misc/SlidingWindow.h)
	* [Meet in the middle knapsack](/Src/Misc/MeetInTheMiddle.h)