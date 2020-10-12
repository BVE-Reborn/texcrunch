mod ffi {
    ispc::ispc_module!(bc7e);
}

pub use ffi::bc7e::_anon36_ as bc7e_opaque_settings;
pub use ffi::bc7e::_anon37_ as bc7e_alpha_settings;
pub use ffi::bc7e::bc7e_compress_block_params;

pub use ffi::bc7e::bc7e_compress_block_init;
pub use ffi::bc7e::bc7e_compress_block_params_init;
pub use ffi::bc7e::bc7e_compress_block_params_init_basic;
pub use ffi::bc7e::bc7e_compress_block_params_init_fast;
pub use ffi::bc7e::bc7e_compress_block_params_init_slow;
pub use ffi::bc7e::bc7e_compress_block_params_init_slowest;
pub use ffi::bc7e::bc7e_compress_block_params_init_ultrafast;
pub use ffi::bc7e::bc7e_compress_block_params_init_veryfast;
pub use ffi::bc7e::bc7e_compress_block_params_init_veryslow;
pub use ffi::bc7e::bc7e_compress_blocks;
