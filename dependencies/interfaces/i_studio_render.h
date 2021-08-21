#pragma once
#include "i_material_system.hpp"
#include <cstddef>
#include <string_view>

enum class override_type {
    normal = 0,
    build_shadows,
    depth_write,
    custom_material, // weapon skins
    ssao_depth_write
};

class iv_studio_render {
    std::byte pad_0[0x250];
    std::byte pad_1[0xC];
    override_type override_type;
    i_material* material_override;
public:
    bool is_forced() noexcept {

       // return override_type == override_type::depth_write || override_type == override_type::ssao_depth_write;
        return 0;
    }
};