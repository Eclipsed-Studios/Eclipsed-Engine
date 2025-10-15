#include "TextRenderer.h"

#include "RenderCommands/CommandList.h"

#include "AssetManagement/Resources/Shaders/Shader.h"
#include "TextSprite.h"
#include "OpenGL/OpenGLGraphicsAPI.h"

#include "TextManager.h"

namespace Eclipse
{
	TextMaterial::TextMaterial()
	{
		myShader = new Shader();
		myShader->Create("Assets/Shaders/TextPixelShader.glsl", "Assets/Shaders/TextVertexShader.glsl");

		int yes = 1;
		GraphicsEngine::SetUniform(UniformType::Int, myShader->GetProgramID(), "TextTexture", &yes);
	}

	void TextMaterial::Use(unsigned textureID)
	{
		glActiveTexture(GL_TEXTURE0);
		GraphicsEngine::BindTexture(GL_TEXTURE_2D, textureID);
	}

	void TextRenderer::EditorUpdate()
	{
		// TODO: should be called form Comp manager
		OnDrawGizmos();

		if (myLastFontSize != myFontSize)
		{
			SetFontSize(myFontSize);
			myLastFontSize = myFontSize;
		}

	}

	void TextRenderer::OnComponentAdded()
	{
		OnSceneLoaded();
	}

	void TextRenderer::OnSceneLoaded()
	{
		if (!myCreatedRenderer)
		{
			myMaterial = new TextMaterial();
			myFont = &TextManager::Get().GetFont(myFontPath->c_str(), myFontSize);

			myCreatedRenderer = true;

			int lastFontSize = myFontSize;
		}
	}

	void TextRenderer::DrawInspector()
	{
		ImGui::PushID(myInstanceComponentID);

		ImGui::Text("Text Color");
		ImGui::SameLine();
		if (ImGui::ColorButton("##TextColorpickerButton", ImVec4(myTextColor->r, myTextColor->g, myTextColor->b, myTextColor->a)))
			ImGui::OpenPopup("TextColorPickerPopup");

		if (ImGui::BeginPopup("TextColorPickerPopup"))
		{
			ImGui::ColorPicker4("##TextColorPicker", myTextColor->data);
			ImGui::EndPopup();
		}


		ImColor defaultcolor = ImGui::GetColorU32(ImGuiCol_Button, 1.f);

		ImColor onColor;
		onColor.Value.x = defaultcolor.Value.x * 0.7f;
		onColor.Value.y = defaultcolor.Value.y * 0.7f;
		onColor.Value.z = defaultcolor.Value.z * 0.7f;
		onColor.Value.w = 1.f;

		ImColor offColor;
		offColor.Value.x = defaultcolor.Value.x * 1.5f;
		offColor.Value.y = defaultcolor.Value.y * 1.5f;
		offColor.Value.z = defaultcolor.Value.z * 1.5f;
		offColor.Value.w = 1.f;

		DrawMultilineInspector();
		DrawAlignmentInspector(onColor, offColor);
		DrawCenteringInspector(onColor, offColor);

		ImGui::PopID();
	}

	void TextRenderer::DrawMultilineInspector()
	{
		char textComponentText[2048];

		strcpy(textComponentText, myText->data());

		ImGui::Text("Text");
		if (ImGui::InputTextMultiline("##TextComponentText", textComponentText, 2048, ImVec2(0, 0)))
			myText = textComponentText;
	}

