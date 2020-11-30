#pragma once

struct CameraFrustum
{
	float verticalFieldOfViewInDegrees = .0f;
	float aspectRatio = .0f;
	float nearClipPlane = .0f;
	float farClipPlane = .0f;
};
