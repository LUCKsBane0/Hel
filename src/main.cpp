#include <SDL3/SDL.h>
#include <imgui.h>
#include <vulkan/vulkan.h>

#include <cstdint>
#include <iostream>

int main()
{
    std::uint32_t vulkanVersion = VK_API_VERSION_1_0;
    if (vkEnumerateInstanceVersion(&vulkanVersion) != VK_SUCCESS)
    {
        std::cerr << "Failed to query the Vulkan loader version.\n";
        return 1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    const int sdlVersion = SDL_GetVersion();
    std::cout << "Hel linked successfully against SDL "
              << SDL_VERSIONNUM_MAJOR(sdlVersion) << '.'
              << SDL_VERSIONNUM_MINOR(sdlVersion) << '.'
              << SDL_VERSIONNUM_MICRO(sdlVersion)
              << ", Vulkan " << VK_API_VERSION_MAJOR(vulkanVersion) << '.'
              << VK_API_VERSION_MINOR(vulkanVersion) << '.'
              << VK_API_VERSION_PATCH(vulkanVersion)
              << ", and Dear ImGui " << IMGUI_VERSION << ".\n";

    ImGui::DestroyContext();
    return 0;
}
