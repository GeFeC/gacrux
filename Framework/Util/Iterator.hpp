#pragma once

#include "../aliases.hpp"

namespace gx{
  struct Range{
    i32 min, max;

    struct iterator{
      i32 value{};

      constexpr auto operator==(const iterator& other) const{
        return value == other.value;
      }

      constexpr auto operator!=(const iterator& other) const{
        return value != other.value;
      }

      constexpr auto operator++(){
        ++value;
      }

      constexpr auto operator*(){
        return value;
      }
    };

    constexpr auto begin() const{
      return iterator{ min };
    }

    constexpr auto end() const{
      return iterator{ max };
    }
  };

  constexpr auto range(i32 min, i32 max){
    return Range{ min, max };
  }

  constexpr auto range(i32 max){
    return Range{ 0, max };
  }

  template<typename Range>
  struct Index{
    Range* range_ptr;

    struct iterator{
      typename Range::iterator range_iter;
      i32 index{};

      constexpr auto operator==(const iterator& other) const{
        return index == other.index && range_iter == other.range_iter;
      }

      constexpr auto operator!=(const iterator& other) const{
        return index != other.index || range_iter != other.range_iter;
      }

      constexpr auto operator++(){
        ++range_iter;
        ++index;
      }

      constexpr auto operator*(){
        return std::make_pair(std::ref(*range_iter), index);
      }
    };

    constexpr auto begin(){
      return iterator{ range_ptr->begin(), 0 };
    }

    constexpr auto end(){
      return iterator{ range_ptr->end(), range_ptr->size() };
    }
  };

  template<typename T>
  auto make_index(T& range){
    return Index<T>{ &range };
  }
}

namespace gx::literals{
  constexpr auto operator""_gx(unsigned long long value){
    return range(value);
  }
}