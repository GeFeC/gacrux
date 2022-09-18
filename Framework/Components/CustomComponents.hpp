#pragma once

namespace gx{
  template<typename... Props>
  struct ComponentStyle : Props...{
    ComponentStyle(){}

    template<typename... ExtraProps>
    using with = ComponentStyle<Props..., ExtraProps...>;
  };

  template<typename Function>
  struct CustomComponent{
    Function render;

    CustomComponent(const Function& render) : render(render) {}

    template<typename... Props>
    auto operator()(const Props&... args) const{
      ComponentStyle<Props...> style;
      set_props(style, args...);
      render(style);
    }

    auto operator()() const{
      ComponentStyle<> style;
      render(style);
    }
  };

  template<typename Function>
  auto make_component(const Function& render_function){
    return CustomComponent<Function>(render_function);
  }
}