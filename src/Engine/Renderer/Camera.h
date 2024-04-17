#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Engine {
    class Camera {
        public:
            Camera(glm::vec3 position, glm::vec3 front, glm::vec3 up, glm::mat4 projection);

            const glm::mat4 &GetProjectionMatrix() const { return this->m_ProjectionMatrix; }
            const glm::mat4 &GetViewMatrix() const { return this->m_ViewMatrix; }
            const glm::mat4 &GetViewProjectionMatrix() const { return this->m_ProjectionViewMatrix; }

            void SetPosition(glm::vec3 position) { this->m_Position = position; }
            void SetFront(glm::vec3 front) { this->m_Front = front; }
            void SetUp(glm::vec3 up) { this->m_Up = up; }

            void RecalculateViewMatrix();
            virtual void RecalculateProjectionMatrix() {};

        protected:
            glm::mat4 m_ProjectionMatrix = glm::mat4(1);
            glm::mat4 m_ProjectionViewMatrix = glm::mat4(1);
            glm::mat4 m_ViewMatrix = glm::mat4(1);

        private:
            glm::vec3 m_Position;
            glm::vec3 m_Front;
            glm::vec3 m_Up;
    };

    class OrthographicCamera : public Camera {
        public:
            struct OrthographicData {
                float Left = 1.0f;
                float Right = 1.0f;
                float Bottom = 1.0f; 
                float Top = 1.0f;
            };

        public:
            OrthographicCamera(glm::vec3 position, glm::vec3 front, glm::vec3 up, OrthographicData data);
            virtual void RecalculateProjectionMatrix() override;

            void SetLeft(float left) { m_Data.Left = left; }
            void SetRight(float right) { m_Data.Right = right; }
            void SetBottom(float bottom) { m_Data.Bottom = bottom; }
            void SetTop(float top) { m_Data.Top = top; }

            OrthographicData GetData() { return m_Data; }

        private:
            OrthographicData m_Data;
    };

    class PerspectiveCamera : public Camera {
        public:
            struct PerspectiveData {
                float Fov = 45.0f;
                float NearClip = 1.778f;
                float FarClip = 0.1f; 
                float AspectRatio = 1000.0f;
            };

        public:
            PerspectiveCamera(glm::vec3 position, glm::vec3 front, glm::vec3 up, PerspectiveData data);
            virtual void RecalculateProjectionMatrix() override;

            void SetFov(float fov) { m_Data.Fov = fov; }
            void SetNearClip(float nearClip) { m_Data.NearClip = nearClip; }
            void SetFarClip(float farClip) { m_Data.FarClip = farClip; }
            void SetAspectRatio(float aspectRatio) { m_Data.AspectRatio = aspectRatio; }

            PerspectiveData GetData() const { return m_Data; }

        private:
            PerspectiveData m_Data;
    };

}