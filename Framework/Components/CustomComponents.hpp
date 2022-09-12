#pragma once

namespace gx{
  template<typename... Props>
  struct ComponentStyle : Props...{
    ComponentStyle(){}
  };

  template<typename Function, typename... Props>
  struct CustomComponent{
    Function render;

    CustomComponent(const Function& render) : render(render) {}

    template<typename... Targs>
    auto operator()(const Targs&... args) const{
      ComponentStyle<Props...> style;
      set_props(style, args...);
      render(style);
    }

    auto operator()() const{
      ComponentStyle<Props...> style;
      render(style);
    }
  };

  template<typename... Props, typename Function>
  auto make_component(const Function& render_function){
    return CustomComponent<Function, Props...>(render_function);
  }
}