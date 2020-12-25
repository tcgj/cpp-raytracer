#include "whitted.hpp"

#include "core/scene.hpp"
#include "core/bsdf.hpp"
#include "core/light.hpp"
#include "core/interaction.hpp"
#include "core/spectrum.hpp"
#include "core/sampler.hpp"
#include "util/scatteringutil.hpp"

namespace TK {
    tkSpectrum WhittedIntegrator::Li(const Scene& scene, const Ray& r, Sampler& sampler, int depth) const {
        tkSpectrum li;
        SurfaceInteraction interaction;
        if (!scene.intersect(r, &interaction)) {
            // TODO: get radiance contribution from
            // light source along the ray if any (sky light etc)
            return li;
        }

        BSDF bsdf;
        interaction.computeScattering(&bsdf);

        Vec3f normal = interaction.n;
        Vec3f wo = interaction.wo;

        // Add emission contribution if interaction with light
        li += interaction.Le();

        // Add contribution of lighting on surface point
        for (const auto& light : scene.m_Lights) {
            // Ignore non-delta light source as whitted integrator does not handle
            // if (!light->isDelta())
            // continue;

            Vec3f wi;
            tkFloat pdf;
            OcclusionChecker occCheck;
            tkSpectrum ld = light->sample(interaction, &wi, sampler.nextVector(), &pdf, &occCheck);
            if (pdf == 0 || ld.isBlack())
                continue;

            tkSpectrum f = bsdf.evaluate(wo, wi);
            if (!f.isBlack() && occCheck.notOccluded(scene))
                li += f * ld * std::abs(dot(wi, normal)) / pdf;
        }

        // Spawn secondary rays from intersection point
        // if depth is under max depth
        if (depth < m_MaxDepth - 1) {
            li += specularReflectedLi(interaction, scene, r, sampler, depth);
            li += specularRefractedLi(interaction, scene, r, sampler, depth);
        }

        return li;
    }
}  // namespace TK
