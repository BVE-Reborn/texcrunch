#ifndef RGBCX_INCLUDE_H
#define RGBCX_INCLUDE_H

#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <limits.h>

namespace rgbcx
{
    enum class bc1_approx_mode
    {
        // The default mode. No rounding for 4-color colors 2,3. My older tools/compressors use this mode.
        // This matches the D3D10 docs on BC1.
        cBC1Ideal = 0,

        // NVidia GPU mode.
        cBC1NVidia = 1,

        // AMD GPU mode.
        cBC1AMD = 2,

        // This mode matches AMD Compressonator's output. It rounds 4-color colors 2,3 (not 3-color color 2).
        // This matches the D3D9 docs on DXT1.
        cBC1IdealRound4 = 3
    };

    // init() MUST be called once before using the BC1 encoder.
    // This function may be called multiple times to change the BC1 approximation mode.
    // This function initializes global state, so don't call it while other threads inside the encoder.
    // Important: If you encode textures for a specific vendor's GPU's, beware that using that texture data on other GPU's may result in ugly artifacts.
    // Encode to cBC1Ideal unless you know the texture data will only be deployed or used on a specific vendor's GPU.
    void init(bc1_approx_mode mode = bc1_approx_mode::cBC1Ideal);

    // Optimally encodes a solid color block to BC1 format.
    void encode_bc1_solid_block(void* pDst, uint32_t fr, uint32_t fg, uint32_t fb, bool allow_3color);

    // BC1 low-level API encoder flags. You can ignore this if you use the simple level API.
    enum
    {
        // Try to improve quality using the most likely total orderings.
        // The total_orderings_to_try parameter will then control the number of total orderings to try for 4 color blocks, and the
        // total_orderings_to_try3 parameter will control the number of total orderings to try for 3 color blocks (if they are enabled).
        cEncodeBC1UseLikelyTotalOrderings = 2,

        // Use 2 least squares pass, instead of one (same as stb_dxt's HIGHQUAL option).
        // Recommended if you're enabling cEncodeBC1UseLikelyTotalOrderings.
        cEncodeBC1TwoLeastSquaresPasses = 4,

        // cEncodeBC1Use3ColorBlocksForBlackPixels allows the BC1 encoder to use 3-color blocks for blocks containing black or very dark pixels.
        // You shader/engine MUST ignore the alpha channel on textures encoded with this flag.
        // Average quality goes up substantially for my 100 texture corpus (~.5 dB), so it's worth using if you can.
        // Note the BC1 encoder does not actually support transparency in 3-color mode.
        // Don't set when encoding to BC3.
        cEncodeBC1Use3ColorBlocksForBlackPixels = 8,

        // If cEncodeBC1Use3ColorBlocks is set, the encoder can use 3-color mode for a small but noticeable gain in average quality, but lower perf.
        // If you also specify the cEncodeBC1UseLikelyTotalOrderings flag, set the total_orderings_to_try3 paramter to the number of total orderings to try.
        // Don't set when encoding to BC3.
        cEncodeBC1Use3ColorBlocks = 16,

        // cEncodeBC1Iterative will greatly increase encode time, but is very slightly higher quality.
        // Same as squish's iterative cluster fit option. Not really worth the tiny boost in quality, unless you just don't care about perf. at all.
        cEncodeBC1Iterative = 32,

        // cEncodeBC1BoundingBox enables a fast all-integer PCA approximation on 4-color blocks.
        // At level 0 options (no other flags), this is ~15% faster, and higher *average* quality.
        cEncodeBC1BoundingBox = 64,

        // Use a slightly lower quality, but ~30% faster MSE evaluation function for 4-color blocks.
        cEncodeBC1UseFasterMSEEval = 128,

        // Examine all colors to compute selectors/MSE (slower than default)
        cEncodeBC1UseFullMSEEval = 256,

        // Use 2D least squares+inset+optimal rounding (the method used in Humus's GPU texture encoding demo), instead of PCA.
        // Around 18% faster, very slightly lower average quality to better (depends on the content).
        cEncodeBC1Use2DLS = 512,

        // Use 6 power iterations vs. 4 for PCA.
        cEncodeBC1Use6PowerIters = 2048,

        // Check all total orderings - *very* slow. The encoder is not designed to be used in this way.
        cEncodeBC1Exhaustive = 8192,

        // Try 2 different ways of choosing the initial endpoints.
        cEncodeBC1TryAllInitialEndponts = 16384,

        // Same as cEncodeBC1BoundingBox, but implemented using integer math (faster, slightly less quality)
        cEncodeBC1BoundingBoxInt = 32768,

