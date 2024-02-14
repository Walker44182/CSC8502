#include "../nclgl/window.h"
#include "Renderer.h"
int main() {
	Window w("Coursework!", 1280, 720, false);
	if (!w.HasInitialised()) {
		return -1;
	}

	Renderer renderer(w);
	if (!renderer.HasInitialised()) {
		return -1;
	}

	w.LockMouseToWindow(true);
	w.ShowOSPointer(false);

	int i = 0, j = 0;
	Vector3 position(0, 700, 0);
	Vector4 Colour1(0, 1, 0, 1);
	Vector4 Colours1[3] = { Vector4(0,1,0,1), Vector4(1,0,0,1),Vector4(0,0,1,1) };
	Vector4 Colour2(1, 1, 1, 1);
	Vector4 Colours2[3] = { Vector4(1,1,1,1), Vector4(1,0.82f,0.88f,1),Vector4(1,0.55f,0,1) };
	float r = 0.0f;
	string message;

	while (w.UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_P))
			position.y -= 3.0f;
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_O))
			position.y += 3.0f;
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_I))
			position.x -= 7.0f;
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_K))
			position.x += 7.0f;
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_L))
			position.z -= 7.0f;
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_J))
			position.z += 7.0f;
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_LEFT))
			--r;
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_RIGHT))
			++r;
		if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_C)) {
			++i;
			Colour1 = Colours1[i % 3];
		}
		if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_V)) {
			++j;
			Colour2 = Colours2[j % 3];
		}

		if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_1)) {
			renderer.SwitchShadow();
		}
		if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_2)) {
			renderer.SwitchSunlight();
		}
		if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_3)) {
			renderer.SwitchSpecularMap();
		}
		if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_4)) {
			renderer.SwitchCorrection();
		}
		if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_5)) {
			renderer.SwitchBlur();
		}
		if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_6)) {
			renderer.EscapeProcess();
		}
		if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_7)) {
			renderer.SwitchFrustum();
		}

		if (Window::GetKeyboard()->KeyDown(KEYBOARD_PLUS)) {
			renderer.SetExposure(renderer.GetExposure() + 0.005);
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_MINUS)) {
			renderer.SetExposure(renderer.GetExposure() - 0.005);
		}

		if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_F)) {
			renderer.SwitchMovingCamera();
		}
		if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_G)) {
			renderer.SwitchTerrainCamera();
		}
		if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_H)) {
			renderer.SwitchSpaceCamera();
		}

		if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_F1)) {
			renderer.SwitchSnow();
		}
		if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_F2)) {
			renderer.SwitchBlocks();
		}
		if (Window::GetKeyboard()->KeyTriggered(KEYBOARD_F3)) {
			renderer.SwitchMiniMap();
		}
	

		renderer.SetUFOPosition(position, r);
		renderer.SetUFOLightColour(Colour1);
		renderer.SetUFOColour(Colour2);
		float timestep = w.GetTimer()->GetTimeDeltaSeconds();
		renderer.UpdateScene(timestep);
		renderer.RenderScene();
		renderer.SwapBuffers();
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_F5)) {
			Shader::ReloadAllShaders();
		}
	}
	return 0;
}