	void TextRenderer::DrawAlignmentInspector(const ImColor& onColor, const ImColor& offColor)
	{
		ImColor color;

		if (myTextAlignment == 0)
			color = onColor;
		else
			color = offColor;

		ImVec2 leftCursorStart = ImGui::GetCursorScreenPos();
		ImGui::PushStyleColor(ImGuiCol_Button, color.Value);
		if (ImGui::Button("##ButtonForUseWithAlightLeft", ImVec2(40, 25)))
			myTextAlignment = 0;
		ImGui::PopStyleColor();

		ImVec2 leftCursorStart1 = ImVec2(leftCursorStart.x + 5.f, leftCursorStart.y + 5.f);
		ImVec2 leftCursorEnd1 = ImVec2(leftCursorStart.x + 30.f, leftCursorStart.y + 5.f);
		ImGui::GetWindowDrawList()->AddLine(leftCursorStart1, leftCursorEnd1, IM_COL32(200, 200, 200, 255));

		ImVec2 leftCursorStart2 = ImVec2(leftCursorStart.x + 5.f, leftCursorStart.y + 10.f);
		ImVec2 leftCursorEnd2 = ImVec2(leftCursorStart.x + 24.f, leftCursorStart.y + 10.f);
		ImGui::GetWindowDrawList()->AddLine(leftCursorStart2, leftCursorEnd2, IM_COL32(200, 200, 200, 255));

		ImVec2 leftCursorStart3 = ImVec2(leftCursorStart.x + 5.f, leftCursorStart.y + 15.f);
		ImVec2 leftCursorEnd3 = ImVec2(leftCursorStart.x + 27.f, leftCursorStart.y + 15.f);
		ImGui::GetWindowDrawList()->AddLine(leftCursorStart3, leftCursorEnd3, IM_COL32(200, 200, 200, 255));

		ImVec2 leftCursorStart4 = ImVec2(leftCursorStart.x + 5.f, leftCursorStart.y + 20.f);
		ImVec2 leftCursorEnd4 = ImVec2(leftCursorStart.x + 22.f, leftCursorStart.y + 20.f);
		ImGui::GetWindowDrawList()->AddLine(leftCursorStart4, leftCursorEnd4, IM_COL32(200, 200, 200, 255));

		ImGui::SameLine();

		if (myTextAlignment == 1)
			color = onColor;
		else
			color = offColor;

		ImVec2 middleCursorStart = ImGui::GetCursorScreenPos();
		ImGui::PushStyleColor(ImGuiCol_Button, color.Value);
		if (ImGui::Button("##ButtonForUseWithAlightMiddle", ImVec2(40, 25)))
			myTextAlignment = 1;
		ImGui::PopStyleColor();

		ImVec2 middleCursorStart1 = ImVec2(middleCursorStart.x + 7.5f, middleCursorStart.y + 5.f);
		ImVec2 middleCursorEnd1 = ImVec2(middleCursorStart.x + 32.5f, middleCursorStart.y + 5.f);
		ImGui::GetWindowDrawList()->AddLine(middleCursorStart1, middleCursorEnd1, IM_COL32(200, 200, 200, 255));

		ImVec2 middleCursorStart2 = ImVec2(middleCursorStart.x + 10.5f, middleCursorStart.y + 10.f);
		ImVec2 middleCursorEnd2 = ImVec2(middleCursorStart.x + 29.5f, middleCursorStart.y + 10.f);
		ImGui::GetWindowDrawList()->AddLine(middleCursorStart2, middleCursorEnd2, IM_COL32(200, 200, 200, 255));

		ImVec2 middleCursorStart3 = ImVec2(middleCursorStart.x + 7.f, middleCursorStart.y + 15.f);
		ImVec2 middleCursorEnd3 = ImVec2(middleCursorStart.x + 33.f, middleCursorStart.y + 15.f);
		ImGui::GetWindowDrawList()->AddLine(middleCursorStart3, middleCursorEnd3, IM_COL32(200, 200, 200, 255));

		ImVec2 middleCursorStart4 = ImVec2(middleCursorStart.x + 11.5f, middleCursorStart.y + 20.f);
		ImVec2 middleCursorEnd4 = ImVec2(middleCursorStart.x + 28.5f, middleCursorStart.y + 20.f);
		ImGui::GetWindowDrawList()->AddLine(middleCursorStart4, middleCursorEnd4, IM_COL32(200, 200, 200, 255));

		ImGui::SameLine();

		if (myTextAlignment == 2)
			color = onColor;
		else
			color = offColor;

		ImVec2 rightCursorStart = ImGui::GetCursorScreenPos();
		ImGui::PushStyleColor(ImGuiCol_Button, color.Value);
		if (ImGui::Button("##ButtonForUseWithAlightRight", ImVec2(40, 25)))
			myTextAlignment = 2;
		ImGui::PopStyleColor();

		ImVec2 rightCursorStart1 = ImVec2(rightCursorStart.x + 10.f, rightCursorStart.y + 5.f);
		ImVec2 rightCursorEnd1 = ImVec2(rightCursorStart.x + 35.f, rightCursorStart.y + 5.f);
		ImGui::GetWindowDrawList()->AddLine(rightCursorStart1, rightCursorEnd1, IM_COL32(200, 200, 200, 255));

		ImVec2 rightCursorStart2 = ImVec2(rightCursorStart.x + 18.f, rightCursorStart.y + 10.f);
		ImVec2 rightCursorEnd2 = ImVec2(rightCursorStart.x + 35.f, rightCursorStart.y + 10.f);
		ImGui::GetWindowDrawList()->AddLine(rightCursorStart2, rightCursorEnd2, IM_COL32(200, 200, 200, 255));

		ImVec2 rightCursorStart3 = ImVec2(rightCursorStart.x + 22.f, rightCursorStart.y + 15.f);
		ImVec2 rightCursorEnd3 = ImVec2(rightCursorStart.x + 35.f, rightCursorStart.y + 15.f);
		ImGui::GetWindowDrawList()->AddLine(rightCursorStart3, rightCursorEnd3, IM_COL32(200, 200, 200, 255));

		ImVec2 rightCursorStart4 = ImVec2(rightCursorStart.x + 19.f, rightCursorStart.y + 20.f);
		ImVec2 rightCursorEnd4 = ImVec2(rightCursorStart.x + 35.f, rightCursorStart.y + 20.f);
		ImGui::GetWindowDrawList()->AddLine(rightCursorStart4, rightCursorEnd4, IM_COL32(200, 200, 200, 255));

		ImGui::SameLine();

		if (myTextAlignment == 3)
			color = onColor;
		else
			color = offColor * 0.5f;

		ImVec2 filledCursorStart = ImGui::GetCursorScreenPos();
		ImGui::PushStyleColor(ImGuiCol_Button, color.Value);
		if (ImGui::Button("##ButtonForUseWithAlightfilled", ImVec2(40, 25)) && false)
			myTextAlignment = 3;
		ImGui::PopStyleColor();

		ImVec2 filledCursorStart1 = ImVec2(filledCursorStart.x + 5.f, filledCursorStart.y + 5.f);
		ImVec2 filledCursorEnd1 = ImVec2(filledCursorStart.x + 35.f, filledCursorStart.y + 5.f);
		ImGui::GetWindowDrawList()->AddLine(filledCursorStart1, filledCursorEnd1, IM_COL32(200, 200, 200, 255));

		ImVec2 filledCursorStart2 = ImVec2(filledCursorStart.x + 5.f, filledCursorStart.y + 10.f);
		ImVec2 filledCursorEnd2 = ImVec2(filledCursorStart.x + 35.f, filledCursorStart.y + 10.f);
		ImGui::GetWindowDrawList()->AddLine(filledCursorStart2, filledCursorEnd2, IM_COL32(200, 200, 200, 255));

		ImVec2 filledCursorStart3 = ImVec2(filledCursorStart.x + 5.f, filledCursorStart.y + 15.f);
		ImVec2 filledCursorEnd3 = ImVec2(filledCursorStart.x + 35.f, filledCursorStart.y + 15.f);
		ImGui::GetWindowDrawList()->AddLine(filledCursorStart3, filledCursorEnd3, IM_COL32(200, 200, 200, 255));

		ImVec2 filledCursorStart4 = ImVec2(filledCursorStart.x + 5.f, filledCursorStart.y + 20.f);
		ImVec2 filledCursorEnd4 = ImVec2(filledCursorStart.x + 35.f, filledCursorStart.y + 20.f);
		ImGui::GetWindowDrawList()->AddLine(filledCursorStart4, filledCursorEnd4, IM_COL32(200, 200, 200, 255));
	}

