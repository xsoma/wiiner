#pragma once

namespace math {
	void angle_vectors_alternative(const vec3_t& angles, vec3_t* forward);
	void correct_movement(vec3_t old_angles, c_usercmd* cmd, float old_forwardmove, float old_sidemove);
	vec3_t calculate_angle(const vec3_t& source, const vec3_t& destination, const vec3_t& viewAngles);
	void sin_cos(float r, float* s, float* c);
	vec3_t angle_vector(vec3_t angle);
	void transform_vector(vec3_t&, matrix_t&, vec3_t&);
	void vector_angles(vec3_t&, vec3_t&);
	void angle_vectors(vec3_t&, vec3_t*, vec3_t*, vec3_t*);
	vec3_t vector_add(vec3_t&, vec3_t&);
	float get_fov(const vec3_t& view_angle, const vec3_t& aim_angle);
	vec3_t vector_subtract(vec3_t&, vec3_t&);
	vec3_t vector_multiply(vec3_t&, vec3_t&);
	vec3_t vector_divide(vec3_t&, vec3_t&);
	bool screen_transform(const vec3_t& point, vec3_t& screen);
	vec3_t normalize(vec3_t angle);
	bool world_to_screen(const vec3_t& origin, vec2_t& screen);
	void angle_vectors2(const vec3_t& angles, vec3_t& forward);
	template<class T>
	void normalize3(T& vec)
	{
		for (auto i = 0; i < 2; i++) {
			while (vec[i] < -180.0f) vec[i] += 360.0f;
			while (vec[i] > 180.0f) vec[i] -= 360.0f;
		}
		vec[2] = 0.f;
	}
};
