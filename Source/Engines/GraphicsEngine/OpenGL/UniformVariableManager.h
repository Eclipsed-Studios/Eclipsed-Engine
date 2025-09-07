#pragma once 

#include <vector>
#include <string>

#include "Math/Math.h"


namespace ENGINE_NAMESPACE
{
    enum class UniformType
    {
        Bool,

        Float,
        Vector2f,
        Vector3f,
        Vector4f,

        // Double,
        // Vector2d,
        // Vector3d,
        // Vector4d,

        Int,
        // Vector2i,
        // Vector3i,
        // Vector4i,

        // UnsignedInt,
        // Vector2ui,
        // Vector3ui,
        // Vector4ui,

        Matrix2x2f,
        Matrix3x3f,
        Matrix4x4f
    };

    class UniformVariableManager
    {
    private:

        friend class GraphicsEngine;

        struct GlobalUniformValueInt
        {
            std::string uniformName;
            int value;
        };

        struct GlobalUniformValueFloat
        {
            std::string uniformName;
            float value;
        };

        struct GlobalUniformValueVector2Float
        {
            std::string uniformName;
            Math::Vector2f value;
        };

        struct GlobalUniformValueVector3Float
        {
            std::string uniformName;
            Math::Vector4f value;
        };

        struct GlobalUniformValueVector4Float
        {
            std::string uniformName;
            Math::Vector4f value;
        };

        struct GlobalUniformValueMatrixMatrix2x2Float
        {
            std::string uniformName;
            float value[4];
        };

        struct GlobalUniformValueMatrixMatrix3x3Float
        {
            std::string uniformName;
            float value[9];
        };

        struct GlobalUniformValueMatrixMatrix4x4Float
        {
            std::string uniformName;
            float value[16];
        };

        std::vector<GlobalUniformValueInt> myGlobalUniformsInt;

        std::vector<GlobalUniformValueFloat> myGlobalUniformsFloat;

        std::vector<GlobalUniformValueVector2Float> myGlobalUniformsVector2Float;
        std::vector<GlobalUniformValueVector3Float> myGlobalUniformsVector3Float;
        std::vector<GlobalUniformValueVector4Float> myGlobalUniformsVector4Float;

        std::vector<GlobalUniformValueMatrixMatrix2x2Float> myGlobalUniformsMatrix2x2Float;
        std::vector<GlobalUniformValueMatrixMatrix3x3Float> myGlobalUniformsMatrix3x3Float;
        std::vector<GlobalUniformValueMatrixMatrix4x4Float> myGlobalUniformsMatrix4x4Float;

        void SetGlobalUniforms(unsigned aShaderProgram);


        void AddInt(const std::string& aUniformName, int* aValue) { myGlobalUniformsInt.emplace_back(aUniformName, *aValue); }

        void AddFloat(const std::string& aUniformName, float* aValue) { myGlobalUniformsFloat.emplace_back(aUniformName, *aValue); }

        void AddVec2Float(const std::string& aUniformName, Math::Vector2f* aValue) { myGlobalUniformsVector2Float.emplace_back(aUniformName, *aValue); }
        void AddVec3Float(const std::string& aUniformName, Math::Vector4f* aValue) { myGlobalUniformsVector3Float.emplace_back(aUniformName, *aValue); }
        void AddVec4Float(const std::string& aUniformName, Math::Vector4f* aValue) { myGlobalUniformsVector4Float.emplace_back(aUniformName, *aValue); }

        void AddMat2x2(const std::string& aUniformName, float* aValue)
        {
            myGlobalUniformsMatrix2x2Float.emplace_back(
                GlobalUniformValueMatrixMatrix2x2Float{ aUniformName,
                    aValue[0], aValue[1], aValue[2], aValue[3]
                }
            );
        }
        void AddMat3x3(const std::string& aUniformName, float* aValue)
        {
            myGlobalUniformsMatrix3x3Float.emplace_back(
                GlobalUniformValueMatrixMatrix3x3Float{ aUniformName,
                    aValue[0], aValue[1], aValue[2], aValue[3], aValue[4], aValue[5], aValue[6], aValue[7], aValue[8]
                }
            );
        }
        void AddMat4x4(const std::string& aUniformName, float* aValue)
        {
            myGlobalUniformsMatrix4x4Float.emplace_back(
                GlobalUniformValueMatrixMatrix4x4Float{ aUniformName,
                    aValue[0], aValue[1], aValue[2], aValue[3], aValue[4], aValue[5], aValue[6], aValue[7],
                    aValue[8], aValue[9], aValue[10], aValue[11], aValue[12], aValue[13], aValue[14], aValue[15]
                });
        }




        void UpdateInt(const std::string& aUniformName, int* aValue)
        {
            for (auto& value : myGlobalUniformsInt)
            {
                if (value.uniformName == aUniformName)
                {
                    value.value = *aValue;
                    return;
                }
            }

            AddInt(aUniformName, aValue);
        }

        void UpdateFloat(const std::string& aUniformName, float* aValue)
        {
            for (auto& value : myGlobalUniformsFloat)
            {
                if (value.uniformName == aUniformName)
                {
                    value.value = *aValue;
                    return;
                }
            }

            AddFloat(aUniformName, aValue);
        }

        void UpdateVec2Float(const std::string& aUniformName, Math::Vector2f* aValue)
        {
            for (auto& value : myGlobalUniformsVector2Float)
            {
                if (value.uniformName == aUniformName)
                {
                    value.value = *aValue;
                    return;
                }
            }
            
            AddVec2Float(aUniformName, aValue);
        }
        void UpdateVec3Float(const std::string& aUniformName, Math::Vector4f* aValue)
        {
            for (auto& value : myGlobalUniformsVector3Float)
            {
                if (value.uniformName == aUniformName)
                {
                    value.value = *aValue;
                    return;
                }
            }

            AddVec3Float(aUniformName, aValue);
        }
        void UpdateVec4Float(const std::string& aUniformName, Math::Vector4f* aValue)
        {
            for (auto& value : myGlobalUniformsVector4Float)
            {
                if (value.uniformName == aUniformName)
                {
                    value.value = *aValue;
                    return;
                }
            }

            AddVec4Float(aUniformName, aValue);
        }

        void UpdateMat2x2(const std::string& aUniformName, float* aValue)
        {
            for (auto& value : myGlobalUniformsMatrix2x2Float)
            {
                if (value.uniformName == aUniformName)
                {
                    std::memcpy(value.value, aValue, 16);
                    return;
                }
            }

            AddMat2x2(aUniformName, aValue);
        }
        void UpdateMat3x3(const std::string& aUniformName, float* aValue)
        {
            for (auto& value : myGlobalUniformsMatrix3x3Float)
            {
                if (value.uniformName == aUniformName)
                {
                    std::memcpy(value.value, aValue, 36);
                    return;
                }
            }

            AddMat3x3(aUniformName, aValue);
        }
        void UpdateMat4x4(const std::string& aUniformName, float* aValue)
        {
            for (auto& value : myGlobalUniformsMatrix4x4Float)
            {
                if (value.uniformName == aUniformName)
                {
                    std::memcpy(value.value, aValue, 64);
                    return;
                }
            }

            AddMat4x4(aUniformName, aValue);
        }
    };
}