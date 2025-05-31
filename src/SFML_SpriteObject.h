#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
class SFML_SpriteObject : public sf::Drawable, public sf::Transformable
{
public:
	SFML_SpriteObject();
	virtual ~SFML_SpriteObject();

	bool setDefaultTexture(std::string textureFile);
	bool setDefaultTexture(std::string textureFile, std::string spriteInfoFile);

	void setColor(const sf::Color& color);

	sf::Vector2f getWorldPos();
	sf::Vector2f getScreenPos(sf::Transform cameraScreenTransform);

	sf::FloatRect getLocalBounds() const;
	sf::FloatRect getGlobalBounds() const;

	virtual void update(float elapsedTime);
	

protected:
	sf::Sprite m_sprite;
	sf::Texture* m_spriteTexture;

	sf::IntRect m_textureRectangle;
	sf::Vector2f m_spriteOrigin;

	bool m_initialised;

private:
	sf::Texture* m_defaultTexture;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

