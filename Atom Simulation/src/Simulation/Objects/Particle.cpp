#include "Particle.h"
#include "Global.h"

Particle::Particle(ParticleType type, const glm::vec3& position, float scale)
	: m_Type(type), m_Position(position), m_Scale(scale)
{
	if (type == PROTON) {
		m_Color = glm::vec3(0.0f, 0.0f, 0.6f);
	}
	else if (type == NEUTRON){
		m_Color = glm::vec3(0.6f, 0.0f, 0.0f);
	}
	else {
		m_Color = glm::vec3(0.0f);
	}
}

Particle::~Particle() {}

void Particle::Draw(Shader& shader)
{
	shader.Bind();

	glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Position);
	model = glm::scale(model, glm::vec3(m_Scale));
	shader.SetUniformMat4f("u_Model", model);

	shader.SetUniform4f("u_Color", m_Color.r, m_Color.g, m_Color.b, 1.0f);

	GLCall(glDrawElements(GL_TRIANGLES, SPHERE_INDICIES_COUNT, GL_UNSIGNED_INT, nullptr));
}

