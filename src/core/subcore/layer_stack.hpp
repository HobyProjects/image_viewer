#pragma once

#include "layer.hpp"

namespace IMGV::Core
{
    class LayerStack
    {
        public:
            LayerStack() = default;
            ~LayerStack();

            void PushLayer(Reference<Layer> layer);
            void PushOverlay(Reference<Layer> overlay);
            void PopLayer(Reference<Layer> layer);
            void PopOverlay(Reference<Layer> overlay);

            std::vector<Reference<Layer>>::iterator begin() { return m_Layers.begin(); }
            std::vector<Reference<Layer>>::iterator end() { return m_Layers.end(); }
            std::vector<Reference<Layer>>::const_iterator begin() const { return m_Layers.begin(); }
            std::vector<Reference<Layer>>::const_iterator end() const { return m_Layers.end(); }
            std::vector<Reference<Layer>>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
            std::vector<Reference<Layer>>::reverse_iterator rend() { return m_Layers.rend(); }
            std::vector<Reference<Layer>>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
            std::vector<Reference<Layer>>::const_reverse_iterator rend() const { return m_Layers.rend(); }

        private:
            std::vector<Reference<Layer>> m_Layers;
            UInt32 m_LayerInsertIndex{IMGV_NULL};
    };  
}