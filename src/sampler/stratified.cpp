#include "stratified.hpp"

#include "math/math.hpp"
#include "core/random.hpp"

namespace TK {
    StratifiedSampler::StratifiedSampler(tkUInt xCount, tkUInt yCount, tkUInt dimensions)
        : Sampler(xCount * yCount), xCount(xCount), yCount(yCount) {
        // Pre-initialize samples with a max dimension count
        for (tkUInt i = 0; i < dimensions; ++i) {
            Sampler::requestFloats(1);
            Sampler::requestVectors(1);
        }
    }

    void generateFloatSamples(tkFloat *samples, tkUInt count) {
        tkFloat invCount = (tkFloat)1 / count;
        for (tkUInt i = 0; i < count; ++i) {
            samples[i] = (i + Random::nextFloat()) * invCount;
        }
    }

    void generateVectorSamples(tkVec2f *samples, tkUInt xCount, tkUInt yCount) {
        tkFloat invX = (tkFloat)1 / xCount;
        tkFloat invY = (tkFloat)1 / yCount;
        tkVec2f *currSample = samples;
        for (tkUInt y = 0; y < yCount; ++y) {
            for (tkUInt x = 0; x < xCount; ++x) {
                currSample->x = (x + Random::nextFloat()) * invX;
                currSample->y = (y + Random::nextFloat()) * invY;
                currSample++;
            }
        }
    }

    template <typename T>
    void randomizeSamples(T *samples, tkUInt count) {
        for (tkUInt i = 0; i < count; ++i) {
            // Sanity check to ensure o never goes out of bounds for whatever reason
            tkUInt o = std::min(count - 1, i + static_cast<tkUInt>(Random::nextFloat() * (count - i)));
            std::swap(samples[i], samples[o]);
        }
    }

    void StratifiedSampler::setPixel(const tkPoint2i &pixelCoord) {
        // Set up float set
        for (auto &f : floatSet) {
            generateFloatSamples(f.data(), samplesPerPixel);
            randomizeSamples(f.data(), samplesPerPixel);
        }
        // Set up vector set
        for (auto &v : vectorSet) {
            generateVectorSamples(v.data(), xCount, yCount);
            randomizeSamples(v.data(), xCount * yCount);
        }
        Sampler::setPixel(pixelCoord);
    }

    tkFloat StratifiedSampler::nextFloat() {
        if (currentFloatSet < floatSet.size()) {
            return floatSet[currentFloatSet++][currentSample];
        } else {
            return Random::nextFloat();
        }
    }

    tkVec2f StratifiedSampler::nextVector() {
        if (currentVectorSet < vectorSet.size()) {
            return vectorSet[currentVectorSet++][currentSample];
        } else {
            return tkVec2f(Random::nextFloat(), Random::nextFloat());
        }
    }

    std::unique_ptr<Sampler> StratifiedSampler::getClone() {
        return std::make_unique<StratifiedSampler>(*this);
    }
}  // namespace TK
