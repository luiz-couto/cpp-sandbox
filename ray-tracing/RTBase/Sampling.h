#pragma once

#include "Core.h"
#include <random>
#include <algorithm>

class Sampler
{
public:
	virtual float next() = 0;
};

class MTRandom : public Sampler
{
public:
	std::mt19937 generator;
	std::uniform_real_distribution<float> dist;
	MTRandom(unsigned int seed = 1) : dist(0.0f, 1.0f)
	{
		generator.seed(seed);
	}
	float next()
	{
		return dist(generator);
	}
};

// Note all of these distributions assume z-up coordinate system
class SamplingDistributions
{
public:
	static Vec3 uniformSampleHemisphere(float r1, float r2) {
		float theta = acosf(r1);
		float phi = 2 * M_PI * r2;
		return SphericalCoordinates::sphericalToWorld(theta, phi);
	}

	static float uniformHemispherePDF(const Vec3 wi) {
		return 1.0f / 2 * M_PI;
	}

	static Vec3 cosineSampleHemisphereByDisk(float r1, float r2) {
		float r = sqrtf(r1);
		float theta = 2 * M_PI * r2;
		float x = r * cosf(theta);
		float y = r * sinf(theta);
		float z = sqrtf(1 - (x * x) - (y * y));
		return Vec3(x, y, z);
	}

	static Vec3 cosineSampleHemisphere(float r1, float r2) {
		// Implement uniform sample disk to calculate this!

		float theta = acosf(sqrtf(r1));
		float phi = 2 * M_PI * r2;
		return SphericalCoordinates::sphericalToWorld(theta, phi);
	}

	static float cosineHemispherePDF(const Vec3 wi) {
		// cos theta is the same as the z coordinate of wi
		return wi.z / M_PI;
	}

	static Vec3 uniformSampleSphere(float r1, float r2) {
		float theta = acosf(1 - (2 * r1));
		float phi = 2 * M_PI * r2;
		return SphericalCoordinates::sphericalToWorld(theta, phi);
	}

	static float uniformSpherePDF(const Vec3& wi) {
		return 1.0f / 4 * M_PI;
	}
};

// Sampling code for triangles