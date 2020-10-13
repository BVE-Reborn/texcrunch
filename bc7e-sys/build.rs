use ispc::TargetISA;

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
        .file("bc7e/bc7e.ispc")
        .wno_perf()
        .woff()
        .compile("bc7e");
}
