// Copyright 2021 Tencent
// SPDX-License-Identifier: BSD-3-Clause

#include "testutil.h"

static int test_squeeze(const ncnn::Mat& a, int squeeze_w, int squeeze_h, int squeeze_d, int squeeze_c)
{
    ncnn::ParamDict pd;
    pd.set(0, squeeze_w);
    pd.set(1, squeeze_h);
    pd.set(11, squeeze_d);
    pd.set(2, squeeze_c);

    std::vector<ncnn::Mat> weights(0);

    int ret = test_layer("Squeeze", pd, weights, a);
    if (ret != 0)
    {
        fprintf(stderr, "test_squeeze failed a.dims=%d a=(%d %d %d %d) squeeze_w=%d squeeze_h=%d squeeze_d=%d squeeze_c=%d\n", a.dims, a.w, a.h, a.d, a.c, squeeze_w, squeeze_h, squeeze_d, squeeze_c);
    }

    return ret;
}

static std::vector<int> IntArray(int a0)
{
    std::vector<int> m(1);
    m[0] = a0;
    return m;
}

static std::vector<int> IntArray(int a0, int a1)
{
    std::vector<int> m(2);
    m[0] = a0;
    m[1] = a1;
    return m;
}

static std::vector<int> IntArray(int a0, int a1, int a2)
{
    std::vector<int> m(3);
    m[0] = a0;
    m[1] = a1;
    m[2] = a2;
    return m;
}

static std::vector<int> IntArray(int a0, int a1, int a2, int a3)
{
    std::vector<int> m(4);
    m[0] = a0;
    m[1] = a1;
    m[2] = a2;
    m[3] = a3;
    return m;
}

static void print_int_array(const std::vector<int>& a)
{
    fprintf(stderr, "[");
    for (size_t i = 0; i < a.size(); i++)
    {
        fprintf(stderr, " %d", a[i]);
    }
    fprintf(stderr, " ]");
}

static int test_squeeze_axes(const ncnn::Mat& a, const std::vector<int>& axes_array)
{
    ncnn::Mat axes(axes_array.size());
    {
        int* p = axes;
        for (size_t i = 0; i < axes_array.size(); i++)
        {
            p[i] = axes_array[i];
        }
    }

    ncnn::ParamDict pd;
    pd.set(3, axes);

    std::vector<ncnn::Mat> weights(0);

    int ret = test_layer("Squeeze", pd, weights, a);
    if (ret != 0)
    {
        fprintf(stderr, "test_squeeze_axes failed a.dims=%d a=(%d %d %d %d)\n", a.dims, a.w, a.h, a.d, a.c);
        fprintf(stderr, " axes=");
        print_int_array(axes_array);
        fprintf(stderr, "\n");
    }

    return ret;
}

static int test_squeeze_all_params(const ncnn::Mat& a)
{
    return 0
           || test_squeeze(a, 0, 0, 0, 0)
           || test_squeeze(a, 0, 0, 0, 1)
           || test_squeeze(a, 0, 0, 1, 0)
           || test_squeeze(a, 0, 0, 1, 1)
           || test_squeeze(a, 0, 1, 0, 0)
           || test_squeeze(a, 0, 1, 0, 1)
           || test_squeeze(a, 0, 1, 1, 0)
           || test_squeeze(a, 0, 1, 1, 1)
           || test_squeeze(a, 1, 0, 0, 0)
           || test_squeeze(a, 1, 0, 0, 1)
           || test_squeeze(a, 1, 0, 1, 0)
           || test_squeeze(a, 1, 0, 1, 1)
           || test_squeeze(a, 1, 1, 0, 0)
           || test_squeeze(a, 1, 1, 0, 1)
           || test_squeeze(a, 1, 1, 1, 0)
           || test_squeeze(a, 1, 1, 1, 1)

           || test_squeeze_axes(a, IntArray(0))
           || test_squeeze_axes(a, IntArray(1))
           || test_squeeze_axes(a, IntArray(2))
           || test_squeeze_axes(a, IntArray(3))
           || test_squeeze_axes(a, IntArray(0, 1))
           || test_squeeze_axes(a, IntArray(0, 2))
           || test_squeeze_axes(a, IntArray(0, 3))
           || test_squeeze_axes(a, IntArray(1, 2))
           || test_squeeze_axes(a, IntArray(1, 3))
           || test_squeeze_axes(a, IntArray(2, 3))
           || test_squeeze_axes(a, IntArray(0, 1, 2))
           || test_squeeze_axes(a, IntArray(0, 1, 3))
           || test_squeeze_axes(a, IntArray(0, 2, 3))
           || test_squeeze_axes(a, IntArray(1, 2, 3))
           || test_squeeze_axes(a, IntArray(0, 1, 2, 3));
}

static int test_squeeze_0()
{
    return 0
           || test_squeeze_all_params(RandomMat(4, 5, 7, 16))
           || test_squeeze_all_params(RandomMat(4, 5, 1, 15))
           || test_squeeze_all_params(RandomMat(4, 1, 7, 12))
           || test_squeeze_all_params(RandomMat(1, 5, 7, 16))
           || test_squeeze_all_params(RandomMat(1, 5, 1, 15))
           || test_squeeze_all_params(RandomMat(1, 1, 7, 12))
           || test_squeeze_all_params(RandomMat(6, 1, 1, 16))
           || test_squeeze_all_params(RandomMat(1, 1, 1, 15))
           || test_squeeze_all_params(RandomMat(4, 5, 7, 1))
           || test_squeeze_all_params(RandomMat(4, 5, 1, 1))
           || test_squeeze_all_params(RandomMat(4, 1, 7, 1))
           || test_squeeze_all_params(RandomMat(1, 5, 7, 1))
           || test_squeeze_all_params(RandomMat(1, 5, 1, 1))
           || test_squeeze_all_params(RandomMat(1, 1, 7, 1))
           || test_squeeze_all_params(RandomMat(1, 1, 1, 1));
}

static int test_squeeze_1()
{
    return 0
           || test_squeeze_all_params(RandomMat(3, 12, 16))
           || test_squeeze_all_params(RandomMat(3, 1, 16))
           || test_squeeze_all_params(RandomMat(1, 33, 15))
           || test_squeeze_all_params(RandomMat(1, 14, 1))
           || test_squeeze_all_params(RandomMat(12, 13, 1))
           || test_squeeze_all_params(RandomMat(1, 1, 1));
}

static int test_squeeze_2()
{
    return 0
           || test_squeeze_all_params(RandomMat(14, 16))
           || test_squeeze_all_params(RandomMat(1, 14))
           || test_squeeze_all_params(RandomMat(11, 1))
           || test_squeeze_all_params(RandomMat(1, 1));
}

static int test_squeeze_3()
{
    return 0
           || test_squeeze_all_params(RandomMat(120))
           || test_squeeze_all_params(RandomMat(1));
}

int main()
{
    SRAND(7767517);

    return test_squeeze_0() || test_squeeze_1() || test_squeeze_2() || test_squeeze_3();
}
