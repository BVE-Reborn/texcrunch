use ispc::TargetISA;
use std::env;

fn main() {
    ispc::Config::new()
        .target_isas(vec![
            TargetISA::SSE2i32x8,
            TargetISA::SSE4i32x8,
            TargetISA::AVX1i32x16,
            TargetISA::AVX2i32x16,
            TargetISA::AVX512KNLi32x16,
            TargetISA::AVX512SKXi32x16,
        ])
        .file("ispc-texcomp/ispc_texcomp/kernel.ispc")
        .file("ispc-texcomp/ispc_texcomp/kernel_astc.ispc")
        .wno_perf()
        .woff()
        .compile("ispc-texcomp");
    cc::Build::new()
        .cpp(true)
        .include("ispc-texcomp/ispc_texcomp")
        .include(env::var_os("OUT_DIR").unwrap())
        .files(&[
            "ispc-texcomp/ispc_texcomp/ispc_texcomp.cpp",
            "ispc-texcomp/ispc_texcomp/ispc_texcomp_astc.cpp",
        ])
        .compile("ispc-texcomp-cpp");
}
