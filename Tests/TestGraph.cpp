#include "catch.hpp"

#include <algorithm>
#include <functional>

#include "TestUtil.h"

#include "Graph/Graph.h"
#include "Graph/BasicGraph.h"
#include "Graph/Dijkstra.h"
#include "Graph/BellmanFord.h"
#include "Graph/SPFA.h"
#include "Graph/FloydWarshall.h"
#include "Graph/BridgeAndArticulation.h"
#include "Graph/ConnectedComponents.h"
#include "Graph/SCC.h"
#include "Graph/CycleDetection.h"
#include "Graph/Eulerian.h"
#include "Graph/SpanningTree/Kruskal.h"
#include "Graph/SpanningTree/Prim.h"
#include "Graph/Flows/MaxFlowEdmondsKarp.h"
#include "Graph/Flows/MaxFlowPushRelabel.h"
#include "Graph/Flows/MinCostFlow.h"
#include "Graph/Flows/CompatibleFlow.h"
#include "Graph/DirectedMST.h"
#include "Graph/Toposort.h"
#include "Graph/PruferCode.h"
#include "Graph/2-SAT.h"
#include "Graph/LCA/LCATarjan.h"
#include "Graph/LCA/LCABinaryLifting.h"
#include "Graph/LCA/LCARangeQuery.h"

using namespace std;

TEST_CASE("Graph") {
	AdjList<WeightLabel> g(4);
	vector<BiEdge<WeightLabel>> edges{ {0, 1, {1}}, {0, 2, {3}}, {1, 2, {1}}, {2, 3, {2}}, {3, 1, {1}} };
	SECTION("Directed") {
		for (auto edge : edges) {
			g.addEdge(edge.from, edge.to, { edge.w });
		}
		SECTION("Basic") {
			REQUIRE(dfsStack(g, 0).size() == 4);
			REQUIRE(bfs(g, 0).size() == 4);
		}
		SECTION("Cycle detection") {
			REQUIRE(hasCycle(g));
			g.removeEdge(1, 2);
			REQUIRE(!hasCycle(g));
		}
		SECTION("Dijkstra") {
			vector<int> minDist, pred;
			tie(minDist, pred) = dijkstra(g, 0);
			REQUIRE(minDist[3] == 4);
			REQUIRE(pred[3] == 2);
			REQUIRE(dijkstraBacktrack(pred, 0, 3).size() == 3);
		}
		SECTION("Bellman-Ford") {
			vector<int> minDist, pred;
			tie(minDist, pred) = bellmanFordDistances(g, 0);
			REQUIRE(minDist[3] == 4);
			REQUIRE(pred[3] == 2);
			REQUIRE(bellmanFordBacktrack(pred, 0, 3).size() == 3);
			REQUIRE(bellmanFordCheckCycle(g, minDist) == -1);
			g.removeEdge(1, 2);
			g.addEdge(1, 2, { -4 });
			tie(minDist, pred) = bellmanFordDistances(g, 0);
			REQUIRE(bellmanFordCheckCycle(g, minDist) != -1);
		}
		SECTION("Shortest path faster algorithm") {
			vector<int> minDist, pred;
			tie(minDist, pred) = spfaDistances(g, 0);
			REQUIRE(minDist[3] == 4);
			REQUIRE(pred[3] == 2);
		}
		SECTION("Floyd-Warshall") {
			AdjMat<WeightLabel> mat(4, { INF });
			for (auto edge : edges)
				mat.setEdge(edge.from, edge.to, { edge.w });

			AdjMat<WeightLabel> minDist;
			AdjMat<Edge<>> next;
			tie(minDist, next) = floydWarshall(mat);
			REQUIRE(minDist(0, 3).w == 4);
			REQUIRE(floydWarshallPath(next, 0, 3).size() == 3);
			mat.setEdge(1, 2, { -4 });
			tie(minDist, next) = floydWarshall(mat);
			floydWarshallInfiniteShortestPaths(minDist);
			REQUIRE(minDist(0, 3).w == -INF);
		}
		SECTION("Eulerian") {
			REQUIRE(!containsEulerianPath(g));
			g.removeEdge(0, 2);
			g.addEdge(2, 0);
			REQUIRE(containsEulerianPath(g));
			REQUIRE(!containsEulerianCycle(g));
			struct VisLabel {
				bool vis = false;
			};
			AdjList<VisLabel> gVis(g.size());
			for (int u = 0; u < g.size(); ++u)
				for (auto v : g.adj[u])
					gVis.addEdge(u, v.to, { false });
			REQUIRE(findEulerianPath(gVis, 2).size() == 6);
		}
		SECTION("Toposort") {
			g.removeEdge(1, 2);
			g.addEdge(2, 1, { 0 }); // Make acyclic graph
			REQUIRE(toposortInDegree(g).size() == 4);
			REQUIRE(toposortDfs(g).size() == 4);
		}
		SECTION("Strongly connected components") {
			REQUIRE(stronglyConnectedComponents(g).size() == 2);
		}
		SECTION("Max flow") {
			AdjMat<WeightLabel> mat(4, { 0 });
			for (auto edge : edges)
				mat.setEdge(edge.from, edge.to, { edge.w });
			SECTION("Edmond-Karp") {
				REQUIRE(maxflowEdmondsKarp(mat, 0, 3) == 2);
				mat.setEdge(2, 3, { 5 });
				REQUIRE(maxflowEdmondsKarp(mat, 0, 3) == 4);
			}
			SECTION("Push-Relabel") {
				REQUIRE(maxFlowPushRelabel(mat, 0, 3) == 2);
				mat.setEdge(2, 3, { 5 });
				REQUIRE(maxFlowPushRelabel(mat, 0, 3) == 4);
			}
			SECTION("Min cost flow") {
				AdjMat<std::vector<WeightCostLabel>> mat(4, {});
				for (auto edge : edges)
					mat.setEdge(edge.from, edge.to, { { edge.w, edge.w } });
				mat.setEdge(2, 3, { { 5, 2 } });
				mat(2, 1).push_back({ 1, 1 });
				mat(1, 3).push_back({ 1, 1 });
				mat(1, 2).push_back({ 1, 10 });
				int flow, minCost;
				tie(flow, minCost) = minCostFlow(mat, 0, 3, 2);
				REQUIRE(flow == 2);
				REQUIRE(minCost == 7);
				tie(flow, minCost) = minCostFlow(mat, 0, 3);
				REQUIRE(flow == 4);
				REQUIRE(minCost == 17);
			}
			SECTION("Compatible flow") {
				/*AdjMat<WeightDemandLabel> mat(4, { 0, 0 });
				for (auto edge : edges)
					mat.setEdge(edge.from, edge.to, { edge.w, edge.w });
				REQUIRE(maxCompatibleFlow(mat, 0, 3) == 2);*/
			}
		}
		SECTION("Directed MST") {
			EdgeList<WeightLabel> list(3);
			list.addEdge(0, 1, { 4 });
			list.addEdge(0, 2, { 6 });
			list.addEdge(1, 2, { 2 });
			list.addEdge(2, 1, { 1 });
			int sum = directedMstEdmond(list, 0);
			REQUIRE(sum == 6);
		}
		SECTION("2-SAT") {
			TwoSAT twoSAT;
			twoSAT.addDisjunction({ { 0, true }, { 1, false } });
			twoSAT.addDisjunction({ { 0, false }, { 1, true } });
			twoSAT.addDisjunction({ { 0, false }, { 1, false } });
			twoSAT.addDisjunction({ { 0, true }, { 2, false } });
			vector<bool> expected{ false, false, false };
			REQUIRE(twoSAT.findAssigment() == expected);
		}
	}

	SECTION("Undirected") {
		for (auto edge : edges) {
			g.addEdge(edge.from, edge.to, { edge.w });
			g.addEdge(edge.to, edge.from, { edge.w });
		}
		SECTION("Prim") {
			vector<int> pred = prim(g, 0);
			vector<int> weights;
			for (int u = 0; u < (int) pred.size(); ++u)
				if (pred[u] != -1)
					weights.push_back(g(pred[u], u).w);
			REQUIRE(*max_element(weights.begin(), weights.end()) == 1);
		}
		SECTION("Kruskal") {
			EdgeList<WeightLabel> list(g.size());
			for (auto edge : edges) {
				list.addEdge(edge.from, edge.to, { edge.w });
			}
			EdgeList<> mst = kruskal(list);
			REQUIRE(mst.list.size() == 3);
		}
		SECTION("Connected components") {
			REQUIRE(isConnected(g));
			g.removeEdge(0, 1);
			g.removeEdge(1, 0);
			g.removeEdge(0, 2);
			g.removeEdge(2, 0); // Isolate 0
			REQUIRE(!isConnected(g));
			REQUIRE(connectedComponents(g).size() == 2);
		}
		SECTION("Bridges and articulations") {
			g.removeEdge(0, 1);
			g.removeEdge(1, 0);
			std::vector<int> articulationPoints;
			std::vector<BiEdge<>> bridges;
			tie(articulationPoints, bridges) = bridgesAndArticulationPoints(g);
			REQUIRE(articulationPoints.size() == 1);
			REQUIRE(articulationPoints[0] == 2);
			REQUIRE(bridges.size() == 1);
			REQUIRE(bridges[0].from == 0);
			REQUIRE(bridges[0].to == 2);
		}
	}
}

