# **Gacrux**
OpenGL-based 2D rendering framework

## **Installation And Building**
**Tools needed:**<br>
* C++17 Compiler
* CMake
* Make (or other build system)

**Clone repository**<br>
First, You have to clone this repository to Your local computer. Use this command to download framework with all needed dependencies:
```
git clone --recurse-submodule https://github.com/GeFeC/gacrux.git
```

**CMake**<br>
Open the downloaded file, create new folder in it, for example: `build` and use this CMake command in this folder to generate build system files:
```
cmake ..
```
If it doesn't work don't worry. You just need to specify the generator with `-G` flag. For example: If You use Make as Your build system, this generator is probably "MinGW Makefiles" or "Unix Makefiles". Here is how to build the project with the generator specified:
```
cmake .. -G "MinGW Makefiles"
```

**Building**<br>
Now the only thing You have to do is to build the entire project:
```
cmake --build .
```
And You're done! Your project should be built!

## **Examples**
### **Simple square**:
`Frames/app.hpp:`
```cpp
#pragma once

#include <../Framework/Components/Render.hpp>
#include <../Framework/Frames/Frame.hpp>

auto app = gx::make_frame([]{
  using namespace gx::render;

  gx::component++(
    gx::Size{{ 100, 100 }},
    gx::Position{{ 350, 250 }},
    gx::colors::Green
  );
});
```
Components are put inside Frames. When You download the framework, the default project has 'app' provided as the default Frame so You have to create it. A Frame is something like a Scene (For Example: one Frame can be game's main menu, and the other can be some level in game). Every Frame has its own set of resources that are automatically allocated before drawing components in that Frame, and destroyed after the rendering.

### **Rotated Square**:
`Frames/app.hpp:`
```cpp
#pragma once

#include <../Framework/Components/Render.hpp>
#include <../Framework/Frames/Frame.hpp>

auto app = gx::make_frame([]{
  using namespace gx::render;

  gx::rotatable++( //NOTE: rotatable instead of component here!
    gx::Size{{ 100, 100 }},
    gx::Position{{ 400, 300 }},
    gx::colors::Red,
    gx::Rotation{ 45.f },
    gx::RotationOffset{{ -50.f, -50.f }}
  );
});
```
As You can see, we're using `rotatable` instead of `component` here. Rotating an object requires doing additional matrix multiplications which means it take a little more time to render an object that can rotate. `component` is rendered faster than `rotatable`. Choose `component` when You're sure an object isn't going to be rotated, and `rotatable` otherwise.
### **Text Rendering**:
`Frames/app.hpp:`
```cpp
#pragma once

#include "res/fonts.hpp"

#include <../Framework/Components/Render.hpp>
#include <../Framework/Frames/Frame.hpp>

auto app_res = gx::Resources(
  gx::FontList{
    //font object and font size
    std::make_pair(&gx::fonts::consolas, 70)
  },
  gx::TextureList{}
);

auto app = gx::make_frame([]{
  using namespace gx::render;

  gx::text++(
    gx::FontFamily{ &gx::fonts::consolas },
    gx::Label{ "Hello World!" },
    gx::colors::White
  );
}, app_res); //NOTE: app_res added here!
```
`text` must have some font, and we have to specify it. But to use a font, first it must be allocated (loaded). We can create an array of fonts and their corresponding sizes, and provide it to our 'app' Frame, so the Frame will manage fonts' allocation and deallocation for us.

### **Custom Component**:
`Frames/app.hpp:`
```cpp
#pragma once

#include <../Framework/Component/Render.hpp>
#include <../Framework/Frames/Frame.hpp>

const auto app_res = gx::Resources(
  gx::FontList{
    { &gx::fonts::consolas, 40 }
  },
  gx::TextureList{}
);

//Custom property
struct BorderColor{
  glm::vec4 border_color;
};

//Custom component
const auto border = [](const auto& props){
  using namespace gx::render;

  //optional property
  const auto position = gx::expect<gx::Position>(props).position;

  gx::component++(
    gx::Position{ position },
    gx::Size{ props.size },
    gx::Color{ props.border_color }
  );

  static constexpr auto BorderSize = 5;

  gx::component++(
    gx::Position{ position + gx::Vec2(BorderSize) },
    gx::Size{ props.size - gx::Vec2(BorderSize * 2) },
    gx::colors::Black
  );
};

const auto app = gx::make_frame([](const auto& state){
  using namespace gx::render;

  border++(
    gx::Size{{ 230, 70 }},
    BorderColor{ gx::colors::Aqua.color }
  );
}, app_res);
```
## License
Gacrux framework is MIT licensed
