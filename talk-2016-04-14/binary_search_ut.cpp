#include "gtest/gtest.h"
#include "binary_search.h"
using lb = bool (*)(const vector<int>& lists, const int& v, int i, int& result);

bool RunTest(lb f, const vector<int>& vec, int val, int start,
         int check1, bool check2)
{
  int result = 0;
  int ret = f(vec, val, start, result);
  return ret == check2 && result == check1;
}

TEST(BinarySearch, BinarySearch)
{
  vector<int> v1 = {1, 3, 5, 7, 9, 9, 11};
  EXPECT_TRUE(RunTest(LowerBound1<int>, v1, -1, -1, 0, false));
  EXPECT_TRUE(RunTest(LowerBound1<int>, v1, 0, -1, 0 , false));
  EXPECT_TRUE(RunTest(LowerBound1<int>, v1, 1, -1, 0, true));
  EXPECT_TRUE(RunTest(LowerBound1<int>, v1, 2, 0, 1, false));
  EXPECT_TRUE(RunTest(LowerBound1<int>, v1, 3, 1, 2, false));
  EXPECT_TRUE(RunTest(LowerBound1<int>, v1, 3, 0, 1, true));
  EXPECT_TRUE(RunTest(LowerBound1<int>, v1, 0, 0, 1, false));
  EXPECT_TRUE(RunTest(LowerBound1<int>, v1, 0, 0, 1, false));
  EXPECT_TRUE(RunTest(LowerBound1<int>, v1, 4, 0, 2, false));
  EXPECT_TRUE(RunTest(LowerBound1<int>, v1, 5, 0, 2, true));
  EXPECT_TRUE(RunTest(LowerBound1<int>, v1, 9, 0, 4, true));
  EXPECT_TRUE(RunTest(LowerBound1<int>, v1, 9, 0, 4, true));
  EXPECT_TRUE(RunTest(LowerBound1<int>, v1, 11, 0, 6, true));
  EXPECT_TRUE(RunTest(LowerBound1<int>, v1, 12, 0, 7, false));

  EXPECT_TRUE(RunTest(LowerBound<int>, v1, -1, 0, 0, false));
  EXPECT_TRUE(RunTest(LowerBound<int>, v1, 0, 0, 0 , false));
  EXPECT_TRUE(RunTest(LowerBound<int>, v1, 1, 0, 0, true));
  EXPECT_TRUE(RunTest(LowerBound<int>, v1, 2, 0, 1, false));
  EXPECT_TRUE(RunTest(LowerBound<int>, v1, 3, 1, 1, true));
  EXPECT_TRUE(RunTest(LowerBound<int>, v1, 3, 0, 1, true));
  EXPECT_TRUE(RunTest(LowerBound<int>, v1, 0, 0, 0, false));
  EXPECT_TRUE(RunTest(LowerBound<int>, v1, 0, 0, 0, false));
  EXPECT_TRUE(RunTest(LowerBound<int>, v1, 4, 0, 2, false));
  EXPECT_TRUE(RunTest(LowerBound<int>, v1, 5, 0, 2, true));
  EXPECT_TRUE(RunTest(LowerBound<int>, v1, 9, 0, 4, true));
  EXPECT_TRUE(RunTest(LowerBound<int>, v1, 9, 0, 4, true));
  EXPECT_TRUE(RunTest(LowerBound<int>, v1, 11, 0, 6, true));
  EXPECT_TRUE(RunTest(LowerBound<int>, v1, 12, 0, 7, false));

  vector<int> v2 = {};
  EXPECT_TRUE(RunTest(LowerBound1<int>, v2, 12, -1, 0, false));
  EXPECT_TRUE(RunTest(LowerBound<int>, v2, 12, 0, 0, false));
  EXPECT_TRUE(RunTest(LowerBound1<int>, v2, 0, -1, 0, false));
  EXPECT_TRUE(RunTest(LowerBound<int>, v2, 0, 0, 0, false));

  vector<int> v3 = {0};
  EXPECT_TRUE(RunTest(LowerBound1<int>, v3, 12, -1, 1, false));
  EXPECT_TRUE(RunTest(LowerBound<int>, v3, 12, 0, 1, false));
  EXPECT_TRUE(RunTest(LowerBound1<int>, v3, 0, -1, 0, true));
  EXPECT_TRUE(RunTest(LowerBound<int>, v3, 0, 0, 0, true));
  EXPECT_TRUE(RunTest(LowerBound1<int>, v3, -1, -1, 0, false));
  EXPECT_TRUE(RunTest(LowerBound<int>, v3, -1, 0, 0, false));


  vector<int> v4 = {0, 5, 5};
  EXPECT_TRUE(RunTest(LowerBound1<int>, v4, 12, -1, 3, false));
  EXPECT_TRUE(RunTest(LowerBound<int>, v4, 12, 0, 3, false));
  EXPECT_TRUE(RunTest(LowerBound1<int>, v4, 0, -1, 0, true));
  EXPECT_TRUE(RunTest(LowerBound<int>, v4, 0, 0, 0, true));
  EXPECT_TRUE(RunTest(LowerBound1<int>, v4, -1, -1, 0, false));
  EXPECT_TRUE(RunTest(LowerBound<int>, v4, -1, 0, 0, false));

  EXPECT_TRUE(RunTest(LowerBound1<int>, v4, 5, -1, 1, true));
  EXPECT_TRUE(RunTest(LowerBound<int>, v4, 5, 0, 1, true));
}


