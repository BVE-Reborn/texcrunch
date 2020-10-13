mod ffi {
    ispc::ispc_module!(bc7e);
}

pub use ffi::{
    bc7e::_anon36_ as bc7e_opaque_settings, //
    bc7e::_anon37_ as bc7e_alpha_settings,
    bc7e::bc7e_compress_block_init,
    bc7e::bc7e_compress_block_params,
    bc7e::bc7e_compress_block_params_init,
    bc7e::bc7e_compress_block_params_init_basic,
    bc7e::bc7e_compress_block_params_init_fast,
    bc7e::bc7e_compress_block_params_init_slow,
    bc7e::bc7e_compress_block_params_init_slowest,
    bc7e::bc7e_compress_block_params_init_ultrafast,
    bc7e::bc7e_compress_block_params_init_veryfast,
    bc7e::bc7e_compress_block_params_init_veryslow,
    bc7e::bc7e_compress_blocks,
};
