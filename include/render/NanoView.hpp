#ifndef BLIB_NANOVIEW_HPP
#define BLIB_NANOVIEW_HPP

#include "View.hpp"
#include "sdl.hpp"
#include "Nanovg.hpp"
#include "RenderNode.hpp"
#include <boost/variant.hpp>

namespace blib {
  namespace render {
    namespace nanovg {
      // View tag, this will be used to specialize the traits.
      // This is inorder used in the view class
      struct NanoViewTag {};


    }

    namespace traits {
      template<>
      struct render_type < blib::render::nanovg::NanoViewTag > {
        typedef ::blib::render::nanovg::NanoVG type;
      };

      template<>
      struct scene_manager < blib::render::nanovg::NanoViewTag > {

      };

      template<>
      struct display_type < blib::render::nanovg::NanoViewTag > {};

      template<>
      struct display_value_type < blib::render::nanovg::NanoViewTag > {};

      template<>
      struct render_element_type < blib::render::nanovg::NanoViewTag > {};

      template<>
      struct event_type < blib::render::nanovg::NanoViewTag > {};
    } // namespace traits
  }
}

#endif // BLIB_NANOVIEW_HPP
