use std::env;
use std::path::PathBuf;

fn main() {
    let bindings = bindgen::builder()
        .header("src/wrapper.hpp")
        .enable_cxx_namespaces()
        .generate()
        .unwrap();

    let out_path = PathBuf::from(env::var("OUT_DIR").unwrap());
    bindings.write_to_file(out_path.join("bc7enc.rs")).unwrap();

    cc::Build::new()
        .cpp(true)
        .include("bc7enc/")
        .files(&["bc7enc/bc7enc.c", "src/rgbcx.cpp"])
        .compile("bc7enc");
}
