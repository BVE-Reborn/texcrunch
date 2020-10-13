#[allow(warnings)]
mod ffi {
    include!(concat!(env!("OUT_DIR"), "/bc7enc.rs"));
}

pub use ffi::root::{
    bc7enc_bool,
    bc7enc_compress_block,
    bc7enc_compress_block_init,
    bc7enc_compress_block_params,
    BC7ENC_BLOCK_SIZE, //
    BC7ENC_FALSE,
    BC7ENC_MAX_PARTITIONS1,
    BC7ENC_MAX_UBER_LEVEL,
    BC7ENC_TRUE,
};

pub use ffi::root::rgbcx::{
    bc1_approx_mode,
    bc1_approx_mode_cBC1AMD, //
    bc1_approx_mode_cBC1Ideal,
    bc1_approx_mode_cBC1IdealRound4,
    bc1_approx_mode_cBC1NVidia,
    encode_bc1,
    encode_bc11,
    encode_bc1_solid_block,
    encode_bc3,
    encode_bc31,
    encode_bc4,
    encode_bc5,
    init,
    rgbcx_cEncodeBC1BoundingBox,
    rgbcx_cEncodeBC1BoundingBoxInt,
    rgbcx_cEncodeBC1EndpointSearchRoundsMask,
    rgbcx_cEncodeBC1EndpointSearchRoundsShift,
    rgbcx_cEncodeBC1Exhaustive,
    rgbcx_cEncodeBC1Iterative,
    rgbcx_cEncodeBC1TryAllInitialEndponts,
    rgbcx_cEncodeBC1TwoLeastSquaresPasses,
    rgbcx_cEncodeBC1Use2DLS,
    rgbcx_cEncodeBC1Use3ColorBlocks,
    rgbcx_cEncodeBC1Use3ColorBlocksForBlackPixels,
    rgbcx_cEncodeBC1Use6PowerIters,
    rgbcx_cEncodeBC1UseFasterMSEEval,
    rgbcx_cEncodeBC1UseFullMSEEval,
    rgbcx_cEncodeBC1UseLikelyTotalOrderings,
    unpack_bc1,
    unpack_bc3,
    unpack_bc4,
    unpack_bc5,
    DEFAULT_TOTAL_ORDERINGS_TO_TRY,
    DEFAULT_TOTAL_ORDERINGS_TO_TRY3,
    MAX_LEVEL,
    MAX_TOTAL_ORDERINGS3,
    MAX_TOTAL_ORDERINGS4,
    MIN_LEVEL,
    MIN_TOTAL_ORDERINGS,
};
