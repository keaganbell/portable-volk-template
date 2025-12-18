#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "volk/volk.h"
#include "volk/volk.c"

#include "core.h"

typedef struct {
    VkInstance instance;
} Vulkan_State;

bool vulkan_bakend_create_instance(Vulkan_State *vk) {
    if (volkInitialize() != VK_SUCCESS) {
        print_error("Volk failed to initialize.");
        return false;
    }
    const char *extensions[] = { "VK_KHR_surface", "VK_KHR_win32_surface" };
    VkInstanceCreateInfo create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.enabledExtensionCount = array_count(extensions);
    create_info.ppEnabledExtensionNames = extensions;
    if (vkCreateInstance(&create_info, NULL, &vk->instance) != VK_SUCCESS) {
        print_error("Failed to create Vulkan instance");
        return false;
    }
    return true;
}

int main(void) {
    Vulkan_State vk = {0};
    if (!vulkan_bakend_create_instance(&vk)) return 1;
    print_info("Vulkan instance created successfully!");
    return 0;
}
