#if defined(_WIN64)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include "volk/volk.h"
#include "volk/volk.c"

#include "core.h"
#include "backend.h"
#include "backend.c"

int main(void) {
    Vulkan_State vk = {0};
    if (!vulkan_bakend_create_instance(&vk)) return 1;
    print_info("Vulkan instance created successfully!");
    return 0;
}
