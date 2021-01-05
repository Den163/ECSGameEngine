#pragma once
#include "BaseSystem.h"
#include "Components/GlWidgetInfo.h"

class CameraAspectRatioSystem : public BaseSystem
{
public:
	void update(entt::registry& registry) override
	{
		auto glView = registry.view<ScreenSettings>();
		auto cameraView = registry.view<CameraFrustum>();
		
		for (auto glEntity : glView)
		{
			auto& screenSettings = glView.get<ScreenSettings>(glEntity);
			const auto aspectRatio = screenSettings.width / screenSettings.height;

			for (auto cameraEntity : cameraView)
			{
				auto& cameraFrustum = cameraView.get<CameraFrustum>(cameraEntity);
				cameraFrustum.aspectRatio = aspectRatio;
			}
		}
	}
};
