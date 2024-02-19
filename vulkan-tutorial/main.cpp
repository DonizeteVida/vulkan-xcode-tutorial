//
//  main.c
//  vulkan-tutorial
//
//  Created by Donizete Vida on 18/02/24.
//
#define GLFW_INCLUDE_VULKAN
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

class HelloTriangleApplication {
public:
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanUp();
    }
private:
    const uint16_t WIDTH = 800;
    const uint16_t HEIGHT = 600;
    GLFWwindow* glfwWindow;

    std::vector<const char*> requiredVulkanExtensions;
    VkInstance vkInstance;

    void initWindow() {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        glfwWindow = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
        uint32_t glfwVulkanExtensionCount;
        const char** glfwVulkanExtensions = glfwGetRequiredInstanceExtensions(&glfwVulkanExtensionCount);
        for (uint32_t i = 0; i < glfwVulkanExtensionCount; i++) {
            requiredVulkanExtensions.push_back(glfwVulkanExtensions[i]);
        }
    }

    void initVulkan() {
        createInstance();
    }

    void createInstance() {
        VkApplicationInfo vkApplicationInfo {
            .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
            .pApplicationName = "Hello Triangle",
            .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
            .pEngineName = "No Engine",
            .engineVersion = VK_MAKE_VERSION(1, 0, 0),
            .apiVersion = VK_API_VERSION_1_0,
        };

#ifdef __APPLE__
        requiredVulkanExtensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
        requiredVulkanExtensions.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
#endif

        VkInstanceCreateInfo vkInstanceCreateInfo {
            .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
            .pApplicationInfo = &vkApplicationInfo,
            .enabledExtensionCount = static_cast<uint32_t>(requiredVulkanExtensions.size()),
            .ppEnabledExtensionNames = requiredVulkanExtensions.data(),
            .enabledLayerCount = 0,
            .flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR,
        };

        if (vkCreateInstance(&vkInstanceCreateInfo, nullptr, &vkInstance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create vkInstance");
        }
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(glfwWindow)) {
            glfwPollEvents();
        }
    }

    void cleanUp() {
        glfwDestroyWindow(glfwWindow);
        glfwTerminate();
    }
};

int main() {
    HelloTriangleApplication app;
    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
