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
`Views/app.hpp:`
```cpp
#include <../Framework/Components/Components.hpp>
#include <../Framework/Components/Props.hpp>
#include <../Framework/Views/View.hpp>

auto app = gx::make_view([]{
  gx::component(
    gx::Size(100, 100),
    gx::Position(350, 250),
    gx::Color(0, 1, 0, 1) //green
  );
});
```
Components are put inside Views. When You download the framework, the default project has 'app' provided as the default View so You have to create it. A View is something like a Scene (For Example: one View can be game's main menu, and the other can be some level in game). Every View has its own set of resources that are automatically allocated before drawing components in that View, and destroyed after the rendering.

### **Rotated Square**:
`Views/app.hpp:`
```cpp
#pragma once

#include <../Framework/Components/Components.hpp>
#include <../Framework/Components/Props.hpp>
#include <../Framework/Views/View.hpp>

auto app = gx::make_view([]{
  gx::rotatable( //NOTE: rotatable instead of component here!
    gx::Size(100, 100),
    gx::Position(400, 300),
    gx::Color(1, 0, 0, 1), //red
    gx::Rotation(45.f), //degrees
    gx::RotationOffset(-50, -50)
  );
});
```
As You can see, we're using `rotatable` instead of `component` here. Rotating an object requires doing additional matrix multiplications which means it take a little more time to render an object that can rotate. `component` is rendered faster than `rotatable`. Choose `component` when You're sure an object isn't going to be rotated, and `rotatable` otherwise.
### **Text Rendering**:
`Views/app.hpp:`
```cpp
#pragma once

#include "res/fonts.hpp"

#include <../Framework/Components/Components.hpp>
#include <../Framework/Components/Props.hpp>
#include <../Framework/Views/View.hpp>

auto app_fonts = gx::FontList{
  std::make_pair(&gx::fonts::consolas, 70)
};

auto app = gx::make_view([]{
  gx::text(
    "Hello World!",
    gx::FontFamily(gx::fonts::consolas),
    gx::Position(190, 250)
  );
}, app_fonts); //NOTE: app_fonts added here!
```
`text` must have some font, and we have to specify it. But to use a font, first it must be allocated (loaded). We can create an array of fonts and their corresponding sizes, and provide it to our 'app' View, so the View will manage fonts' allocation and deallocation for us.

### **Custom Component**:
`Components/button.hpp:`
```cpp
#pragma once

#include <../Framework/Components/Components.hpp>
#include <../Framework/Components/Props.hpp>
#include <../Framework/Components/CustomComponents.hpp>

#include "res/fonts.hpp"

const auto label = gx::make_component<gx::Label, gx::Position, gx::Size>([](const auto& props){
  const auto& [x, y] = props.position;
  const auto& [w, h] = props.size;

  gx::component(
    gx::Position(x, y),
    gx::Size(w, h),
    gx::Color(1, 1, 1, 1)
  );

  static constexpr auto BorderSize = 5;

  gx::component(
    gx::Position(x + BorderSize, y + BorderSize),
    gx::Size(w - 2 * BorderSize, h - 2 * BorderSize),
    gx::Color(0, 0, 0, 1)
  );

  gx::text(
    props.label,
    gx::Position(props.position.x, props.position.y),
    gx::Color(1, 1, 1, 1) //white
  );
});
```
`Views/app.hpp:`
```cpp
#pragma once

#include "Components/button.hpp"
#include "res/fonts.hpp"

#include <../Framework/Views/View.hpp>

auto app_fonts = gx::FontList{
  std::make_pair(&gx::fonts::consolas, 70)
};

auto app = gx::make_view([]{
  button(
    gx::Label("Hello World!"),
    gx::Position(190, 250)
  );
}, app_fonts); //NOTE: app_fonts added here!
```
## License
Gacrux framework is MIT licensed