using UB = void (*)(const vector<int>& lists, const int& v, int i, int& result);
bool RunTest(UB f, const vector<int>& vec, int val, int start,
         int check1)
{
  int result;
  f(vec, val, start, result);
  return result == check1;
}

TEST(BinarySearch, upperbound)
{
  vector<int> v1 = {1, 3, 5, 7, 9, 9, 11};
  EXPECT_TRUE(RunTest(UpperBound1<int>, v1, -1, -1, 0));
  EXPECT_TRUE(RunTest(UpperBound1<int>, v1, 0, -1, 0 ));
  EXPECT_TRUE(RunTest(UpperBound1<int>, v1, 1, -1, 1));
  EXPECT_TRUE(RunTest(UpperBound1<int>, v1, 2, 0, 1));
  EXPECT_TRUE(RunTest(UpperBound1<int>, v1, 3, 1, 2));
  EXPECT_TRUE(RunTest(UpperBound1<int>, v1, 3, 0, 2));
  EXPECT_TRUE(RunTest(UpperBound1<int>, v1, 0, 0, 1));
  EXPECT_TRUE(RunTest(UpperBound1<int>, v1, 4, 0, 2));
  EXPECT_TRUE(RunTest(UpperBound1<int>, v1, 5, 0, 3));
  EXPECT_TRUE(RunTest(UpperBound1<int>, v1, 9, 0, 6));
  EXPECT_TRUE(RunTest(UpperBound1<int>, v1, 11, 0, 7));
  EXPECT_TRUE(RunTest(UpperBound1<int>, v1, 12, 0, 7));

  EXPECT_TRUE(RunTest(UpperBound<int>, v1, -1, 0, 0));
  EXPECT_TRUE(RunTest(UpperBound<int>, v1, 0, 0, 0 ));
  EXPECT_TRUE(RunTest(UpperBound<int>, v1, 1, 0, 1));
  EXPECT_TRUE(RunTest(UpperBound<int>, v1, 2, 0, 1));
  EXPECT_TRUE(RunTest(UpperBound<int>, v1, 3, 1, 2));
  EXPECT_TRUE(RunTest(UpperBound<int>, v1, 3, 0, 2));
  EXPECT_TRUE(RunTest(UpperBound<int>, v1, 0, 0, 0));
  EXPECT_TRUE(RunTest(UpperBound<int>, v1, 0, 0, 0));
  EXPECT_TRUE(RunTest(UpperBound<int>, v1, 4, 0, 2));
  EXPECT_TRUE(RunTest(UpperBound<int>, v1, 5, 0, 3));
  EXPECT_TRUE(RunTest(UpperBound<int>, v1, 9, 0, 6));
  EXPECT_TRUE(RunTest(UpperBound<int>, v1, 9, 0, 6));
  EXPECT_TRUE(RunTest(UpperBound<int>, v1, 11, 0, 7));
  EXPECT_TRUE(RunTest(UpperBound<int>, v1, 12, 0, 7));

  vector<int> v2 = {};
  EXPECT_TRUE(RunTest(UpperBound1<int>, v2, 12, -1, 0));
  EXPECT_TRUE(RunTest(UpperBound<int>, v2, 12, 0, 0));
  EXPECT_TRUE(RunTest(UpperBound1<int>, v2, 0, -1, 0));
  EXPECT_TRUE(RunTest(UpperBound<int>, v2, 0, 0, 0));

  vector<int> v3 = {0};
  EXPECT_TRUE(RunTest(UpperBound1<int>, v3, 12, -1, 1));
  EXPECT_TRUE(RunTest(UpperBound<int>, v3, 12, 0, 1));
  EXPECT_TRUE(RunTest(UpperBound1<int>, v3, 0, -1, 1));
  EXPECT_TRUE(RunTest(UpperBound<int>, v3, 0, 0, 1));
  EXPECT_TRUE(RunTest(UpperBound1<int>, v3, -1, -1, 0));
  EXPECT_TRUE(RunTest(UpperBound<int>, v3, -1, 0, 0));


  vector<int> v4 = {0, 5, 5};
  EXPECT_TRUE(RunTest(UpperBound1<int>, v4, 12, -1, 3));
  EXPECT_TRUE(RunTest(UpperBound<int>, v4, 12, 0, 3));
  EXPECT_TRUE(RunTest(UpperBound1<int>, v4, 0, -1, 1));
  EXPECT_TRUE(RunTest(UpperBound<int>, v4, 0, 0, 1));
  EXPECT_TRUE(RunTest(UpperBound1<int>, v4, -1, -1, 0));
  EXPECT_TRUE(RunTest(UpperBound<int>, v4, -1, 0, 0));

  EXPECT_TRUE(RunTest(UpperBound1<int>, v4, 5, -1, 3));
  EXPECT_TRUE(RunTest(UpperBound<int>, v4, 5, 0, 3));
}

