
using System.Runtime.InteropServices;

namespace AtomicEngine
{
    [StructLayout(LayoutKind.Sequential)]
    public struct BiasParameters
    {
        public float ConstantBias;
        public float SlopeScaleBias;
        public float NormalOffset;

        public BiasParameters(float constantBias, float slopeScaleBias, float normalOffset = 0.0f)
        {
            ConstantBias = constantBias;
            SlopeScaleBias = slopeScaleBias;
            NormalOffset = normalOffset;
        }
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct CascadeParameters
    {
        public float Split1, Split2, Split3, Split4;
        public float FadeStart;
        public float BiasAutoAdjust;

        public CascadeParameters(float split1, float split2, float split3, float split4, float fadeStart, float biasAutoAdjust = 1f)
        {
            Split1 = split1;
            Split2 = split2;
            Split3 = split3;
            Split4 = split4;
            FadeStart = fadeStart;
            BiasAutoAdjust = biasAutoAdjust;
        }
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct FocusParameters
    {
        public byte Focus;
        public byte NonUniform;
        public byte AutoSize;
        public float Quantize;
        public float MinView;
    }
}
