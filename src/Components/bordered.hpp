#pragma once

#include "../Framework/Components/Render.hpp"

const auto bordered_square = [](const auto& props){
  gx::component++(
    gx::Size{{ 50, 50 }},
    gx::Position{props.position},
    gx::Color{ glm::vec4(1) }
  );

  gx::component++(
    gx::Size{{ 40, 40 }},
    gx::Position{props.position + gx::Vec2(5, 5)},
    gx::Color{ glm::vec4(0, 0, 0, 1) }
  );
};
