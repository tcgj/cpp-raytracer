#include "specularreflection.hpp"

#include "bsdfutil.hpp"

namespace TK {
    tkSpectrum SpecularReflection::operator()(const tkVec3f &wo, const tkVec3f &wi) const {
        tkVec3f refl(-wo.x, -wo.y, wo.z);
        if (dot(wi, refl) < TK_ONE_MINUS_EPSILON)
            return 0;

        return dhr * fresnel->evaluate(cosTheta(wi)) / absCosTheta(wi);
    }

    tkSpectrum SpecularReflection::getSample(const tkVec3f &wo, tkVec3f *wi, tkFloat *pdf) const {
        *wi = tkVec3f(-wo.x, -wo.y, wo.z);
        *pdf = 1;
        return dhr * fresnel->evaluate(cosTheta(*wi)) / absCosTheta(*wi);
    }
} // namespace TK
