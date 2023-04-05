#include "ObjectHandler.h"
#include <iostream>
#include <thread>
#include <ctime>
#include <future>
#include <functional>

ObjectHandler::ObjectHandler(uint16_t amount) :
	m_objectCount(amount),
	m_objects(amount, ObjectHandler::Object(sf::Vector2f(0.0f, 0.0f), sf::Time::Zero)),
	m_vertices(sf::Points, amount)
{
	srand(time(NULL));
	for (size_t i = 0; i < amount; i++)
	{
		m_vertices[i].position = sf::Vector2f(static_cast<float>(rand() % 800), static_cast<float>(rand() % 800));
		m_vertices[i].color = sf::Color(rand() % 255, rand() % 255, rand() % 255);
	}
}

void ObjectHandler::addObject(sf::Vector2f position) {
	m_vertices.append(sf::Vertex(position));
	m_objects.push_back(ObjectHandler::Object(sf::Vector2f(0.0f, 0.0f), sf::Time::Zero));
}

void ObjectHandler::resetObject(uint64_t index) {
	//m_vertices[index].position = sf::Vector2f(0.0f, 0.0f);
	m_vertices[index].position = sf::Vector2f(static_cast<float>(rand() % 800), static_cast<float>(rand() % 800));
	m_objects.at(index).time = 0.0f;
	m_objects.at(index).velocity = sf::Vector2f(0.0f, 0.0f);
}

uint16_t ObjectHandler::getObjectCount() {
	return m_objectCount;
}

void ObjectHandler::update(float acceleration, sf::Time t)
{
	sf::Time timeElapsed = t - totalTime;

	for (size_t i = 0; i < m_objectCount; i++)
	{
		m_objects.at(i).time = timeElapsed.asSeconds();
		m_objects.at(i).velocity += sf::Vector2f(0, acceleration * m_objects.at(i).time);
	
		auto job = std::async(std::bind(&ObjectHandler::fixedUpdate, this, i));
		
	}
}

void ObjectHandler::fixedUpdate(uint16_t index) {
	
		if (m_vertices[index].position.x > 800 || m_vertices[index].position.y > 800)
		{
			auto twerk = std::async(std::bind(&ObjectHandler::resetObject, this, index));

		}
		else
		{
			m_vertices[index].position += sf::Vector2f(0.0f, m_objects.at(index).velocity.y * m_objects.at(index).time);
		}
}