	void TextRenderer::DrawCenteringInspector(const ImColor& onColor, const ImColor& offColor)
	{
		ImColor color;

		if (myTextCentering == 0)
			color = onColor;
		else
			color = offColor;

		ImVec2 upCursorStart = ImGui::GetCursorScreenPos();
		ImGui::PushStyleColor(ImGuiCol_Button, color.Value);
		if (ImGui::Button("##ButtonForUseWithCenterUp", ImVec2(40, 25)))
			myTextCentering = 0;
		ImGui::PopStyleColor();

		ImVec2 upCursorStart1 = ImVec2(upCursorStart.x + 5.f, upCursorStart.y + 4.f);
		ImVec2 upCursorEnd1 = ImVec2(upCursorStart.x + 35.f, upCursorStart.y + 4.f);
		ImGui::GetWindowDrawList()->AddLine(upCursorStart1, upCursorEnd1, IM_COL32(200, 200, 200, 255));

		ImVec2 upCursorStart2 = ImVec2(upCursorStart.x + 5.f, upCursorStart.y + 8.f);
		ImVec2 upCursorEnd2 = ImVec2(upCursorStart.x + 35.f, upCursorStart.y + 8.f);
		ImGui::GetWindowDrawList()->AddLine(upCursorStart2, upCursorEnd2, IM_COL32(200, 200, 200, 255));

		ImVec2 upCursorStart3 = ImVec2(upCursorStart.x + 5.f, upCursorStart.y + 12.f);
		ImVec2 upCursorEnd3 = ImVec2(upCursorStart.x + 35.f, upCursorStart.y + 12.f);
		ImGui::GetWindowDrawList()->AddLine(upCursorStart3, upCursorEnd3, IM_COL32(200, 200, 200, 255));

		ImGui::SameLine();

		if (myTextCentering == 1)
			color = onColor;
		else
			color = offColor;

		ImVec2 middleCursorStart = ImGui::GetCursorScreenPos();
		ImGui::PushStyleColor(ImGuiCol_Button, color.Value);
		if (ImGui::Button("##ButtonForUseWithCenterMiddle", ImVec2(40, 25)))
			myTextCentering = 1;
		ImGui::PopStyleColor();

		ImVec2 middleCursorStart1 = ImVec2(middleCursorStart.x + 5.f, middleCursorStart.y + 8.5);
		ImVec2 middleCursorEnd1 = ImVec2(middleCursorStart.x + 35.f, middleCursorStart.y + 8.5);
		ImGui::GetWindowDrawList()->AddLine(middleCursorStart1, middleCursorEnd1, IM_COL32(200, 200, 200, 255));

		ImVec2 middleCursorStart2 = ImVec2(middleCursorStart.x + 5.f, middleCursorStart.y + 12.5f);
		ImVec2 middleCursorEnd2 = ImVec2(middleCursorStart.x + 35.f, middleCursorStart.y + 12.5);
		ImGui::GetWindowDrawList()->AddLine(middleCursorStart2, middleCursorEnd2, IM_COL32(200, 200, 200, 255));

		ImVec2 middleCursorStart3 = ImVec2(middleCursorStart.x + 5.f, middleCursorStart.y + 16.5);
		ImVec2 middleCursorEnd3 = ImVec2(middleCursorStart.x + 35.f, middleCursorStart.y + 16.5);
		ImGui::GetWindowDrawList()->AddLine(middleCursorStart3, middleCursorEnd3, IM_COL32(200, 200, 200, 255));

		ImGui::SameLine();

		if (myTextCentering == 2)
			color = onColor;
		else
			color = offColor * 0.5f;

		ImVec2 downCursorStart = ImGui::GetCursorScreenPos();
		ImGui::PushStyleColor(ImGuiCol_Button, color.Value);
		if (ImGui::Button("##ButtonForUseWithCenterDown", ImVec2(40, 25)) && false)
			myTextCentering = 2;
		ImGui::PopStyleColor();

		ImVec2 downCursorStart1 = ImVec2(downCursorStart.x + 5.f, downCursorStart.y + 12.f);
		ImVec2 downCursorEnd1 = ImVec2(downCursorStart.x + 35.f, downCursorStart.y + 12.f);
		ImGui::GetWindowDrawList()->AddLine(downCursorStart1, downCursorEnd1, IM_COL32(200, 200, 200, 255));

		ImVec2 downCursorStart2 = ImVec2(downCursorStart.x + 5.f, downCursorStart.y + 16.f);
		ImVec2 downCursorEnd2 = ImVec2(downCursorStart.x + 35.f, downCursorStart.y + 16.f);
		ImGui::GetWindowDrawList()->AddLine(downCursorStart2, downCursorEnd2, IM_COL32(200, 200, 200, 255));

		ImVec2 downCursorStart3 = ImVec2(downCursorStart.x + 5.f, downCursorStart.y + 20.f);
		ImVec2 downCursorEnd3 = ImVec2(downCursorStart.x + 35.f, downCursorStart.y + 20.f);
		ImGui::GetWindowDrawList()->AddLine(downCursorStart3, downCursorEnd3, IM_COL32(200, 200, 200, 255));
	}

