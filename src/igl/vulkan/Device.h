/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <lvk/LVK.h>
#include <lvk/Pool.h>
#include <igl/vulkan/Common.h>
#include <igl/vulkan/CommandBuffer.h>
#include <memory>
#include <vector>

namespace lvk {
namespace vulkan {

class VulkanContext;
class VulkanContextConfig;
class VulkanShaderModule;

class Device final : public IDevice {
 public:
  explicit Device(std::unique_ptr<VulkanContext> ctx);

  ICommandBuffer& acquireCommandBuffer() override;

  void submit(const lvk::ICommandBuffer& commandBuffer,
              lvk::QueueType queueType,
              ITexture* present) override;

  Holder<BufferHandle> createBuffer(const BufferDesc& desc, Result* outResult) override;
  Holder<SamplerHandle> createSampler(const SamplerStateDesc& desc, Result* outResult) override;
  std::shared_ptr<ITexture> createTexture(const TextureDesc& desc,
                                          const char* debugName,
                                          Result* outResult) override;

  Holder<ComputePipelineHandle> createComputePipeline(const ComputePipelineDesc& desc,
                                                      Result* outResult) override;
  Holder<RenderPipelineHandle> createRenderPipeline(const RenderPipelineDesc& desc,
                                                    Result* outResult) override;
  Holder<ShaderModuleHandle> createShaderModule(const ShaderModuleDesc& desc,
                                                Result* outResult) override;

  void destroy(ComputePipelineHandle handle) override;
  void destroy(RenderPipelineHandle handle) override;
  void destroy(ShaderModuleHandle handle) override;
  void destroy(SamplerHandle handle) override;
  void destroy(BufferHandle handle) override;

  uint32_t gpuId(SamplerHandle handle) const override;
  Result upload(BufferHandle handle, const void* data, size_t size, size_t offset = 0) override;
  uint8_t* getMappedPtr(BufferHandle handle) const override;
  uint64_t gpuAddress(BufferHandle handle, size_t offset = 0) const override;

  std::shared_ptr<ITexture> getCurrentSwapchainTexture() override;

  VulkanContext& getVulkanContext() {
    return *ctx_.get();
  }
  const VulkanContext& getVulkanContext() const {
    return *ctx_.get();
  }

  static std::unique_ptr<VulkanContext> createContext(const VulkanContextConfig& config,
                                                      void* window,
                                                      void* display = nullptr);

  static std::vector<HWDeviceDesc> queryDevices(VulkanContext& ctx,
                                                HWDeviceType deviceType,
                                                Result* outResult = nullptr);

  static std::unique_ptr<IDevice> create(std::unique_ptr<VulkanContext> ctx,
                                         const HWDeviceDesc& desc,
                                         uint32_t width,
                                         uint32_t height,
                                         Result* outResult = nullptr);

 private:
  friend class ComputePipelineState;
  friend class RenderPipelineState;

  VulkanShaderModule createShaderModule(const void* data,
                                        size_t length,
                                        const char* entryPoint,
                                        const char* debugName,
                                        Result* outResult) const;
  VulkanShaderModule createShaderModule(ShaderStage stage,
                                        const char* source,
                                        const char* entryPoint,
                                        const char* debugName,
                                        Result* outResult) const;

  std::unique_ptr<VulkanContext> ctx_;

  lvk::vulkan::CommandBuffer currentCommandBuffer_;
};

} // namespace vulkan
} // namespace lvk