TEST_CASE("Tree") {
	vector<int> preds{ -1, 3, 3, 0, 1, 1, 1, 4, 4 };
	AdjList<> tree(preds.size());
	for (int i = 0; i < int(preds.size()); ++i) {
		if (preds[i] != -1)
			tree.addEdge(preds[i], i);
	}
	SECTION("Directed") {
		SECTION("LCA") {
			SECTION("Binary lifting") {
				LcaBinaryLifting lca(tree, 0);
				REQUIRE(lca.query(2, 4) == 3);
				REQUIRE(lca.query(1, 0) == 0);
			}
			SECTION("Tarjan's offline algorithm") {
				std::vector<int> lcas = lcaTarjanOffline(tree, 0, { { 2, 4 }, { 1, 0 } });
				REQUIRE(lcas[0] == 3);
				REQUIRE(lcas[1] == 0);
			}
			SECTION("Range query") {
				LcaRangeQuery lca(tree, 0);
				REQUIRE(lca.query(2, 4) == 3);
				REQUIRE(lca.query(1, 0) == 0);
			}
			SECTION("Range query optimized") {
				LcaRangeQueryOptimized lca(tree, 0);
				REQUIRE(lca.query(2, 4) == 3);
				REQUIRE(lca.query(0, 1) == 0);
			}
		}
	}
	SECTION("Undirected") {
		for (int i = 0; i < int(preds.size()); ++i) {
			if (preds[i] != -1)
				tree.addEdge(i, preds[i]);
		}
		SECTION("Prufer code") {
			vector<int> code{ 3, 3, 1, 1, 1, 4, 4 };
			REQUIRE(pruferCode(tree) == code);
			REQUIRE(pruferCode(pruferTree(code)) == code);
		}
	}
}