        // Try refining the final endpoints by examining nearby colors.
        cEncodeBC1EndpointSearchRoundsShift = 22,
        cEncodeBC1EndpointSearchRoundsMask = 1023U << cEncodeBC1EndpointSearchRoundsShift,
    };

    const uint32_t MIN_TOTAL_ORDERINGS = 1;
    const uint32_t MAX_TOTAL_ORDERINGS3 = 32;

#if RGBCX_USE_SMALLER_TABLES
    const uint32_t MAX_TOTAL_ORDERINGS4 = 32;
#else
    const uint32_t MAX_TOTAL_ORDERINGS4 = 128;
#endif

    // DEFAULT_TOTAL_ORDERINGS_TO_TRY is around 3x faster than libsquish at slightly higher average quality. 10-16 is a good range to start to compete against libsquish.
    const uint32_t DEFAULT_TOTAL_ORDERINGS_TO_TRY = 10;

    const uint32_t DEFAULT_TOTAL_ORDERINGS_TO_TRY3 = 1;

    // Encodes a 4x4 block of RGBX (X=ignored) pixels to BC1 format.
    // This is the simplified interface for BC1 encoding, which accepts a level parameter and converts that to the best overall flags.
    // The pixels are in RGBA format, where R is first in memory. The BC1 encoder completely ignores the alpha channel (i.e. there is no punchthrough alpha support).
    // This is the recommended function to use for BC1 encoding, becuase it configures the encoder for you in the best possible way (on average).
    // Note that the 3 color modes won't be used at all until level 5 or higher.
    // No transparency supported, however if you set use_transparent_texels_for_black to true the encocer will use transparent selectors on very dark/black texels to reduce MSE.
    const uint32_t MIN_LEVEL = 0, MAX_LEVEL = 18;
    void encode_bc1(uint32_t level, void* pDst, const uint8_t* pPixels, bool allow_3color, bool use_transparent_texels_for_black);

    // Low-level interface for BC1 encoding.
    // Always returns a 4 color block, unless cEncodeBC1Use3ColorBlocksForBlackPixels or cEncodeBC1Use3ColorBlock flags are specified.
    // total_orderings_to_try controls the perf. vs. quality tradeoff on 4-color blocks when the cEncodeBC1UseLikelyTotalOrderings flag is used. It must range between [MIN_TOTAL_ORDERINGS, MAX_TOTAL_ORDERINGS4].
    // total_orderings_to_try3 controls the perf. vs. quality tradeoff on 3-color bocks when the cEncodeBC1UseLikelyTotalOrderings and the cEncodeBC1Use3ColorBlocks flags are used. Valid range is [0,MAX_TOTAL_ORDERINGS3] (0=disabled).
    void encode_bc1(void* pDst, const uint8_t* pPixels, uint32_t flags = 0, uint32_t total_orderings_to_try = DEFAULT_TOTAL_ORDERINGS_TO_TRY, uint32_t total_orderings_to_try3 = DEFAULT_TOTAL_ORDERINGS_TO_TRY3);

    // Encodes a 4x4 block of RGBA pixels to BC3 format.
    // There are two encode_bc3() functions.
    // The first is the recommended function, which accepts a level parameter.
    // The second is a low-level version that allows fine control over BC1 encoding.
    void encode_bc3(uint32_t level, void* pDst, const uint8_t* pPixels);
    void encode_bc3(void* pDst, const uint8_t* pPixels, uint32_t flags = 0, uint32_t total_orderings_to_try = DEFAULT_TOTAL_ORDERINGS_TO_TRY);

    // Encodes a single channel to BC4.
    // stride is the source pixel stride in bytes.
    void encode_bc4(void* pDst, const uint8_t* pPixels, uint32_t stride = 4);

    // Encodes two channels to BC5.
    // chan0/chan1 control which channels, stride is the source pixel stride in bytes.
    void encode_bc5(void* pDst, const uint8_t* pPixels, uint32_t chan0 = 0, uint32_t chan1 = 1, uint32_t stride = 4);

    // Decompression functions.

    // Returns true if the block uses 3 color punchthrough alpha mode.
    bool unpack_bc1(const void* pBlock_bits, void* pPixels, bool set_alpha = true, bc1_approx_mode mode = bc1_approx_mode::cBC1Ideal);

    void unpack_bc4(const void* pBlock_bits, uint8_t* pPixels, uint32_t stride = 4);

    // Returns true if the block uses 3 color punchthrough alpha mode.
    bool unpack_bc3(const void* pBlock_bits, void* pPixels, bc1_approx_mode mode = bc1_approx_mode::cBC1Ideal);

    void unpack_bc5(const void* pBlock_bits, void* pPixels, uint32_t chan0 = 0, uint32_t chan1 = 1, uint32_t stride = 4);
}
#endif // #ifndef RGBCX_INCLUDE_H