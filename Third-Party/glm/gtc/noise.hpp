/// @ref gtc_noise
/// @file glm/gtc/noise.hpp
///
/// @see core (dependence)
///
/// @defgroup gtc_noise GLM_GTC_noise
/// @ingroup gtc
///
/// Include <glm/gtc/noise.hpp> to use the features of this extension.
///
/// Defines 2D, 3D and 4D procedural noise functions
/// Based on the work of Stefan Gustavson and Ashima Arts on "webgl-noise":
/// https://github.com/ashima/webgl-noise
/// Following Stefan Gustavson's paper "Simplex noise demystified":
/// http://www.itn.liu.se/~stegu/simplexnoise/simplexnoise.pdf

#pragma once

// Dependencies
#include "Third-Party/glm/detail/setup.hpp"
#include "Third-Party/glm/detail/qualifier.hpp"
#include "Third-Party/glm/detail/_noise.hpp"
#include "Third-Party/glm/geometric.hpp"
#include "Third-Party/glm/common.hpp"
#include "Third-Party/glm/vector_relational.hpp"
#include "Third-Party/glm/vec2.hpp"
#include "Third-Party/glm/vec3.hpp"
#include "Third-Party/glm/vec4.hpp"

#if GLM_MESSAGES == GLM_ENABLE && !defined(GLM_EXT_INCLUDED)
#	pragma message("GLM: GLM_GTC_noise extension included")
#endif

namespace glm
{
	/// @addtogroup gtc_noise
	/// @{

	/// Classic perlin noise.
	/// @see gtc_noise
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL T perlin(
		vec<L, T, Q> const& p);

	/// Periodic perlin noise.
	/// @see gtc_noise
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL T perlin(
		vec<L, T, Q> const& p,
		vec<L, T, Q> const& rep);

	/// Simplex noise.
	/// @see gtc_noise
	template<length_t L, typename T, qualifier Q>
	GLM_FUNC_DECL T simplex(
		vec<L, T, Q> const& p);

	/// @}
}//namespace glm

#include "noise.inl"
