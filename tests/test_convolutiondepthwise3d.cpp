// Copyright 2019 Tencent
// SPDX-License-Identifier: BSD-3-Clause

#include "testutil.h"

static int test_convolutiondepthwise3d(int w, int h, int d, int c, int outch, int kernel, int dilation, int stride, int pad, int bias, int group)
{
    ncnn::Mat a = RandomMat(w, h, d, c);

    ncnn::ParamDict pd;
    pd.set(0, outch);    // num_output
    pd.set(1, kernel);   // kernel_w
    pd.set(2, dilation); // dilation_w
    pd.set(3, stride);   // stride_w
    pd.set(4, pad);      // pad_w
    pd.set(5, bias);     // bias_term
    pd.set(6, outch / group * c / group * kernel * kernel * kernel * group);
    pd.set(7, group);

    int activation_type = RAND() % 7; // 0 1 2 3 4 5 6
    ncnn::Mat activation_params(2);
    activation_params[0] = (activation_type == 6) ? RandomFloat(0, 1) : RandomFloat(-1, 0); // alpha
    activation_params[1] = RandomFloat(0, 1);                                               // beta
    pd.set(9, activation_type);
    pd.set(10, activation_params);

    std::vector<ncnn::Mat> weights(2);
    weights[0] = RandomMat(outch / group * c / group * kernel * kernel * kernel * group);
    weights[1] = RandomMat(outch);

    int ret = test_layer("ConvolutionDepthWise3D", pd, weights, a);
    if (ret != 0)
    {
        fprintf(stderr, "test_convolutiondepthwise3d failed w=%d h=%d d=%d c=%d outch=%d kernel=%d dilation=%d stride=%d pad=%d bias=%d group=%d act=%d actparams=[%f,%f]\n", w, h, d, c, outch, kernel, dilation, stride, pad, bias, group, activation_type, activation_params[0], activation_params[1]);
    }

    return ret;
}

static int test_convolutiondepthwise3d_0()
{
    static const int kdsp[7][4] = {
        {1, 1, 1, 0},
        {1, 1, 2, 0},
        {2, 1, 1, 1},
        {2, 1, 2, -233},
        {3, 1, 1, 1},
        {3, 1, 2, 1},
        {3, 2, 1, -234},
    };

    for (int i = 0; i < 7; i++)
    {
        const int k = kdsp[i][0];
        const int d = kdsp[i][1];
        const int s = kdsp[i][2];
        const int p = kdsp[i][3];

        int ret = 0
                  || test_convolutiondepthwise3d(11, 10, 9, 1, 1, k, d, s, p, 1, 1)
                  || test_convolutiondepthwise3d(11, 10, 9, 2, 2, k, d, s, p, 0, 1)
                  || test_convolutiondepthwise3d(11, 10, 9, 2, 2, k, d, s, p, 1, 2)
                  || test_convolutiondepthwise3d(11, 10, 9, 3, 3, k, d, s, p, 0, 3)
                  || test_convolutiondepthwise3d(11, 10, 9, 4, 2, k, d, s, p, 1, 2)
                  || test_convolutiondepthwise3d(11, 10, 9, 4, 4, k, d, s, p, 0, 4)
                  || test_convolutiondepthwise3d(11, 10, 9, 7, 7, k, d, s, p, 1, 7)
                  || test_convolutiondepthwise3d(11, 10, 9, 8, 8, k, d, s, p, 0, 2)
                  || test_convolutiondepthwise3d(11, 10, 9, 8, 8, k, d, s, p, 1, 8)
                  || test_convolutiondepthwise3d(11, 10, 9, 12, 12, k, d, s, p, 0, 4)
                  || test_convolutiondepthwise3d(11, 10, 9, 15, 15, k, d, s, p, 1, 15)
                  || test_convolutiondepthwise3d(11, 10, 9, 16, 8, k, d, s, p, 0, 2)
                  || test_convolutiondepthwise3d(11, 10, 9, 16, 16, k, d, s, p, 1, 16);

        if (ret != 0)
            return -1;
    }

    return 0;
}

int main()
{
    SRAND(7767517);

    return test_convolutiondepthwise3d_0();
}
