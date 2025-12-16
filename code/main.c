#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "volk/volk.h"
#include "volk/volk.c"

#include "core.h"

bool vulkan_create_instance(VkInstance *inst) {

    const char *layers[] = {
    };
    const char *extensions[] = {
        "VK_KHR_surface",
        "VK_KHR_win32_surface",

    };

    VkInstanceCreateInfo instance_info = {};
    instance_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instance_info.enabledLayerCount = array_count(layers);
    instance_info.ppEnabledLayerNames = layers;
    instance_info.enabledExtensionCount = array_count(extensions);
    instance_info.ppEnabledExtensionNames = extensions;

    VkInstance instance;
    if (vkCreateInstance(&instance_info, NULL, &instance) != VK_SUCCESS) {
        print_error("Failed to create Vulkan instance");
        return false;
    }
    *inst = instance;
    return true;
}

int main(void) {

    if (volkInitialize() != VK_SUCCESS) return 1;
    print_info("Volk - Intialize successfully!");

    VkInstance instance = 0;
    if (!vulkan_create_instance(&instance)) return 1;
    volkLoadInstance(instance);
    print_info("Vulkan - Intialize successfully!");


    return 0;
}