struct TestCase
{
  vector<int> a, b, expect;
  TestCase(vector<int> a1, vector<int> b1, vector<int> result):
    a(a1), b(b1), expect(result)
  {
  }
  bool Run()
  {
    vector<int> result;
    BinaryIntersect(a, b, result);
    return result.size() == expect.size() &&
      std::equal(expect.begin(), expect.end(), result.begin());
  }
};

TEST(BinarySearch, BinaryIntersect)
{
  EXPECT_TRUE(TestCase({}, {}, {}).Run());
  EXPECT_TRUE(TestCase({1}, {}, {}).Run());
  EXPECT_TRUE(TestCase({}, {1}, {}).Run());
  EXPECT_TRUE(TestCase({1}, {1}, {1}).Run());
  EXPECT_TRUE(TestCase({1, 2,}, {}, {}).Run());
  EXPECT_TRUE(TestCase({1, 2}, {1}, {1}).Run());
  EXPECT_TRUE(TestCase({1}, {1, 2}, {1}).Run());
  EXPECT_TRUE(TestCase({1, 2}, {2}, {2}).Run());
  EXPECT_TRUE(TestCase({2}, {1, 2}, {2}).Run());
  EXPECT_TRUE(TestCase({1, 2}, {1, 2}, {1, 2}).Run());


  EXPECT_TRUE(TestCase({1, 2, 3}, {3}, {3}).Run());
  EXPECT_TRUE(TestCase({1, 2, 3}, {1, 3}, {1, 3}).Run());
  EXPECT_TRUE(TestCase({1, 2, 3, 4}, {1, 4}, {1, 4}).Run());
  EXPECT_TRUE(TestCase({1, 3, 5}, {4, 6}, {}).Run());

  EXPECT_TRUE(TestCase({1, 5, 9, 10, 12}, {0, 3, 9, 11}, {9}).Run());
  EXPECT_TRUE(TestCase({0, 1, 2, 5, 10}, {1, 3, 5, 7, 9, 11}, {1, 5}).Run());
  EXPECT_TRUE(TestCase({1, 5, 9, 10, 12}, {13}, {}).Run());
  EXPECT_TRUE(TestCase({1, 5, 9, 10, 12}, {5, 11}, {5}).Run());
}

int main (int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    int returnValue;
    //Do whatever setup here you will need for your tests here
    //
    //
    returnValue =  RUN_ALL_TESTS();
    //Do Your teardown here if required
    //
    //
    return returnValue;
}
