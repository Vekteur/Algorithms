#include "catch.hpp"

#include <iostream>

#include "Dynamic/Knapsack.h"
#include "Dynamic/MinimumCoins.h"
#include "Dynamic/LongestIncreasingSubsequence.h"
#include "Dynamic/LongestCommonSubsequence.h"
#include "Dynamic/EditDistance.h"

using namespace std;

TEST_CASE("Dynamic") {
	SECTION("Knapsack") {
		vector<KnapsackObject> objs{ {3, 5}, {2, 3}, {2, 3}, {1, 2} };
		REQUIRE(knapsack(objs, 5) == 8);
		REQUIRE(knapsack(objs, 6) == 10);
	}
	SECTION("Minimum coins problem") {
		REQUIRE(minimumCoins({ 1, 3, 4 }, 6) == 2);
	}
	SECTION("Longest increasing subsequence") {
		REQUIRE(longestIncreasingSubsequence({ 5, 1, 3, 8, 4, 2, 7 }) == 4);
		REQUIRE(longestIncreasingSubsequence({ 1, 2, 3, 4 }) == 4);
		REQUIRE(longestIncreasingSubsequence({ 4, 3, 2, 1 }) == 1);
	}
	SECTION("Longest common subsequence") {
		REQUIRE(longestCommonSubsequence({ 1, 2, 4, 5 }, { 2, 3, 4, 5, 6 }) == 3);
		REQUIRE(longestCommonSubsequence({ 1, 2, 3 }, { 3, 4, 5 }) == 1);
	}
	SECTION("Edit distance") {
		REQUIRE(editDistance({0, 2, 3, 5}, {1, 2, 3, 4, 5}) == 2);
	}
}