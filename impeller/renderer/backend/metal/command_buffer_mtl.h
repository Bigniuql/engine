// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <Metal/Metal.h>

#include "flutter/fml/macros.h"
#include "impeller/core/allocator.h"
#include "impeller/renderer/command_buffer.h"

namespace impeller {

class CommandBufferMTL final : public CommandBuffer {
 public:
  // |CommandBuffer|
  ~CommandBufferMTL() override;

 private:
  friend class ContextMTL;

  id<MTLCommandBuffer> buffer_ = nullptr;

  CommandBufferMTL(const std::weak_ptr<const Context>& context,
                   id<MTLCommandQueue> queue);

  // |CommandBuffer|
  void SetLabel(const std::string& label) const override;

  // |CommandBuffer|
  bool IsValid() const override;

  // |CommandBuffer|
  bool OnSubmitCommands(CompletionCallback callback) override;

  // |CommandBuffer|
  void OnWaitUntilScheduled() override;

  // |CommandBuffer|
  bool EncodeAndSubmit(const std::shared_ptr<RenderPass>& render_pass) override;

  // |CommandBuffer|
  bool EncodeAndSubmit(const std::shared_ptr<BlitPass>& blit_ass,
                       const std::shared_ptr<Allocator>& allocator) override;

  // |CommandBuffer|
  std::shared_ptr<RenderPass> OnCreateRenderPass(RenderTarget target) override;

  // |CommandBuffer|
  std::shared_ptr<BlitPass> OnCreateBlitPass() override;

  // |CommandBuffer|
  std::shared_ptr<ComputePass> OnCreateComputePass() override;

  CommandBufferMTL(const CommandBufferMTL&) = delete;

  CommandBufferMTL& operator=(const CommandBufferMTL&) = delete;
};

}  // namespace impeller
