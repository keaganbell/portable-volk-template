#define NOB_IMPLEMENTATION
#include "nob.h"

int main(int argc, char **argv) {
    NOB_GO_REBUILD_URSELF(argc, argv);
    
    if (!nob_mkdir_if_not_exists("build")) return 1;

    Nob_Cmd compile = {0};
    nob_cmd_append(&compile, "cl.exe");
    nob_cmd_append(&compile, "-Zi", "-MT", "-nologo", "-FC", "-FS");
    nob_cmd_append(&compile, "-Fobuild\\main.obj");
    nob_cmd_append(&compile, "-Fdbuild\\tergen_compiler.pdb");
    nob_cmd_append(&compile, "-Febuild\\tergen.exe");
    nob_cmd_append(&compile, "-Icode");
    nob_cmd_append(&compile, "-DVOLK_VULKAN_H_PATH=\"vulkan/vulkan.h\"");
    nob_cmd_append(&compile, "code/main.c");
    nob_cmd_append(&compile, "-link");
    nob_cmd_append(&compile, "-incremental:no");
    nob_cmd_append(&compile, "-pdb:build\\terger_linker.pdb");
    if (!nob_cmd_run(&compile)) return 1;

    return 0;
}