	void TextRenderer::OnDrawGizmos()
	{
		const Math::Vector2f& position = gameObject->transform->GetPosition();
		float rotation = gameObject->transform->GetRotation();
		const Math::Vector2f& scale = gameObject->transform->GetScale() * myRect;

		DebugDrawer::DrawSquare(position * 0.5f + Math::Vector2f(0.5f, 0.5f), rotation, scale * 0.5f, Math::Color(0.7f, 0.7f, 0.7f, 1.f));
	}

	void TextRenderer::Draw()
	{
		if (!myMaterial)
			return;

		const char* textInConstChar = myText->c_str();

		Math::Vector2f position = gameObject->transform->GetPosition();
		float rotation = gameObject->transform->GetRotation();
		Math::Vector2f scale = gameObject->transform->GetScale();

		unsigned shaderID = myMaterial->myShader->GetProgramID();
		myMaterial->myShader->Use(shaderID);

		GraphicsEngine::SetUniform(UniformType::Vector2f, shaderID, "transform.position", &position);
		GraphicsEngine::SetUniform(UniformType::Float, shaderID, "transform.rotation", &rotation);
		GraphicsEngine::SetUniform(UniformType::Vector2f, shaderID, "transform.size", &scale);
		GraphicsEngine::SetGlobalUniforms(shaderID);

		Font& font = TextManager::Get().GetFont(myFontPath->c_str(), myFontSize);

		Math::Vector2f textOffset = { 0, 0 };
		Math::Vector2f scaleRect = scale * myRect;

		lineOffsets.resize(1);
		lineOffsets.back() = 0;
		for (int i = 0; i < myText->size(); i++)
		{
			char character = textInConstChar[i];
			if (character == ' ')
			{
				lineOffsets.back() += scale.x * 0.5f;
				continue;
			}
			else if (character == '\n')
			{
				lineOffsets.emplace_back(0);
				continue;
			}
			Character& characterFace = font.myCharTexture.at(character);
			float convertedAdvance = (float)(characterFace.advance >> 6) * 0.01f * scale.x;;
			lineOffsets.back() += convertedAdvance * 0.5f * myTextAlignment;
		}

		if (myTextAlignment == 0 || myTextAlignment == 3)
			textOffset.x -= scaleRect.x;
		else if (myTextAlignment == 2)
			textOffset.x += scaleRect.x - scale.x;


		Math::Vector2f startOffset = textOffset;

		float maxCharSize = myFont->maxCharHeight;
		if (myTextCentering == 0)
			textOffset.y = (scaleRect.y - myFontSize * 0.0004f);
		else if (myTextCentering == 1)
			textOffset.y = (myFontSize * 0.000175f) * lineOffsets.size();
		// else if (myTextCentering == 2)
		// 	textOffset.y = (-scaleRect.y + 0.0125f)  * lineOffsets.size();


		int currentLineCount = 0;
		for (int i = 0; i < myText->size(); i++)
		{
			char character = textInConstChar[i];

			if (character == '\t')
			{
				textOffset.x += scale.x * 4.f * myCharacterSpacing;
				continue;
			}
			else if (character == '\n')
			{
				textOffset.y -= scale.y * myEnterSpacing * 7.f;
				textOffset.x = startOffset.x;
				currentLineCount++;
				continue;
			}
			else if (character == ' ')
			{
				textOffset.x += scale.x * myCharacterSpacing;
				continue;
			}

			Math::Vector2f scaleRect = scale * myRect;

			if (font.myCharTexture.find(character) == font.myCharTexture.end())
				character = '\n';

			Character& characterFace = font.myCharTexture.at(character);
			float characterAdvance = (float)(characterFace.advance >> 6) * 0.01f * scale.x;

			// float newXOffset = textOffset.x + characterAdvance;
			// if (newXOffset >= scaleRect.x)
			// {
			// 	return;
			// }

			myMaterial->Use(characterFace.textureID);

			Math::Vector2f textSize = { (float)characterFace.size.x, (float)characterFace.size.y };
			GraphicsEngine::SetUniform(UniformType::Vector2f, shaderID, "size", &textSize);

			float lineOffset;
			if (myTextAlignment == 0)
				lineOffset = 0;
			else
				lineOffset = lineOffsets[currentLineCount];


			Math::Vector2f characterSpecificOffset = textOffset;
			characterSpecificOffset.x += (characterFace.bearing.x * 0.01f * scale.x) - lineOffset;
			characterSpecificOffset.y -= (characterFace.size.y - characterFace.bearing.y) * 0.01f * scale.y;
			GraphicsEngine::SetUniform(UniformType::Vector2f, shaderID, "offset", &characterSpecificOffset);

			textOffset.x += characterAdvance * myCharacterSpacing;

			Math::Vector4f color(myTextColor->r, myTextColor->g, myTextColor->b, myTextColor->a);
			GraphicsEngine::SetUniform(UniformType::Vector4f, shaderID, "color", &color);

			TextSprite::Get().Render();
		}
	}

	void TextRenderer::Render()
	{
		CommandListManager::GetSpriteCommandList().Enqueue([&]() {
			this->Draw();
			});
	}

	void TextRenderer::SetFontSize(int aFontSize)
	{
		myFontSize = aFontSize;

		myFont = &TextManager::Get().GetFont(myFontPath->c_str(), myFontSize);
	}

	void TextRenderer::SetFont(const char* aFont)
	{
		myFontPath = aFont;
		myFont = &TextManager::Get().GetFont(myFontPath->c_str(), myFontSize);
	}

	void TextRenderer::SetText(const char* aText)
	{
		myText = aText;
	}
}