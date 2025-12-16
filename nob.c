#define NOB_IMPLEMENTATION
#include "nob.h"

int main(int argc, char **argv) {
    NOB_GO_REBUILD_URSELF(argc, argv);
    
    if (!nob_mkdir_if_not_exists("build")) return 1;

    Nob_Cmd compile = {0};
    nob_cmd_append(&compile, "gcc");
    nob_cmd_append(&compile, "-o", "build/tergen.exe");
    nob_cmd_append(&compile, "code/main.c");
    nob_cmd_append(&compile, "-Wall", "-Wextra");
    nob_cmd_append(&compile, "-Icode/");
    nob_cmd_append(&compile, "-DVOLK_VULKAN_H_PATH=\"C:\\Users\\kbell\\Coding\\Projects\\terrain\\code\\vulkan\\vulkan.h\"");
    if (!nob_cmd_run(&compile)) return 1;

    return 0;
}