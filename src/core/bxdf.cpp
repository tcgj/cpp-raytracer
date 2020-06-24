#include "bxdf.hpp"

#include "random.hpp"
#include "spectrum/rgbspectrum.hpp"
#include "util/scatteringutil.hpp"
#include "util/samplingutil.hpp"

namespace TK {
    bool BxDF::hasType(BxDFType t) const {
        return (t & type) == type;
    }

    tkFloat BxDF::getPdf(const tkVec3f &wo, const tkVec3f &wi) const {
        return isSameHemisphere(wo, wi) ? absCosTheta(wi) * TK_INVPI : 0;
    }

    tkSpectrum BxDF::sample(const tkVec3f &wo, tkVec3f *wi,
                                 tkFloat *pdf) const {
        *wi = cosHemisphereSample(Random::nextFloat(), Random::nextFloat());
        if (wo.z < 0)
            wi->z = -(wi->z);
        *pdf = getPdf(wo, *wi);
        return (*this)(wo, *wi);
    }
} // namespace TK
