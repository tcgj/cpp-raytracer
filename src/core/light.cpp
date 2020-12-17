#include "light.hpp"

namespace TK {
    std::unique_ptr<Distribution> lightPowerDistribution(const Scene& scene) {
        if (scene.m_Lights.empty())
            return 0;

        std::vector<tkFloat> powers;
        for (const auto& light : scene.m_Lights) {
            powers.push_back(light->power().luminance());
        }
        return std::make_unique<Distribution>(powers);
    }
}  // namespace TK
