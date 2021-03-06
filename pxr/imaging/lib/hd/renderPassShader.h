//
// Copyright 2016 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#ifndef HD_RENDER_PASS_SHADER_H
#define HD_RENDER_PASS_SHADER_H

#include "pxr/pxr.h"
#include "pxr/imaging/hd/api.h"
#include "pxr/imaging/hd/version.h"
#include "pxr/imaging/hd/enums.h"
#include "pxr/imaging/hd/binding.h"
#include "pxr/imaging/hd/resourceBinder.h"
#include "pxr/imaging/hd/shaderCode.h"
#include "pxr/imaging/glf/glslfx.h"

#include "pxr/base/tf/declarePtrs.h"
#include "pxr/base/tf/token.h"

#include <boost/shared_ptr.hpp>

PXR_NAMESPACE_OPEN_SCOPE


typedef boost::shared_ptr<class HdRenderPassShader> HdRenderPassShaderSharedPtr;

/// \class HdRenderPassShader
///
/// A shader that supports common renderPass functionality.
///
class HdRenderPassShader : public HdShaderCode {
public:
    HD_API
    HdRenderPassShader();
    HD_API
    HdRenderPassShader(TfToken const &glslfxFile);
    HD_API
    virtual ~HdRenderPassShader() override;

    /// HdShader overrides
    HD_API
    virtual ID ComputeHash() const override;
    HD_API
    virtual std::string GetSource(TfToken const &shaderStageKey) const override;
    HD_API
    virtual void BindResources(Hd_ResourceBinder const &binder, int program) override;
    HD_API
    virtual void UnbindResources(Hd_ResourceBinder const &binder, int program) override;
    HD_API
    virtual void AddBindings(HdBindingRequestVector *customBindings) override;

    /// Add a custom binding request for use when this shader executes.
    HD_API
    void AddBufferBinding(HdBindingRequest const& req);

    /// Remove \p name from custom binding.
    HD_API
    void RemoveBufferBinding(TfToken const &name);

    /// Clear all custom bindings associated with this shader.
    HD_API
    void ClearBufferBindings();

    HdCullStyle GetCullStyle() const {
        return _cullStyle;
    }

    void SetCullStyle(HdCullStyle cullStyle) {
        _cullStyle = cullStyle;
    }

private:
    TfToken _glslfxFile;
    boost::scoped_ptr<GlfGLSLFX> _glslfx;
    mutable size_t  _hash;
    mutable bool    _hashValid;

    TfHashMap<TfToken, HdBindingRequest, TfToken::HashFunctor> _customBuffers;
    HdCullStyle _cullStyle;


    // No copying
    HdRenderPassShader(const HdRenderPassShader &)                     = delete;
    HdRenderPassShader &operator =(const HdRenderPassShader &)         = delete;
};


PXR_NAMESPACE_CLOSE_SCOPE

#endif // HD_RENDER_PASS_SHADER_H
